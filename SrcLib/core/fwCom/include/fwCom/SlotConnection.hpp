/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2012.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */
#ifndef __FWCOM_SLOTCONNECTION_HPP__
#define __FWCOM_SLOTCONNECTION_HPP__

#include "fwCom/SlotConnectionBase.hpp"


namespace fwCom
{

template < typename F >
struct Signal;

template < typename F >
struct SlotConnection;

struct SlotBase;

/**
 * @brief Slot connection implementation.
 * This class is for internal use purpose.
 */
#ifdef BOOST_NO_VARIADIC_TEMPLATES
//===============================================================================
//===============================================================================
//==================================== BEGIN ====================================
template < typename A1, typename A2, typename A3, typename A4, typename A5 >
struct SlotConnection< void ( A1, A2, A3, A4, A5 ) > : SlotConnectionBase
{
    /**
     * @name Typedefs
     * @{ */
    typedef void SignatureType( A1, A2, A3, A4, A5 );
    typedef SlotConnection< SignatureType > SelfType;

    typedef SPTR( SelfType ) sptr;

    typedef Signal< SignatureType > SignalType;
    typedef SPTR( SignalType )      SignalSptrType;
    typedef WPTR( SignalType )      SignalWptrType;

    typedef SlotRun< SignatureType > SlotWrapperType;
    typedef SPTR( SlotWrapperType )  SlotWrapperSptrType;

    typedef SlotRun< SignatureType > SlotRunType;
    typedef SPTR( SlotRunType )      SlotRunSptrType;

    typedef std::pair< bool, SlotRunType* > PairType;
    /**  @} */

    /// Build a new connection with the given signal and slot.
    static sptr New( const SignalSptrType &signal, const SlotRunSptrType &slot );

    /// Build a new connection with the given signal, slot and wrapper.
    static sptr New( const SignalSptrType &signal,
                     const SPTR( SlotBase ) &slot,
                     const SlotWrapperSptrType &slotWrapper
                    );

    /// Disconnect the related slot.
    void disconnect();

    ~SlotConnection();


    /// Build a new connection with the given signal and slot.
    SlotConnection( const SignalSptrType &signal, const SlotRunSptrType &slot );

    /// Build a new connection with the given signal, slot and wrapper.
    SlotConnection( const SignalSptrType &signal,
                    const SPTR( SlotBase ) &slot,
                    const SlotWrapperSptrType &slotWrapper
                    );


protected:

    template < typename F >
    friend struct Signal;

    /// Connect the related Signal and Slot together.
    void connectNoLock();


    /// *NOT THREAD SAFE* Disconnect the related signal.
    void disconnectSignalNoLock(const SignalSptrType &sig);

    /// *NOT THREAD SAFE* Disconnect the related slot.
    void disconnectSlotNoLock(const SPTR( SlotBase ) &slot);

    /// *NOT THREAD SAFE* Disconnect the related slot and signal.
    void disconnectWeakLock();

    /**
     * @brief Returns a blocker on the connection.
     * The connection is blocked until the returned shared pointer dies.
     */
    SlotConnectionBase::BlockerSptrType getBlocker();

    /// Unblock this connection.
    void unblock();

    /// Related Signal.
    SignalWptrType m_signal;

    /// Related Slot.
    WPTR( SlotBase ) m_connectedSlot;

    /// Slot wrapper.
    SlotWrapperSptrType m_slotWrapper;

    /**
     * @brief Associates state of this connection to related Slot.
     * If m_pair.first is false, the connection is blocked.
     */
    PairType m_pair;

    /// Connection blocker.
    SlotConnectionBase::BlockerWptrType m_weakBlocker;

    mutable ::fwCore::mt::ReadWriteMutex m_mutex;
};
template < typename A1, typename A2, typename A3, typename A4 >
struct SlotConnection< void ( A1, A2, A3, A4 ) > : SlotConnectionBase
{
    /**
     * @name Typedefs
     * @{ */
    typedef void SignatureType( A1, A2, A3, A4 );
    typedef SlotConnection< SignatureType > SelfType;

    typedef SPTR( SelfType ) sptr;

    typedef Signal< SignatureType > SignalType;
    typedef SPTR( SignalType )      SignalSptrType;
    typedef WPTR( SignalType )      SignalWptrType;

    typedef SlotRun< SignatureType > SlotWrapperType;
    typedef SPTR( SlotWrapperType )  SlotWrapperSptrType;

