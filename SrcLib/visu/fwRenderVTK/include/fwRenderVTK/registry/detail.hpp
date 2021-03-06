/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2012.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __FWRENDERVTK_REGISTRY_DETAIL_HPP__
#define __FWRENDERVTK_REGISTRY_DETAIL_HPP__

#include <string>

#include <fwCore/macros.hpp>
#include <fwCore/util/FactoryRegistry.hpp>

#include "fwRenderVTK/config.hpp"

namespace fwRenderVTK
{

class IVtkRenderWindowInteractorManager;

namespace registry
{

typedef std::string KeyType;

typedef ::fwCore::util::FactoryRegistry< SPTR(::fwRenderVTK::IVtkRenderWindowInteractorManager) (), KeyType > Type;

FWRENDERVTK_API SPTR(Type) get();

} // namespace registry

} // namespace fwRenderVTK

#endif /* __FWRENDERVTK_REGISTRY_DETAIL_HPP__ */


