/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2014.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include <QGraphicsItemGroup>
#include <QPoint>
#include <QBitmap>
#include <QPixmap>

#include <fwData/Image.hpp>
#include <fwData/Boolean.hpp>
#include <fwData/Composite.hpp>
#include <fwData/Integer.hpp>
#include <fwData/TransferFunction.hpp>

#include <fwServices/Base.hpp>
#include <fwServices/IEditionService.hpp>

#include <fwComEd/ImageMsg.hpp>
#include <fwComEd/TransferFunctionMsg.hpp>
#include <fwComEd/Dictionary.hpp>
#include <fwComEd/helper/Image.hpp>

#include "scene2D/adaptor/Negato.hpp"
#include "scene2D/Scene2DGraphicsView.hpp"

fwServicesRegisterMacro( ::scene2D::adaptor::IAdaptor , ::scene2D::adaptor::Negato  , ::fwData::Image ) ;


namespace scene2D
{
namespace adaptor
{

typedef ::fwComEd::helper::MedicalImageAdaptor MedicalImageAdaptor;

//-----------------------------------------------------------------------------

Negato::Negato() throw()
: m_pointIsCaptured (false),
    m_orientation(MedicalImageAdaptor::Z_AXIS), m_changeSliceTypeAllowed(true)
{
    this->installTFSelectionEventHandler(this);
//    this->addNewHandledEvent( ::fwComEd::ImageMsg::SLICE_INDEX );
//    this->addNewHandledEvent( ::fwComEd::TransferFunctionMsg::WINDOWING );
//    this->addNewHandledEvent( ::fwComEd::ImageMsg::CHANGE_SLICE_TYPE );
}

//-----------------------------------------------------------------------------

Negato::~Negato() throw()
{}

//-----------------------------------------------------------------------------

void Negato::configuring() throw ( ::fwTools::Failed )
{
    SLM_TRACE_FUNC();

    SLM_ASSERT("\"config\" tag missing", m_configuration->getName() == "config");

    this->IAdaptor::configuring();

    SLM_TRACE("IAdaptor configuring ok");

    if( !m_configuration->getAttributeValue("orientation").empty() )
    {
        const std::string orientationValue = m_configuration->getAttributeValue("orientation");

        if ( orientationValue == "axial" )
        {
            m_orientation = MedicalImageAdaptor::Z_AXIS;
        }
        else if ( orientationValue == "sagittal" )
        {
            m_orientation = MedicalImageAdaptor::X_AXIS;
        }
        else if ( orientationValue == "frontal" )
        {
            m_orientation = MedicalImageAdaptor::Y_AXIS;
        }
    }

    if(!m_configuration->getAttributeValue("changeSliceType").empty())
    {
        const std::string changeValue = m_configuration->getAttributeValue(("changeSliceType"));

        if(changeValue == "true" || changeValue == "yes")
        {
            m_changeSliceTypeAllowed = true;
        }
        else if(changeValue == "no" || changeValue == "false")
        {
            m_changeSliceTypeAllowed = false;
        }
    }
    this->parseTFConfig( m_configuration );
}

//-----------------------------------------------------------------------------

void Negato::updateBufferFromImage( QImage * qimg )
{
    // Window min/max
    ::fwData::TransferFunction::sptr tf = this->getTransferFunction();
    const double wlMin = tf->getWLMinMax().first;
    const double wlMax = tf->getWLMinMax().second;

    // Window max
    ::fwData::Image::sptr image = this->getObject< ::fwData::Image >();
    ::fwComEd::helper::Image imgHelper(image);
    const ::fwData::Image::SizeType size = image->getSize();
    signed short * imgBuff = (signed short *) imgHelper.getBuffer();
    const double window = tf->getWindow();
    const size_t imageZOffset = size[0] * size[1];

    const double tfMin = tf->getMinMaxTFValues().first;
    const double tfMax = tf->getMinMaxTFValues().second;


    // Fill image according to current slice type:
    if( m_orientation == MedicalImageAdaptor::X_AXIS ) // sagittal
    {
        for( size_t z = 0; z < size[2]; ++z)
        {
            const size_t zOffset = z * imageZOffset;
            const int zPos = static_cast<int>(size[2] - 1 - z);
            const size_t zxOffset = zOffset + m_sagittalIndex->value();

            for( size_t y = 0; y < size[1]; y++ )
            {
                QRgb val = this->getQImageVal(zxOffset + y * size[0], imgBuff, wlMin, wlMax, window, tfMin, tfMax, tf);
                qimg->setPixel(y, zPos, val);
            }
        }
    }
    else if( m_orientation == MedicalImageAdaptor::Y_AXIS ) // frontal
    {
        const double yOffset = m_frontalIndex->value() * size[0];

        for( ::boost::int32_t z = 0; z < size[2]; ++z)
        {
            const double zOffset = z * imageZOffset;
            const double zPos = size[2] - 1 - z;
            const double zyOffset = zOffset + yOffset;

            for( ::boost::int32_t x = 0; x < size[0]; x++ )
            {
                QRgb val = this->getQImageVal(zyOffset + x, imgBuff, wlMin, wlMax, window, tfMin, tfMax, tf);
                qimg->setPixel(x, zPos, val);
            }
        }
    }
    else if( m_orientation == MedicalImageAdaptor::Z_AXIS ) // axial
    {
        const double zOffset = m_axialIndex->value() * imageZOffset;

        for( ::boost::int32_t y = 0; y < size[1]; y++ )
        {
            const unsigned int yOffset = static_cast<unsigned int>(y * size[0]);
            const unsigned int zyOffset = zOffset + yOffset;

            for( ::boost::int32_t x = 0; x < size[0]; x++ )
            {
                QRgb val = this->getQImageVal(x + zyOffset, imgBuff, wlMin, wlMax, window, tfMin, tfMax, tf);
                qimg->setPixel(x, y, val);
            }
        }
    }

    QPixmap m_pixmap = QPixmap::fromImage( *m_qimg );
    m_pixmapItem->setPixmap(m_pixmap);
}

//-----------------------------------------------------------------------------

QRgb Negato::getQImageVal(
    const size_t index, signed short* buffer, const double wlMin, const double wlMax, const double window,
    const double tfMin, const double tfMax, ::fwData::TransferFunction::sptr tf)
{
    signed short val16 = buffer[index];

    double value = (val16 - wlMin) / window;
    value = value * (tfMax - tfMin) + tfMin;

    ::fwData::TransferFunction::TFColor color = tf->getInterpolatedColor(value);

    // use QImage::Format_RGBA8888 in QImage if you need alpha value
    return qRgb(color.r*255, color.g*255, color.b*255);
}

//---------------------------------------------------------------------------

QImage * Negato::createQImage()
{
    SLM_TRACE_FUNC();

    ::fwData::Image::sptr img = this->getObject< ::fwData::Image >();

    const ::fwData::Image::SizeType size = img->getSize();
    const ::fwData::Image::SpacingType spacing = img->getSpacing();
    const ::fwData::Image::OriginType origin = img->getOrigin();

    double qImageSpacing[2];
    double qImageOrigin[2];
    int qImageSize[2];

    switch ( m_orientation )
    {
        case MedicalImageAdaptor::X_AXIS:// sagittal
            this->m_yAxis->setScale(-1);
            qImageSize[0]    = static_cast<int>(size[1]);
            qImageSize[1]    = static_cast<int>(size[2]);
            qImageSpacing[0] = spacing[1];
            qImageSpacing[1] = spacing[2];
            qImageOrigin[0]  = origin[1] - 0.5f*spacing[1];
            qImageOrigin[1]  =  - ( origin[2] + size[2] * spacing[2]  - 0.5f*spacing[2]);
            break;

        case MedicalImageAdaptor::Y_AXIS:// frontal
            qImageSize[0]    = static_cast<int>(size[0]);
            qImageSize[1]    = static_cast<int>(size[2]);
            qImageSpacing[0] = spacing[0];
            qImageSpacing[1] = spacing[2];
            qImageOrigin[0]  = origin[0] - 0.5f*spacing[0];
            qImageOrigin[1]  =  - ( origin[2] + size[2] * spacing[2]  - 0.5f*spacing[2]);
            break;

        case MedicalImageAdaptor::Z_AXIS:// axial
            qImageSize[0]    = static_cast<int>(size[0]);
            qImageSize[1]    = static_cast<int>(size[1]);
            qImageSpacing[0] = spacing[0];
            qImageSpacing[1] = spacing[1];
            qImageOrigin[0]  = origin[0] - 0.5f*spacing[0];
            qImageOrigin[1]  = origin[1] - 0.5f*spacing[1];
            break;

        default:
            SLM_FATAL("Unsupported value for m_orientation");
            break;
    }

    // Create empty QImage
    QImage * qimage = new QImage(qImageSize[0], qImageSize[1], QImage::Format_RGB888);

    // Place m_pixmapItem
    m_pixmapItem->resetTransform();
    m_pixmapItem->setTransform(QTransform::fromScale(qImageSpacing[0], qImageSpacing[1]), true);
    m_pixmapItem->setPos(qImageOrigin[0], qImageOrigin[1]);

    // Force bounding box recomputing ( Qt bug )
    m_layer->removeFromGroup( m_pixmapItem );
    m_layer->addToGroup( m_pixmapItem );

    // Update image scene
    this->getScene2DRender()->updateSceneSize( 0.20f );

    return qimage;
}

//-----------------------------------------------------------------------------

void Negato::doStart() throw ( ::fwTools::Failed )
{
    ::fwData::Image::sptr image = this->getObject< ::fwData::Image >();
    this->updateImageInfos( image );
    this->updateTransferFunction( image, this->getSptr() );

    m_pixmapItem = new QGraphicsPixmapItem();
    m_pixmapItem->setShapeMode( QGraphicsPixmapItem::BoundingRectShape );
    m_pixmapItem->setTransformationMode(Qt::SmoothTransformation);
    m_layer = new QGraphicsItemGroup();
    m_layer->resetTransform();
    m_layer->addToGroup( m_pixmapItem );
    m_layer->setPos( m_xAxis->getOrigin(), m_yAxis->getOrigin() );
    m_layer->setZValue( m_zValue );
    this->getScene2DRender()->getScene()->addItem( m_layer );

    m_qimg = this->createQImage();
    this->updateBufferFromImage( m_qimg );

    this->getScene2DRender()->updateSceneSize( 1.f );

    this->installTFObserver( this->getSptr() );
}

//-----------------------------------------------------------------------------

void Negato::doUpdate() throw ( ::fwTools::Failed )
{
    SLM_TRACE_FUNC();

    m_qimg = this->createQImage();
    this->updateBufferFromImage( m_qimg );
}

//-----------------------------------------------------------------------------

void Negato::doReceive( fwServices::ObjectMsg::csptr msg) throw ( ::fwTools::Failed )
{
    SLM_TRACE_FUNC();
    if( msg->hasEvent( ::fwComEd::ImageMsg::VISIBILITY ))
    {
        ::fwData::Object::csptr dataInfo = msg->getDataInfo(::fwComEd::ImageMsg::VISIBILITY);
        SLM_ASSERT("dataInfo is missing", dataInfo);
            
        ::fwData::Boolean::csptr boolean = ::fwData::Boolean::dynamicConstCast(dataInfo);
            
        SLM_ASSERT("dataInfo is missing", boolean);
           
        if( boolean->getValue() ) // display the scene
        {
            m_layer->setVisible(true);
        }
        else // remove the layer from the scene
        {
            m_layer->setVisible(false);
        }
    }
    if( msg->hasEvent( ::fwComEd::ImageMsg::CHANGE_SLICE_TYPE) && m_changeSliceTypeAllowed )
    {
        ::fwData::Object::csptr cObjInfo = msg->getDataInfo( ::fwComEd::ImageMsg::CHANGE_SLICE_TYPE );
        ::fwData::Object::sptr objInfo = ::boost::const_pointer_cast< ::fwData::Object > ( cObjInfo );
        ::fwData::Composite::sptr info = ::fwData::Composite::dynamicCast ( objInfo );

        ::fwData::Integer::sptr fromSliceType = ::fwData::Integer::dynamicCast( info->getContainer()["fromSliceType"] );
        ::fwData::Integer::sptr toSliceType = ::fwData::Integer::dynamicCast( info->getContainer()["toSliceType"] );

        if( toSliceType->value() == static_cast< int > ( m_orientation ) )
        {
            m_orientation = static_cast< MedicalImageAdaptor::Orientation > ( fromSliceType->value() );
        }
        else if(fromSliceType->value() == static_cast<int>(m_orientation))
        {
            m_orientation = static_cast< MedicalImageAdaptor::Orientation >( toSliceType->value() );
        }

        // manages the modification of axes
        if ( m_orientation == MedicalImageAdaptor::Z_AXIS )
        {
            this->m_yAxis->setScale(1);
        }
        else
        {
            this->m_yAxis->setScale(-1);
        }

        this->doUpdate();
    }

    if ( msg->hasEvent( ::fwComEd::ImageMsg::MODIFIED ) )
    {
        this->updateBufferFromImage(m_qimg);
    }

    if ( this->upadteTFObserver(msg, this->getSptr() )
            || msg->hasEvent( ::fwComEd::TransferFunctionMsg::WINDOWING )
            || msg->hasEvent( ::fwComEd::TransferFunctionMsg::MODIFIED_POINTS ) )
    {
        this->updateBufferFromImage( m_qimg );
    }

    if ( msg->hasEvent( ::fwComEd::ImageMsg::SLICE_INDEX ) )
    {
        ::fwComEd::ImageMsg::csptr imgMsg = ::fwComEd::ImageMsg::dynamicConstCast(msg);
        imgMsg->getSliceIndex(m_axialIndex, m_frontalIndex, m_sagittalIndex);

        ::fwData::Image::sptr image = this->getObject< ::fwData::Image >();
        this->updateImageInfos( image );
        this->updateBufferFromImage( m_qimg );
    }
}

//-----------------------------------------------------------------------------

void Negato::doSwap() throw ( ::fwTools::Failed )
{
    this->doStop();
    this->doStart();
}

//-----------------------------------------------------------------------------

void Negato::doStop() throw ( ::fwTools::Failed )
{
    this->removeTFObserver();

    this->getScene2DRender()->getScene()->removeItem(m_layer);

    delete m_qimg;
    delete m_pixmapItem;
    delete m_layer;
}

//-----------------------------------------------------------------------------

void Negato::processInteraction( ::scene2D::data::Event::sptr _event )
{
    SLM_TRACE_FUNC();

    // if a key is pressed
    if(_event->getType() == ::scene2D::data::Event::KeyRelease)
    {
        // if pressed key is 'R'
        if ( _event->getKey() == Qt::Key_R )
        {
            // get image origin
            QRectF recImage =  m_pixmapItem->sceneBoundingRect();
       
            ::scene2D::data::Viewport::sptr sceneViewport = this->getScene2DRender()->getViewport();

            float sceneWidth  = static_cast<float>(this->getScene2DRender()->getView()->width());
            float sceneHeight = static_cast<float>(this->getScene2DRender()->getView()->height());

            float ratioYonXimage = recImage.height() / recImage.width();
            float sceneRatio      = sceneHeight / sceneWidth;

            if ( sceneRatio > ratioYonXimage ) // used scene ratio
            {
                float widthViewPortNew = recImage.width();
                float heightViewPortNew = widthViewPortNew * sceneRatio;

                // computes new y origin
                float newOrigineY =  recImage.y() - ( heightViewPortNew - recImage.height() ) / 2.f;
                
                sceneViewport->setX(  recImage.x() );
                sceneViewport->setY( newOrigineY );
                sceneViewport->setWidth(  widthViewPortNew );
                sceneViewport->setHeight( heightViewPortNew );
            }
            else
            {               
                float heightViewPortNew = recImage.height();
                float widthViewPortNew = heightViewPortNew / sceneRatio;

                // computes new x origin
                float newOrigineX =  recImage.x() - (widthViewPortNew - recImage.width() )/ 2.f;
                
                sceneViewport->setX( newOrigineX );
                sceneViewport->setY( recImage.y() );
                sceneViewport->setWidth(  widthViewPortNew );
                sceneViewport->setHeight( heightViewPortNew );
            }

            this->getScene2DRender()->getView()->updateFromViewport();
        }

        //image pixel
        if ( _event->getKey() == Qt::Key_F )
        {
            m_pixmapItem->setTransformationMode(Qt::FastTransformation);
            this->doUpdate();
        }

        //image smooth
        if ( _event->getKey() == Qt::Key_S )
        {
            m_pixmapItem->setTransformationMode(Qt::SmoothTransformation);
            this->doUpdate();
        }
    }

    ::scene2D::data::Coord coord = this->getScene2DRender()->mapToScene( _event->getCoord() );
    coord.setX( coord.getX() / m_layer->scale());
    coord.setY( coord.getY() / m_layer->scale());

    if ( _event->getType() == ::scene2D::data::Event::MouseButtonPress
            && _event->getButton() == ::scene2D::data::Event::RightButton
            && _event->getModifier() == ::scene2D::data::Event::NoModifier )
    {
        m_pointIsCaptured = true;
        m_oldCoord = _event->getCoord();
        _event->setAccepted(true);
    }
    else if ( m_pointIsCaptured )
    {
        if( _event->getType() == ::scene2D::data::Event::MouseMove )
        {
            ::scene2D::data::Coord newCoord = _event->getCoord();
            this->changeImageMinMaxFromCoord( m_oldCoord, newCoord );
            m_oldCoord = newCoord;
            _event->setAccepted(true);
        }
        else if( _event->getButton() == ::scene2D::data::Event::RightButton
                && _event->getType() == ::scene2D::data::Event::MouseButtonRelease )
        {
            m_pointIsCaptured = false;
            _event->setAccepted(true);
        }
    }
}

//-----------------------------------------------------------------------------

void Negato::changeImageMinMaxFromCoord( scene2D::data::Coord & oldCoord, scene2D::data::Coord & newCoord )
{
    ::fwData::Image::sptr image = this->getObject< ::fwData::Image >();
    ::fwData::TransferFunction::sptr tf = this->getTransferFunction();

    double min = tf->getWLMinMax().first;
    double max = tf->getWLMinMax().second;

    double window = newCoord.getX() - m_oldCoord.getX();
    double level = newCoord.getY() - m_oldCoord.getY();

    double imgWindow = max - min;
    double imgLevel = min + imgWindow/2.0;


    double newImgLevel = imgLevel + level;
    double newImgWindow = imgWindow + imgWindow * window/100.0;

    double newMin = newImgLevel - newImgWindow/2.0;
    double newMax = newImgLevel + newImgWindow/2.0;

    this->doUpdate();

    // Fire the message
    this->setWindowLevel(newMin, newMax);
    this->notifyTFWindowing(this->getSptr());
}

//-----------------------------------------------------------------------------

} // namespace adaptor
} // namespace scene2D



