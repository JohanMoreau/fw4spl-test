/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2013.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __IOVTK_SMODELSERIESWRITER_HPP__
#define __IOVTK_SMODELSERIESWRITER_HPP__

#include <string>
#include <boost/filesystem/path.hpp>

#include <fwServices/ObjectMsg.hpp>
#include <fwData/Mesh.hpp>

#include <io/IWriter.hpp>

#include "ioVTK/export.hpp"

namespace fwData
{
    class Mesh;
}

namespace ioVTK
{

/**
 * @brief   Model series writer service.
 * @class   SModelSeriesWriter
 *
 * Service writing a model series as .vtk files using the fwVtkIO lib.
 */
class IOVTK_CLASS_API SModelSeriesWriter : public ::io::IWriter
{

public :
    ~SModelSeriesWriter() throw() {}

    fwCoreServiceClassDefinitionsMacro ( (SModelSeriesWriter)( ::io::IWriter) ) ;

    /**
     * @brief Configure the mesh path.
     *
     * This method is used to find the file path  using a file selector.
     */
    IOVTK_API virtual void configureWithIHM();


protected:

    IOVTK_API virtual ::io::IOPathType getIOPathType() const;

    /**
     * @brief Starting method.
     *
     * This method is used to initialize the service.
     */
    IOVTK_API virtual void starting() throw(::fwTools::Failed);

    /**
     * @brief Stopping method.
     *
     * The stopping method is empty for this service.
     */
    IOVTK_API virtual void stopping() throw(::fwTools::Failed);

    /**
     * @brief Updating method.
     *
     * This method is used to update the service.
     * The mesh is read.
     */
    IOVTK_API void updating() throw(::fwTools::Failed);

    /**
     * @brief React on modifications : default does nothing.
     *
     * @note This method is automatically called by update( msg ) method from base service ( ::fwServices::IService ).
     *
     * @param[in] _msg information message for modification
     */
    void receiving( CSPTR(::fwServices::ObjectMsg) _msg ) throw(::fwTools::Failed){};

    /**
     * @brief Info method.
     *
     * This method is used to give
     * informations about the service.
     */
    IOVTK_API void info(std::ostream &_sstream ) ;

};

} // namespace ioVTK

#endif //__IOVTK_SMODELSERIESWRITER_HPP__

