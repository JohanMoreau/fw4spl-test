/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __FWDATA_MATERIAL_HPP__
#define __FWDATA_MATERIAL_HPP__


#include "fwData/Object.hpp"
#include "fwData/Color.hpp"
#include "fwData/Image.hpp"
#include "fwData/factory/new.hpp"

fwCampAutoDeclareDataMacro((fwData)(Material), FWDATA_API);

namespace fwData
{

/**
 * @brief This class defines a material. A material is represented by an ambient color and a diffuse color.
 * @see ::fwData::Color
 */
class FWDATA_CLASS_API Material : public Object
{

public:

    fwCoreClassDefinitionsWithFactoryMacro( (Material)(::fwData::Object), (()), ::fwData::factory::New< Material >) ;
    fwCampMakeFriendDataMacro((fwData)(Material));


    /**
     * @brief Constructor
     * @param key Private construction key
     */
    FWDATA_API Material(::fwData::Object::Key key);

    /// Destructor
    FWDATA_API virtual ~Material();

    /// Defines shallow copy
    FWDATA_API void shallowCopy( const Object::csptr& _source );

    /// Defines deep copy
    FWDATA_API void cachedDeepCopy(const Object::csptr& _source, DeepCopyCacheType &cache);

    /**
    * @brief returns editable ambient color
    */
    FWDATA_API Color::sptr ambient() const;

    /**
     * @brief Setter for ambient color
     *
     * @param ambient color
     */
    FWDATA_API void setAmbient(Color::sptr ambient);

    /**
    * @brief returns editable diffuse color
    */
    FWDATA_API Color::sptr diffuse() const;

    /**
     * @brief Setter for diffuse color
     *
     * @param diffuse color
     */
    FWDATA_API void setDiffuse(Color::sptr diffuse);

    /**
    * @brief returns editable diffuse texture
    */
    FWDATA_API Image::sptr getDiffuseTexture() const;

    /**
     * @brief Setter for diffuse texture
     *
     * @param diffuseTexture texture
     */
    FWDATA_API void setDiffuseTexture(Image::sptr diffuseTexture);

    /**
     * @brief Options
     */
    typedef enum
    {
        MODE_STANDARD = 1,
        MODE_NORMALS  = 2,
    } OPTIONS_MODE;

    /**
     * @brief Shading models
     */
    typedef enum
    {
        MODE_FLAT    = 1,
        MODE_GOURAUD = 2,//MODE_FLAT<<1 -> 10
        MODE_PHONG   = 4,//MODE_FLAT<<2 -> 100
    } SHADING_MODE;

    /**
     * @brief Representation models
     */
    typedef enum
    {
        MODE_SURFACE   = 1, //1
        MODE_POINT     = 2, //MODE_SURFACE<<1 -> 10
        MODE_WIREFRAME = 4, //MODE_SURFACE<<2 -> 100
        MODE_EDGE      = 5, //MODE_SURFACE|MODE_WIREFRAME -> 101
    } REPRESENTATION_MODE;


    /**
     * @brief Texture filtering types
     */
    typedef enum
    {
        NEAREST,
        LINEAR,
    } FilteringType;

    /**
     * @brief Texture wrapping types
     */
    typedef enum
    {
        CLAMP,
        REPEAT,
    } WrappingType;

    fwGettersSettersDocMacro(ShadingMode, shadingMode, SHADING_MODE, the shading models(flat, gouraud, phong).);
    fwGettersSettersDocMacro(RepresentationMode, representationMode, REPRESENTATION_MODE, the representation models(edge, point, wireframe, surface).);
    fwGettersSettersDocMacro(OptionsMode, optionsMode, OPTIONS_MODE, the option representation (Standard, normals).);
    fwGettersSettersDocMacro(DiffuseTextureFiltering, diffuseTextureFiltering, FilteringType, the texture filtering.);
    fwGettersSettersDocMacro(DiffuseTextureWrapping, diffuseTextureWrapping, WrappingType, the texture wrapping.);

protected :

    /// Shading mode (flat, Gouraud, Phong)
    SHADING_MODE m_shadingMode;

    /// Fill mode (flat, wireframe, point)
    REPRESENTATION_MODE m_representationMode;

    /// Options mode (display normals or not)
    OPTIONS_MODE m_optionsMode;

    /// Ambient color
    Color::sptr m_ambient;

    /// Diffuse color
    Color::sptr m_diffuse;

    /// Diffuse texture
    Image::sptr m_diffuseTexture;

    /// Filtering for diffuse texture
    FilteringType m_diffuseTextureFiltering;

    /// Wrapping for diffuse texture
    WrappingType m_diffuseTextureWrapping;
};

} //namespace fwData

#endif /* __FWDATA_MATERIAL_HPP__ */

