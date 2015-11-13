/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "Tuto15MultithreadCtrl/SIncrementArray.hpp"

#include <fwComEd/helper/Array.hpp>

#include <fwThread/Timer.hpp>

#include <fwData/Array.hpp>
#include <fwData/mt/ObjectWriteLock.hpp>

#include <fwServices/macros.hpp>
#include <fwServices/ObjectMsg.hpp>

#include <fwCom/Signal.hxx>

#include <boost/date_time/posix_time/posix_time.hpp>

#include <functional>

fwServicesRegisterMacro( ::fwServices::IService, ::Tuto15MultithreadCtrl::SIncrementArray, ::fwData::Array );

namespace Tuto15MultithreadCtrl
{

SIncrementArray::SIncrementArray() throw() :
    m_periodInMillisec(500)
{
}

SIncrementArray::~SIncrementArray() throw()
{
}

void SIncrementArray::starting() throw( ::fwTools::Failed )
{
    SLM_TRACE_FUNC();
    m_timer = m_associatedWorker->createTimer();
    m_timer->setFunction( std::bind(&SIncrementArray::updating, this) );
    m_timer->setDuration( ::boost::chrono::milliseconds(m_periodInMillisec) );
}

void SIncrementArray::stopping() throw( ::fwTools::Failed )
{
    m_timer.reset();
}

void SIncrementArray::updating() throw( ::fwTools::Failed )
{
    ::fwData::Array::sptr array = this->getObject< ::fwData::Array >();
    ::fwData::mt::ObjectWriteLock writeLock(array);

    SLM_ASSERT("No array.", array);
    SLM_ASSERT("Array : bad number of dimensions.", array->getNumberOfDimensions() == 1 );

    const int arraySize = array->getSize()[0];

    ::fwComEd::helper::Array arrayHelper(array);

    unsigned int *buffer = static_cast< unsigned int* >( arrayHelper.getBuffer() );

    for (int i = 0; i < arraySize; i++)
    {
        ++buffer[i];
    }

    ::fwData::Object::ObjectModifiedSignalType::sptr sig
        = array->signal< ::fwData::Object::ObjectModifiedSignalType>( ::fwData::Object::s_OBJECT_MODIFIED_SIG );


    ::fwServices::ObjectMsg::sptr msg = ::fwServices::ObjectMsg::New();
    msg->addEvent("MODIFIED_EVENT");
    {
        ::fwCom::Connection::Blocker block(sig->getConnection(m_slotReceive));
        sig->asyncEmit(msg);
    }

}

void SIncrementArray::configuring() throw( ::fwTools::Failed )
{

}

void SIncrementArray::receiving( ::fwServices::ObjectMsg::csptr _msg ) throw ( ::fwTools::Failed )
{
    m_timer->start();
}

void SIncrementArray::swapping( ) throw( ::fwTools::Failed )
{

}

} // namespace Tuto15MultithreadCtrl
