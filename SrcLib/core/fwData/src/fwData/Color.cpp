/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2014.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include <fwCore/base.hpp>
#include "fwData/registry/macros.hpp"
#include "fwData/Exception.hpp"



#include "fwData/Color.hpp"

fwDataRegisterMacro( ::fwData::Color );
namespace fwData
{
//------------------------------------------------------------------------------

Color::Color ( ::fwData::Object::Key key )
{
    m_vRGBA[0] = 1.0;
    m_vRGBA[1] = 1.0;
    m_vRGBA[2] = 1.0;
    m_vRGBA[3] = 1.0;
}

//------------------------------------------------------------------------------
Color::sptr Color::ColorFactory(Color::ColorType red, Color::ColorType green, Color::ColorType blue, Color::ColorType alpha)
{
    Color::sptr color = ::fwData::Color::New();
    color->m_vRGBA[0] = red;
    color->m_vRGBA[1] = green;
    color->m_vRGBA[2] = blue;
    color->m_vRGBA[3] = alpha;
    return color;
}

//------------------------------------------------------------------------------

Color::~Color ()
{
}


//------------------------------------------------------------------------------

void Color::shallowCopy(const Object::csptr &_source )
{
    Color::csptr other = Color::dynamicConstCast(_source);
    FW_RAISE_EXCEPTION_IF( ::fwData::Exception(
            "Unable to copy" + (_source?_source->getClassname():std::string("<NULL>"))
            + " to " + this->getClassname()), !bool(other) );
    this->fieldShallowCopy( _source );
    m_vRGBA = other->m_vRGBA;
}

//------------------------------------------------------------------------------

void Color::cachedDeepCopy(const Object::csptr &_source, DeepCopyCacheType &cache)
{
    Color::csptr other = Color::dynamicConstCast(_source);
    FW_RAISE_EXCEPTION_IF( ::fwData::Exception(
            "Unable to copy" + (_source?_source->getClassname():std::string("<NULL>"))
            + " to " + this->getClassname()), !bool(other) );
    this->fieldDeepCopy( _source, cache );
    m_vRGBA = other->m_vRGBA;
}

//------------------------------------------------------------------------------

void Color::setRGBA( const ColorType red, const ColorType green, const ColorType blue, const ColorType alpha )
{
    m_vRGBA[0] = red;
    m_vRGBA[1] = green;
    m_vRGBA[2] = blue;
    m_vRGBA[3] = alpha;
}

//------------------------------------------------------------------------------

void Color::setRGBA( std::string  hexaColor )
{
    OSLM_ASSERT(
            "Color string should start with '#' and followed by 6 ou 8 "
            "hexadecimal digits. Given color : " << hexaColor ,
            hexaColor[0] == '#'
                && ( hexaColor.length() == 7 || hexaColor.length() == 9)
            );

    std::string redString = hexaColor.substr(1, 2);
    std::string greenString = hexaColor.substr(3, 2);
    std::string blueString = hexaColor.substr(5, 2);
    int r,g,b, a = 255;

    std::istringstream iss;
    iss.str (redString);
    iss >> std::hex >> r;
    iss.clear();
    iss.str (greenString);
    iss >> std::hex >> g;
    iss.clear();
    iss.str (blueString);
    iss >> std::hex >> b;

    if (hexaColor.length() == 9)
    {
        std::string alphaString = hexaColor.substr(7, 2);
        iss.clear();
        iss.str (alphaString);
        iss >> std::hex >> a;
    }

    this->setRGBA(r/255.0f, g/255.0f, b/255.0f, a/255.0f);

}

//------------------------------------------------------------------------------

Color::ColorType  &Color::red()
{
    return m_vRGBA[0];
}
Color::ColorType  &Color::green()
{
    return m_vRGBA[1];
}
Color::ColorType  &Color::blue()
{
    return m_vRGBA[2];
}
Color::ColorType  &Color::alpha()
{
    return m_vRGBA[3];
}


const Color::ColorType  &Color::red() const
{
    return m_vRGBA[0];
}
const Color::ColorType  &Color::green() const
{
    return m_vRGBA[1];
}
const Color::ColorType  &Color::blue() const
{
    return m_vRGBA[2];
}
const Color::ColorType  &Color::alpha() const
{
    return m_vRGBA[3];
}

//------------------------------------------------------------------------------

} // namespace fwData


