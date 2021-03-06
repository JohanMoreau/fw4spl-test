/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2014.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef _FWDATA_MT_OBJECTREADLOCK_HPP_
#define _FWDATA_MT_OBJECTREADLOCK_HPP_

#include <fwCore/mt/types.hpp>

#include "fwData/Object.hpp"

#include "fwData/config.hpp"

namespace fwData
{
namespace mt
{

/**
 * @brief  A helper to lock object on read mode.
 */
class FWDATA_CLASS_API ObjectReadLock
{

public :

    /**
     * @brief Constructor : owns an read lock on object mutex.
     * If adopt_lock==false : the mutex is not locked (call lock() to lock mutex)
     */
    FWDATA_API ObjectReadLock( ::fwData::Object::sptr obj, bool lock=true );

    /// Destructor. Does nothing
    FWDATA_API ~ObjectReadLock();

    /// Adds read lock on object mutex
    FWDATA_API void lock();

    /// Releases lock on object mutex
    FWDATA_API void unlock();

private :

    /// lock on object mutex
    ::fwCore::mt::ReadLock m_lock;
};

} // mt
} // fwData

#endif // _FWDATA_MT_OBJECTREADLOCK_HPP_
