/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2012.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef _FWDATAIO_READER_IOBJECTREADER_HPP_
#define _FWDATAIO_READER_IOBJECTREADER_HPP_

#include <boost/filesystem/path.hpp>

#include <fwCore/base.hpp>

#include <fwTools/Object.hpp>

#include <fwData/location/ILocation.hpp>

#include "fwDataIO/config.hpp"
#include "fwDataIO/reader/factory/new.hpp"
#include "fwDataIO/reader/registry/detail.hpp"

namespace fwDataIO
{

namespace reader
{

/**
 * @brief   Base class for all object readers.
 * @class   IObjectReader
 * 
 * @date    2009
 *
 * This class defines the API to use basic object readers. This reader is not
 * service. Their equivalent exist as services see ::io::IReader. To read an
 * object with this class, use setLocation and setOject method before execute
 * the method read. Reading modify the object given in parameter with the
 * method setOject.
 */
class FWDATAIO_CLASS_API IObjectReader : public ::fwCore::BaseObject
{

public :

    fwCoreNonInstanciableClassDefinitionsMacro( (IObjectReader) );

    typedef ::fwDataIO::reader::factory::Key Key;

    /**
     * @brief Class used to register a class factory in factory registry.
     * This class defines also the object factory ( 'create' )
     *
     * @tparam T Factory product type
     */
    template <typename T>
    class Registrar
    {
    public:
        Registrar()
        {
            ::fwDataIO::reader::registry::get()->addFactory(T::classname(), &::fwDataIO::reader::factory::New<T>);
        }
    };

    /**
     * @brief Defines an reader interface.
     *
     * This method (re)init the object given in parameter of setObject method.
     */
    FWDATAIO_API virtual void read() = 0;

    /**
     * @brief m_object setter.
     * @param[out] _pObject replace weakptr m_object of the instance reader
     * @note m_object is save in class with a weakptr
     * @note This object can be get with the method getObject()
     */
    FWDATAIO_API virtual void setObject( ::fwTools::Object::sptr _pObject );

    /**
     * @brief m_object getter.
     *
     * @return m_object
     * @note m_object is saved in reader with a weakptr
     */
    FWDATAIO_API virtual ::fwTools::Object::sptr getObject();

    /**
     * @brief m_location setter.
     * @param[in] _location set location where object will be read
     */
    FWDATAIO_API virtual void setLocation( const ::fwData::location::ILocation::sptr _location );

    /**
     * @brief m_location getter.
     *
     * @return m_location
     */
    FWDATAIO_API virtual ::fwData::location::ILocation::sptr getLocation();

    FWDATAIO_API virtual std::string  extension()=0;

protected :

    /// Constructor. Do nothing.
    FWDATAIO_API IObjectReader();

    /// Destructor. Do nothing.
    FWDATAIO_API virtual ~IObjectReader();

    /**
     * @brief Object result of reading process.
     *
     * This object is given in parameter of setObject method but it is conserved with a weakptr.
     */
    ::fwTools::Object::wptr m_object;

    /// Object location ( file path, directory path, url, etc )
    ::fwData::location::ILocation::sptr m_location;

};

} // namespace reader

} // namespace fwDataIO


#endif // _FWDATAIO_READER_IOBJECTREADER_HPP_