    typedef SlotRun< SignatureType > SlotRunType;
    typedef SPTR( SlotRunType )      SlotRunSptrType;

    typedef std::pair< bool, SlotRunType* > PairType;
    /**  @} */

    /// Build a new connection with the given signal and slot.
    static sptr New( const SignalSptrType &signal, const SlotRunSptrType &slot );

    /// Build a new connection with the given signal, slot and wrapper.
    static sptr New( const SignalSptrType &signal,
                     const SPTR( SlotBase ) &slot,
                     const SlotWrapperSptrType &slotWrapper
                    );

    /// Disconnect the related slot.
    void disconnect();

    ~SlotConnection();


    /// Build a new connection with the given signal and slot.
    SlotConnection( const SignalSptrType &signal, const SlotRunSptrType &slot );

    /// Build a new connection with the given signal, slot and wrapper.
    SlotConnection( const SignalSptrType &signal,
                    const SPTR( SlotBase ) &slot,
                    const SlotWrapperSptrType &slotWrapper
                    );


protected:

    template < typename F >
    friend struct Signal;

    /// Connect the related Signal and Slot together.
    void connectNoLock();


    /// *NOT THREAD SAFE* Disconnect the related signal.
    void disconnectSignalNoLock(const SignalSptrType &sig);

    /// *NOT THREAD SAFE* Disconnect the related slot.
    void disconnectSlotNoLock(const SPTR( SlotBase ) &slot);

    /// *NOT THREAD SAFE* Disconnect the related slot and signal.
    void disconnectWeakLock();

    /**
     * @brief Returns a blocker on the connection.
     * The connection is blocked until the returned shared pointer dies.
     */
    SlotConnectionBase::BlockerSptrType getBlocker();

    /// Unblock this connection.
    void unblock();

    /// Related Signal.
    SignalWptrType m_signal;

    /// Related Slot.
    WPTR( SlotBase ) m_connectedSlot;

    /// Slot wrapper.
    SlotWrapperSptrType m_slotWrapper;

    /**
     * @brief Associates state of this connection to related Slot.
     * If m_pair.first is false, the connection is blocked.
     */
    PairType m_pair;

    /// Connection blocker.
    SlotConnectionBase::BlockerWptrType m_weakBlocker;

    mutable ::fwCore::mt::ReadWriteMutex m_mutex;
};
template < typename A1, typename A2, typename A3 >
struct SlotConnection< void ( A1, A2, A3 ) > : SlotConnectionBase
{
    /**
     * @name Typedefs
     * @{ */
    typedef void SignatureType( A1, A2, A3 );
    typedef SlotConnection< SignatureType > SelfType;

    typedef SPTR( SelfType ) sptr;

    typedef Signal< SignatureType > SignalType;
    typedef SPTR( SignalType )      SignalSptrType;
    typedef WPTR( SignalType )      SignalWptrType;

    typedef SlotRun< SignatureType > SlotWrapperType;
    typedef SPTR( SlotWrapperType )  SlotWrapperSptrType;

    typedef SlotRun< SignatureType > SlotRunType;
    typedef SPTR( SlotRunType )      SlotRunSptrType;

    typedef std::pair< bool, SlotRunType* > PairType;
    /**  @} */

    /// Build a new connection with the given signal and slot.
    static sptr New( const SignalSptrType &signal, const SlotRunSptrType &slot );

    /// Build a new connection with the given signal, slot and wrapper.
    static sptr New( const SignalSptrType &signal,
                     const SPTR( SlotBase ) &slot,
                     const SlotWrapperSptrType &slotWrapper
                    );

    /// Disconnect the related slot.
    void disconnect();

    ~SlotConnection();


    /// Build a new connection with the given signal and slot.
    SlotConnection( const SignalSptrType &signal, const SlotRunSptrType &slot );

    /// Build a new connection with the given signal, slot and wrapper.
    SlotConnection( const SignalSptrType &signal,
                    const SPTR( SlotBase ) &slot,
                    const SlotWrapperSptrType &slotWrapper
                    );


protected:

    template < typename F >
    friend struct Signal;

    /// Connect the related Signal and Slot together.
    void connectNoLock();


    /// *NOT THREAD SAFE* Disconnect the related signal.
    void disconnectSignalNoLock(const SignalSptrType &sig);

