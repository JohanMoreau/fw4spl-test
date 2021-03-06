/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2012.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __FWCAMP_VALUEMAPPER_HPP__
#define __FWCAMP_VALUEMAPPER_HPP__

#include <boost/lexical_cast.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <camp/valuemapper.hpp>
#include <camp/type.hpp>
#include <camp/camptype.hpp>

namespace camp_ext
{

template <>
struct ValueMapper< ::boost::uint64_t>
{
    // The corresponding CAMP type is "string"
    static const int type = camp::intType;

    // Convert from MyStringClass to std::string
    static std::string to(const ::boost::uint64_t& source)
    {
        return boost::lexical_cast<std::string>(source);
    }

    // Convert from any type to MyStringClass
    // Be smart, just reuse ValueMapper<std::string> :)
    template <typename T>
    static ::boost::uint64_t from(const T& source)
    {
        return boost::lexical_cast< ::boost::uint64_t>(source);
    }
};

//-----------------------------------------------------------------------------

template<typename T>
struct wrapperTribbol
{
    static ::boost::logic::tribool get(const T& source)
    {
        return ::boost::logic::tribool();
    }
};

//-----------------------------------------------------------------------------

template<>
struct wrapperTribbol<std::string >
{
    static ::boost::logic::tribool get(const std::string& source)
    {
        ::boost::logic::tribool value;

        if (source.compare("true") == 0)
        {
            value = true;
        }
        else if (source.compare("false") == 0)
        {
            value = false;
        }
        else
        {
            value = boost::logic::indeterminate;
        }

        return value;
    }
};

//-----------------------------------------------------------------------------

template <>
struct ValueMapper< ::boost::logic::tribool>
{
    // The corresponding CAMP type is "string"
    static const int type = camp::stringType;

    // Convert from MyStringClass to std::string
    static std::string to(const ::boost::logic::tribool& source)
    {
        std::string value;

        if (source)
        {
            value = "true";
        }
        else if (!source)
        {
            value = "false";
        }
        else
        {
            value = "indeterminate";
        }
        return value;
    }
    template <typename T>
    static ::boost::logic::tribool from(const T& source)
    {
        return wrapperTribbol<T>::get(source);;
    }
};

//-----------------------------------------------------------------------------

template <>
struct ValueMapper< ::boost::posix_time::ptime >
{
    typedef boost::posix_time::ptime ReturnType;
    static const int type = camp::stringType;
    static const std::string to(const ReturnType& source)
    {
        return boost::posix_time::to_simple_string(source);
    }

    static ReturnType from(bool source)                    {CAMP_ERROR(camp::BadType(camp::boolType, camp::mapType<ReturnType>()));}
    static ReturnType from(long source)                    {CAMP_ERROR(camp::BadType(camp::intType, camp::mapType<ReturnType>()));}
    static ReturnType from(double source)                  {CAMP_ERROR(camp::BadType(camp::realType, camp::mapType<ReturnType>()));}
    static ReturnType from(const camp::EnumObject& source) {CAMP_ERROR(camp::BadType(camp::enumType, camp::mapType<ReturnType>()));}
    static ReturnType from(const camp::UserObject& source) {CAMP_ERROR(camp::BadType(camp::userType, camp::mapType<ReturnType>()));}
    static ReturnType from(const std::string& source)
    {
        return boost::posix_time::time_from_string(source);
    }
};

//-----------------------------------------------------------------------------

template <>
struct ValueMapper< ::boost::filesystem::path >
{
    typedef ::boost::filesystem::path ReturnType;
    static const int type = camp::stringType;
    static const std::string to(const ReturnType& source)
    {
        return source.string();
    }

    static ReturnType from(bool source)
    {
        CAMP_ERROR(camp::BadType(camp::boolType, camp::mapType<ReturnType>()));
    }
    static ReturnType from(long source)
    {
        CAMP_ERROR(camp::BadType(camp::intType, camp::mapType<ReturnType>()));
    }
    static ReturnType from(double source)
    {
        CAMP_ERROR(camp::BadType(camp::realType, camp::mapType<ReturnType>()));
    }
    static ReturnType from(const camp::EnumObject& source)
    {
        CAMP_ERROR(camp::BadType(camp::enumType, camp::mapType<ReturnType>()));
    }
    static ReturnType from(const camp::UserObject& source)
    {
        CAMP_ERROR(camp::BadType(camp::userType, camp::mapType<ReturnType>()));
    }
    static ReturnType from(const std::string& source)
    {
        return ::boost::filesystem::path(source);
    }
};

//-----------------------------------------------------------------------------

/*
 * Specialization of ValueMapper for unsigned char
 */
template <>
struct ValueMapper<unsigned char>
{
    static const int type = camp::stringType;
    static std::string to(unsigned char source)
    {
        unsigned int intValue = boost::numeric_cast<unsigned int>(source);;

        return boost::lexical_cast<std::string>(intValue);
    }

    static unsigned char from(bool source)                    {return static_cast<unsigned char>(source);}
    static unsigned char from(long source)                    {return static_cast<unsigned char>(source);}
    static unsigned char from(double source)                  {return static_cast<unsigned char>(source);}
    static unsigned char from(const std::string& source)
    {
        unsigned int intValue = boost::lexical_cast<unsigned int>(source);
        return boost::numeric_cast<unsigned char>(intValue);
    }
    static unsigned char from(const camp::EnumObject& source) {return static_cast<unsigned char>(source.value());}
    static unsigned char from(const camp::UserObject&)        {CAMP_ERROR(camp::BadType(camp::userType, camp::realType));}
};

//-----------------------------------------------------------------------------

template <typename T>
struct ValueMapper<boost::shared_ptr<T> >
{
    typedef boost::shared_ptr<T> ReturnType;
    static const int type = camp::userType;
    static const camp::UserObject to(const ReturnType& source)
    {
        return camp::UserObject(source);
    }

    static ReturnType from(bool source)
    {
        CAMP_ERROR(camp::BadType(camp::boolType, camp::mapType<ReturnType>()));
    }
    static ReturnType from(long source)
    {
        CAMP_ERROR(camp::BadType(camp::intType, camp::mapType<ReturnType>()));
    }
    static ReturnType from(double source)
    {
        CAMP_ERROR(camp::BadType(camp::realType, camp::mapType<ReturnType>()));
    }
    static ReturnType from(const std::string& source)
    {
        CAMP_ERROR(camp::BadType(camp::stringType, camp::mapType<ReturnType>()));
    }
    static ReturnType from(const camp::EnumObject& source)
    {
        CAMP_ERROR(camp::BadType(camp::enumType, camp::mapType<ReturnType>()));
    }
    static ReturnType from(const camp::UserObject& source)
    {
        ReturnType result;
        try
        {
            T* ptr = source.get< T* >();
            result = T::dynamicCast(ptr->getSptr());
        }
        catch(...)
        {
            boost::shared_ptr<T> tmp;
            return tmp;
        }
        return result;
    }
};
}  // namespace camp_ext

#endif /* __FWCAMP_VALUEMAPPER_HPP__ */

