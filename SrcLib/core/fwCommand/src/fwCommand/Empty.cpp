/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2012.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "fwCommand/Empty.hpp"

namespace fwCommand
{


//-----------------------------------------------------------------------------

const boost::uint32_t  Empty::getSize() const
{
    return sizeof(*this);
}

//-----------------------------------------------------------------------------

void Empty::apply()
{}

//-----------------------------------------------------------------------------

void Empty::unapply()
{}

//-----------------------------------------------------------------------------

const std::string Empty::getDescription() const
{
    return std::string("Empty command");
}

//-----------------------------------------------------------------------------

} // namespace fwCommand