    /// *NOT THREAD SAFE* Disconnect the related slot.
    void disconnectSlotNoLock(const SPTR( SlotBase ) &slot);

    /// *NOT THREAD SAFE* Disconnect the related slot and signal.
    void disconnectWeakLock();

    /**
     * @brief Returns a blocker on the connection.
     * The connection is blocked until the returned shared pointer dies.
     */
    SlotConnectionBase::BlockerSptrType getBlocker();

    /// Unblock this connection.
    void unblock();

    /// Related Signal.
    SignalWptrType m_signal;

    /// Related Slot.
    WPTR( SlotBase ) m_connectedSlot;

    /// Slot wrapper.
    SlotWrapperSptrType m_slotWrapper;

    /**
     * @brief Associates state of this connection to related Slot.
     * If m_pair.first is false, the connection is blocked.
     */
    PairType m_pair;

    /// Connection blocker.
    SlotConnectionBase::BlockerWptrType m_weakBlocker;

    mutable ::fwCore::mt::ReadWriteMutex m_mutex;
};
template < typename A1, typename A2 >
struct SlotConnection< void ( A1, A2 ) > : SlotConnectionBase
{
    /**
     * @name Typedefs
     * @{ */
    typedef void SignatureType( A1, A2 );
    typedef SlotConnection< SignatureType > SelfType;

    typedef SPTR( SelfType ) sptr;

    typedef Signal< SignatureType > SignalType;
    typedef SPTR( SignalType )      SignalSptrType;
    typedef WPTR( SignalType )      SignalWptrType;

    typedef SlotRun< SignatureType > SlotWrapperType;
    typedef SPTR( SlotWrapperType )  SlotWrapperSptrType;

    typedef SlotRun< SignatureType > SlotRunType;
    typedef SPTR( SlotRunType )      SlotRunSptrType;

    typedef std::pair< bool, SlotRunType* > PairType;
    /**  @} */

    /// Build a new connection with the given signal and slot.
    static sptr New( const SignalSptrType &signal, const SlotRunSptrType &slot );

    /// Build a new connection with the given signal, slot and wrapper.
    static sptr New( const SignalSptrType &signal,
                     const SPTR( SlotBase ) &slot,
                     const SlotWrapperSptrType &slotWrapper
                    );

    /// Disconnect the related slot.
    void disconnect();

    ~SlotConnection();


    /// Build a new connection with the given signal and slot.
    SlotConnection( const SignalSptrType &signal, const SlotRunSptrType &slot );

    /// Build a new connection with the given signal, slot and wrapper.
    SlotConnection( const SignalSptrType &signal,
                    const SPTR( SlotBase ) &slot,
                    const SlotWrapperSptrType &slotWrapper
                    );


protected:

    template < typename F >
    friend struct Signal;

    /// Connect the related Signal and Slot together.
    void connectNoLock();


    /// *NOT THREAD SAFE* Disconnect the related signal.
    void disconnectSignalNoLock(const SignalSptrType &sig);

    /// *NOT THREAD SAFE* Disconnect the related slot.
    void disconnectSlotNoLock(const SPTR( SlotBase ) &slot);

    /// *NOT THREAD SAFE* Disconnect the related slot and signal.
    void disconnectWeakLock();

    /**
     * @brief Returns a blocker on the connection.
     * The connection is blocked until the returned shared pointer dies.
     */
    SlotConnectionBase::BlockerSptrType getBlocker();

    /// Unblock this connection.
    void unblock();

    /// Related Signal.
    SignalWptrType m_signal;

    /// Related Slot.
    WPTR( SlotBase ) m_connectedSlot;

    /// Slot wrapper.
    SlotWrapperSptrType m_slotWrapper;

    /**
     * @brief Associates state of this connection to related Slot.
     * If m_pair.first is false, the connection is blocked.
     */
    PairType m_pair;

    /// Connection blocker.
    SlotConnectionBase::BlockerWptrType m_weakBlocker;

    mutable ::fwCore::mt::ReadWriteMutex m_mutex;
};
template < typename A1 >
struct SlotConnection< void ( A1 ) > : SlotConnectionBase
{
    /**
     * @name Typedefs
     * @{ */
    typedef void SignatureType( A1 );
    typedef SlotConnection< SignatureType > SelfType;

    typedef SPTR( SelfType ) sptr;

