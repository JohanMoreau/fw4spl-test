/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2012.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include <fwData/location/SingleFile.hpp>
#include <fwCamp/UserObject.hpp>

fwCampImplementDataMacro((fwData)(location)(SingleFile))
{
    builder.base< ::fwData::Object>()
        .tag("object_version", "1")
        .tag("lib_name", "fwData")
        .property("path", &::fwData::location::SingleFile::m_path)
        ;
}
