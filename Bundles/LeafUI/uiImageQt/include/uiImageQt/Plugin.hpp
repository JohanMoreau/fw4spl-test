/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2012.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef _UIIMAGEQT_PLUGIN_HPP_
#define _UIIMAGEQT_PLUGIN_HPP_

#include <fwRuntime/Plugin.hpp>

namespace uiImage
{
/**
 * @namespace uiImage
 * @brief   Contains editors attached to image.
 * 
 * @date    2009.
 */
struct Plugin : public ::fwRuntime::Plugin
{
    /**
     * @brief   destructor
     */
    ~Plugin() throw();

    // Overrides
    void start() throw(::fwRuntime::RuntimeException);

    // Overrides
    void stop() throw();

};

} // namespace uiImage

#endif //_UIIMAGEQT_PLUGIN_HPP_