    typedef Signal< SignatureType > SignalType;
    typedef SPTR( SignalType )      SignalSptrType;
    typedef WPTR( SignalType )      SignalWptrType;

    typedef SlotRun< SignatureType > SlotWrapperType;
    typedef SPTR( SlotWrapperType )  SlotWrapperSptrType;

    typedef SlotRun< SignatureType > SlotRunType;
    typedef SPTR( SlotRunType )      SlotRunSptrType;

    typedef std::pair< bool, SlotRunType* > PairType;
    /**  @} */

    /// Build a new connection with the given signal and slot.
    static sptr New( const SignalSptrType &signal, const SlotRunSptrType &slot );

    /// Build a new connection with the given signal, slot and wrapper.
    static sptr New( const SignalSptrType &signal,
                     const SPTR( SlotBase ) &slot,
                     const SlotWrapperSptrType &slotWrapper
                    );

    /// Disconnect the related slot.
    void disconnect();

    ~SlotConnection();


    /// Build a new connection with the given signal and slot.
    SlotConnection( const SignalSptrType &signal, const SlotRunSptrType &slot );

    /// Build a new connection with the given signal, slot and wrapper.
    SlotConnection( const SignalSptrType &signal,
                    const SPTR( SlotBase ) &slot,
                    const SlotWrapperSptrType &slotWrapper
                    );


protected:

    template < typename F >
    friend struct Signal;

    /// Connect the related Signal and Slot together.
    void connectNoLock();


    /// *NOT THREAD SAFE* Disconnect the related signal.
    void disconnectSignalNoLock(const SignalSptrType &sig);

    /// *NOT THREAD SAFE* Disconnect the related slot.
    void disconnectSlotNoLock(const SPTR( SlotBase ) &slot);

    /// *NOT THREAD SAFE* Disconnect the related slot and signal.
    void disconnectWeakLock();

    /**
     * @brief Returns a blocker on the connection.
     * The connection is blocked until the returned shared pointer dies.
     */
    SlotConnectionBase::BlockerSptrType getBlocker();

    /// Unblock this connection.
    void unblock();

    /// Related Signal.
    SignalWptrType m_signal;

    /// Related Slot.
    WPTR( SlotBase ) m_connectedSlot;

    /// Slot wrapper.
    SlotWrapperSptrType m_slotWrapper;

    /**
     * @brief Associates state of this connection to related Slot.
     * If m_pair.first is false, the connection is blocked.
     */
    PairType m_pair;

    /// Connection blocker.
    SlotConnectionBase::BlockerWptrType m_weakBlocker;

    mutable ::fwCore::mt::ReadWriteMutex m_mutex;
};
template <>
struct SlotConnection< void () > : SlotConnectionBase
{
    /**
     * @name Typedefs
     * @{ */
    typedef void SignatureType();
    typedef SlotConnection< SignatureType > SelfType;

    typedef SPTR( SelfType ) sptr;

    typedef Signal< SignatureType > SignalType;
    typedef SPTR( SignalType )      SignalSptrType;
    typedef WPTR( SignalType )      SignalWptrType;

    typedef SlotRun< SignatureType > SlotWrapperType;
    typedef SPTR( SlotWrapperType )  SlotWrapperSptrType;

    typedef SlotRun< SignatureType > SlotRunType;
    typedef SPTR( SlotRunType )      SlotRunSptrType;

    typedef std::pair< bool, SlotRunType* > PairType;
    /**  @} */

    /// Build a new connection with the given signal and slot.
    static sptr New( const SignalSptrType &signal, const SlotRunSptrType &slot );

    /// Build a new connection with the given signal, slot and wrapper.
    static sptr New( const SignalSptrType &signal,
                     const SPTR( SlotBase ) &slot,
                     const SlotWrapperSptrType &slotWrapper
                    );

    /// Disconnect the related slot.
    void disconnect();

    ~SlotConnection();


    /// Build a new connection with the given signal and slot.
    SlotConnection( const SignalSptrType &signal, const SlotRunSptrType &slot );

    /// Build a new connection with the given signal, slot and wrapper.
    SlotConnection( const SignalSptrType &signal,
                    const SPTR( SlotBase ) &slot,
                    const SlotWrapperSptrType &slotWrapper
                    );


protected:

    template < typename F >
    friend struct Signal;

    /// Connect the related Signal and Slot together.
    void connectNoLock();


