/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2012.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef _FWRUNTIME_PROFILE_INITIALIZER_HPP_
#define _FWRUNTIME_PROFILE_INITIALIZER_HPP_

#include <string>
#include <boost/utility.hpp>

#include "fwRuntime/config.hpp"


namespace fwRuntime
{

namespace profile
{



/**
 * @brief   Starts a given bundle.
 * @class  Initializer
 * @date    2007-2009
 * 
 */
class Initializer : public boost::noncopyable
{

public:

    /**
     * @brief       Constructor
     *
     * @param[in]   identifier  a string containing a bundle identifier
     */
    FWRUNTIME_API Initializer( const std::string & identifier );

    /**
     * @brief   Applies the initializer on the bundle.
     *
     * @remark  This method should be called directly.
     */
    void apply();


protected:

    const std::string   m_identifier;   ///< a bundle identifier

};



} // namespace profile

} // namespace fwRuntime



#endif /*_FWRUNTIME_PROFILE_INITIALIZER_HPP_*/
