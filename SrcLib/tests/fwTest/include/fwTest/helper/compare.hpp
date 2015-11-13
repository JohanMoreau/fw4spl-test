/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __FWTEST_HELPER_COMPARE_HPP__
#define __FWTEST_HELPER_COMPARE_HPP__

#include "fwTest/config.hpp"

#include <fwCore/base.hpp>

#include <set>
#include <string>

namespace fwData
{
class Object;
}

namespace fwTest
{
namespace helper
{
typedef std::set<std::string> ExcludeSetType;

FWTEST_API bool compare(SPTR(::fwData::Object) objRef,
                        SPTR(::fwData::Object) objComp,
                        ExcludeSetType exclude = ExcludeSetType());

} // namespace helper
} // namespace fwTest

#endif // __FWTEST_HELPER_COMPARE_HPP__