    /// *NOT THREAD SAFE* Disconnect the related signal.
    void disconnectSignalNoLock(const SignalSptrType &sig);

    /// *NOT THREAD SAFE* Disconnect the related slot.
    void disconnectSlotNoLock(const SPTR( SlotBase ) &slot);

    /// *NOT THREAD SAFE* Disconnect the related slot and signal.
    void disconnectWeakLock();

    /**
     * @brief Returns a blocker on the connection.
     * The connection is blocked until the returned shared pointer dies.
     */
    SlotConnectionBase::BlockerSptrType getBlocker();

    /// Unblock this connection.
    void unblock();

    /// Related Signal.
    SignalWptrType m_signal;

    /// Related Slot.
    WPTR( SlotBase ) m_connectedSlot;

    /// Slot wrapper.
    SlotWrapperSptrType m_slotWrapper;

    /**
     * @brief Associates state of this connection to related Slot.
     * If m_pair.first is false, the connection is blocked.
     */
    PairType m_pair;

    /// Connection blocker.
    SlotConnectionBase::BlockerWptrType m_weakBlocker;

    mutable ::fwCore::mt::ReadWriteMutex m_mutex;
};
//===================================== END =====================================
//===============================================================================
//===============================================================================

#else  // BOOST_NO_VARIADIC_TEMPLATES
template < typename ...A >
struct SlotConnection< void (A...) > : SlotConnectionBase
{
    /**
     * @name Typedefs
     * @{ */
    typedef void SignatureType( A... );
    typedef SlotConnection< SignatureType > SelfType;

    typedef SPTR( SelfType ) sptr;

    typedef Signal< SignatureType > SignalType;
    typedef SPTR( SignalType )      SignalSptrType;
    typedef WPTR( SignalType )      SignalWptrType;

    typedef SlotRun< SignatureType > SlotWrapperType;
    typedef SPTR( SlotWrapperType )  SlotWrapperSptrType;

    typedef SlotRun< SignatureType > SlotRunType;
    typedef SPTR( SlotRunType )      SlotRunSptrType;

    typedef std::pair< bool, SlotRunType* > PairType;
    /**  @} */

    /// Build a new connection with the given signal and slot.
    static sptr New( const SignalSptrType &signal, const SlotRunSptrType &slot );

    /// Build a new connection with the given signal, slot and wrapper.
    static sptr New( const SignalSptrType &signal,
                     const SPTR( SlotBase ) &slot,
                     const SlotWrapperSptrType &slotWrapper
                    );

    /// Disconnect the related slot.
    void disconnect();

    ~SlotConnection();


    /// Build a new connection with the given signal and slot.
    SlotConnection( const SignalSptrType &signal, const SlotRunSptrType &slot );

    /// Build a new connection with the given signal, slot and wrapper.
    SlotConnection( const SignalSptrType &signal,
                    const SPTR( SlotBase ) &slot,
                    const SlotWrapperSptrType &slotWrapper
                    );


protected:

    template < typename F >
    friend struct Signal;

    /// Connect the related Signal and Slot together.
    void connectNoLock();


    /// *NOT THREAD SAFE* Disconnect the related signal.
    void disconnectSignalNoLock(const SignalSptrType &sig);

    /// *NOT THREAD SAFE* Disconnect the related slot.
    void disconnectSlotNoLock(const SPTR( SlotBase ) &slot);

    /// *NOT THREAD SAFE* Disconnect the related slot and signal.
    void disconnectWeakLock();

    /**
     * @brief Returns a blocker on the connection.
     * The connection is blocked until the returned shared pointer dies.
     */
    SlotConnectionBase::BlockerSptrType getBlocker();

    /// Unblock this connection.
    void unblock();

    /// Related Signal.
    SignalWptrType m_signal;

    /// Related Slot.
    WPTR( SlotBase ) m_connectedSlot;

    /// Slot wrapper.
    SlotWrapperSptrType m_slotWrapper;

    /**
     * @brief Associates state of this connection to related Slot.
     * If m_pair.first is false, the connection is blocked.
     */
    PairType m_pair;

    /// Connection blocker.
    SlotConnectionBase::BlockerWptrType m_weakBlocker;

    mutable ::fwCore::mt::ReadWriteMutex m_mutex;
};
#endif  // BOOST_NO_VARIADIC_TEMPLATES



} // namespace fwCom

#endif /* __FWCOM_SLOTCONNECTION_HPP__ */

