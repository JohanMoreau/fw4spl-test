/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2012.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef _FWGUI_FWMENUBAR_HPP_
#define _FWGUI_FWMENUBAR_HPP_

#include "fwGui/GuiBaseObject.hpp"
#include "fwGui/config.hpp"

namespace fwGui
{
namespace container
{
/**
 * @brief   Defines the menu bar for IHM.
 * @class   fwMenuBar
 * 
 * @date    2009-2010.
 *
 */
class FWGUI_CLASS_API fwMenuBar : public ::fwGui::GuiBaseObject
{

public:

    fwCoreNonInstanciableClassDefinitionsMacro ( (fwMenuBar)(::fwGui::GuiBaseObject) ) ;

    FWGUI_API virtual void clean() = 0;
    FWGUI_API virtual void destroyContainer() = 0;

};
} // namespace container
} // namespace fwGui

#endif /*_FWGUI_FWMENUBAR_HPP_*/


