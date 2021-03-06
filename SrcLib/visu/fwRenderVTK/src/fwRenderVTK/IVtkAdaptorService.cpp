/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2012.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include <boost/foreach.hpp>

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAbstractPropPicker.h>
#include <vtkTransform.h>

#include <fwData/String.hpp>
#include <fwTools/fwID.hpp>

#include <fwServices/Base.hpp>
#include <fwServices/IEditionService.hpp>

#include "fwRenderVTK/IVtkAdaptorService.hpp"



namespace fwRenderVTK
{

IVtkAdaptorService::IVtkAdaptorService() throw()
    : m_comChannelPriority(0.5),
      m_vtkPipelineModified(true),
      m_rendererId ("default") ,
      m_pickerId   (""), // by default no Picker
      m_transformId   (""), // by default no Transform
      m_propCollection ( vtkPropCollection::New() ),
      m_autoRender(true)
{
    m_connections = ::fwServices::helper::SigSlotConnection::New();
}

IVtkAdaptorService::~IVtkAdaptorService() throw()
{
    m_propCollection->Delete();
}

void IVtkAdaptorService::info(std::ostream &_sstream )
{
    _sstream << "IVtkAdaptorService : " ;
    this->SuperClass::info( _sstream ) ;
}

void IVtkAdaptorService::starting() throw(fwTools::Failed)
{
    /// Install observation
    m_connections->connect(this->getObject(), this->getSptr(), this->getObjSrvConnections());

    assert( m_renderService.lock() );

    doStart();
    requestRender();
}

//------------------------------------------------------------------------------

void IVtkAdaptorService::stopping() throw(fwTools::Failed)
{
    /// Stop observation
    m_connections->disconnect();
    doStop();
    requestRender();
}
//------------------------------------------------------------------------------

void IVtkAdaptorService::swapping() throw(fwTools::Failed)
{
    m_connections->disconnect();
    m_connections->connect(this->getObject(), this->getSptr(), this->getObjSrvConnections());
    doSwap();
    requestRender();
}

//------------------------------------------------------------------------------

void IVtkAdaptorService::updating() throw(fwTools::Failed)
{
    doUpdate();
    requestRender();
}

//------------------------------------------------------------------------------

void IVtkAdaptorService::receiving(::fwServices::ObjectMsg::csptr msg) throw(fwTools::Failed)
{
    doReceive(msg);
    requestRender();
}

//------------------------------------------------------------------------------

void IVtkAdaptorService::setRenderService( VtkRenderService::sptr service)
{
    /// Preconditions
    SLM_ASSERT("service not instanced", service);
    assert( this->isStopped() ) ;

    m_renderService = service ;
}

//------------------------------------------------------------------------------

void IVtkAdaptorService::setRenderId(VtkRenderService::RendererIdType newID)
{
    m_rendererId =  newID;
}

//------------------------------------------------------------------------------

void IVtkAdaptorService::setVtkPipelineModified()
{
    m_vtkPipelineModified = true;
}

//------------------------------------------------------------------------------

void IVtkAdaptorService::requestRender()
{
    if ( this->getRenderService()->isShownOnScreen() && m_vtkPipelineModified && m_autoRender )
    {
        if ( !this->getRenderService()->getPendingRenderRequest())
        {
            this->getRenderService()->setPendingRenderRequest(true);
            this->getRenderService()->slot(VtkRenderService::s_RENDER_SLOT)->asyncRun();
        }
        m_vtkPipelineModified = false;
    }
}

//------------------------------------------------------------------------------

VtkRenderService::RendererIdType IVtkAdaptorService::getRenderId()
{
    return m_rendererId;
}

//------------------------------------------------------------------------------

VtkRenderService::sptr  IVtkAdaptorService:: getRenderService()
{
    return m_renderService.lock();
}

//------------------------------------------------------------------------------

vtkRenderer* IVtkAdaptorService::getRenderer()
{
    return m_renderService.lock()->getRenderer(m_rendererId);
}

//------------------------------------------------------------------------------

void IVtkAdaptorService::setPickerId(VtkRenderService::PickerIdType newID)
{
    m_pickerId =  newID;
}

//------------------------------------------------------------------------------

VtkRenderService::PickerIdType IVtkAdaptorService::getPickerId()
{
    return m_pickerId;
}

//------------------------------------------------------------------------------

vtkAbstractPropPicker * IVtkAdaptorService::getPicker(std::string pickerId)
{
    if (pickerId.empty())
    {
        pickerId = m_pickerId;
    }
    return m_renderService.lock()->getPicker(pickerId);
}

//------------------------------------------------------------------------------

void IVtkAdaptorService::setTransformId(VtkRenderService::VtkObjectIdType newID)
{
    m_transformId =  newID;
}

//------------------------------------------------------------------------------

VtkRenderService::VtkObjectIdType IVtkAdaptorService::getTransformId()
{
    return m_transformId;
}

//------------------------------------------------------------------------------

vtkTransform * IVtkAdaptorService::getTransform()
{
    return vtkTransform::SafeDownCast(m_renderService.lock()->getVtkObject(m_transformId));
}

//------------------------------------------------------------------------------

vtkObject * IVtkAdaptorService::getVtkObject(VtkRenderService::VtkObjectIdType objectId)
{
    if (!objectId.empty())
    {
        return m_renderService.lock()->getVtkObject(objectId);
    }
    return NULL;
}

//------------------------------------------------------------------------------

vtkRenderWindowInteractor* IVtkAdaptorService::getInteractor()
{
    return this->getRenderer()->GetRenderWindow()->GetInteractor();
}

//------------------------------------------------------------------------------

::fwData::Object::sptr IVtkAdaptorService::getAssociatedObject(vtkProp *prop, int depth)
{
    ::fwData::Object::sptr obj;

    if (prop)
    {
        if ( m_propCollection->IsItemPresent(prop) )
        {
            obj = this->getObject();
        }
        else
        {
            ::fwData::Object::sptr res;
            BOOST_FOREACH( ServiceVector::value_type service, m_subServices)
            {
                if(!service.expired())
                {
                    res = service.lock()->getAssociatedObject(prop, depth - 1 );
                    if (res) break;
                }
            }
            obj = ( res && depth == 0 ) ? this->getObject() : res;
        }
    }
    return obj;
}

//------------------------------------------------------------------------------

void IVtkAdaptorService::registerService( ::fwRenderVTK::IVtkAdaptorService::sptr service)
{
        m_subServices.push_back(service);
}

//------------------------------------------------------------------------------

void IVtkAdaptorService::unregisterServices()
{
    BOOST_FOREACH(
            ServiceVector::value_type service,
            m_subServices
            )
    {
        if(!service.expired())
        {
            service.lock()->stop();
            ::fwServices::OSR::unregisterService(service.lock());
        }
    }
    m_subServices.clear();
}

//------------------------------------------------------------------------------

void IVtkAdaptorService::registerProp(vtkProp *prop)
{
    getProps(m_propCollection, prop);
}

//------------------------------------------------------------------------------

void IVtkAdaptorService::getProps(vtkPropCollection *propc, vtkProp *prop)
{
    int initSize = propc->GetNumberOfItems();

    prop->GetActors(propc);
    prop->GetActors2D(propc);
    prop->GetVolumes(propc);

    if (initSize == propc->GetNumberOfItems())
    {
        propc->AddItem(prop);
    }
}

//------------------------------------------------------------------------------

void IVtkAdaptorService::getAllSubProps(vtkPropCollection *propc, int depth)
{
    vtkProp *prop;

    m_propCollection->InitTraversal();
    while ( (prop = m_propCollection->GetNextProp()) )
    {
        getProps(propc, prop);
    }

    if(depth != 0)
    {
        BOOST_FOREACH( ServiceVector::value_type service, m_subServices)
        {
            if(!service.expired())
            {
                service.lock()->getAllSubProps( propc, depth - 1 );
            }
        }
    }
}

//------------------------------------------------------------------------------

void IVtkAdaptorService::unregisterProps()
{
    m_propCollection->RemoveAllItems();
}

//------------------------------------------------------------------------------

void IVtkAdaptorService::addToRenderer(vtkProp *prop)
{
    this->registerProp(prop);
    this->getRenderer()->AddViewProp(prop);
    this->setVtkPipelineModified();
}

//------------------------------------------------------------------------------

void IVtkAdaptorService::addToPicker(vtkProp *prop, std::string pickerId)
{
    OSLM_ASSERT("Picker '"<< pickerId << "' undefined." , this->getPicker(pickerId));
    this->getPicker(pickerId)->AddPickList(prop);
    this->setVtkPipelineModified();
}

//------------------------------------------------------------------------------

void IVtkAdaptorService::removeFromPicker(vtkProp *prop, std::string pickerId)
{
    OSLM_ASSERT("Picker '"<< pickerId << "' undefined." , this->getPicker(pickerId));
    this->getPicker(pickerId)->DeletePickList(prop);
    this->setVtkPipelineModified();
}

//------------------------------------------------------------------------------

void IVtkAdaptorService::removeAllPropFromRenderer()
{
    vtkPropCollection *propc = m_propCollection;
    vtkProp *prop;

    propc->InitTraversal();
    while ( (prop = propc->GetNextProp()) )
    {
        this->getRenderer()->RemoveViewProp(prop);
    }
    this->unregisterProps();
    this->setVtkPipelineModified();
}


} // namespace fwRenderVTK

