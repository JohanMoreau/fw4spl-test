/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2012.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */


#include <fwServices/macros.hpp>

#include <vtkCubeSource.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>

#include "visuVTKAdaptor/Cube.hpp"



fwServicesRegisterMacro( ::fwRenderVTK::IVtkAdaptorService, ::visuVTKAdaptor::Cube, ::fwData::Object ) ;

namespace visuVTKAdaptor
{

void Cube::doStart() throw(fwTools::Failed)
{
    vtkCubeSource *cube = vtkCubeSource::New();
    vtkPolyDataMapper *mapper = vtkPolyDataMapper::New();
    mapper->SetInputConnection(cube->GetOutputPort());
    vtkActor *actor = vtkActor::New();
    actor->SetMapper(mapper);
    this->addToRenderer(actor);
    this->setVtkPipelineModified();
}


void Cube::doStop() throw(fwTools::Failed)
{
    this->removeAllPropFromRenderer();
}




} //namespace visuVTKAdaptor
