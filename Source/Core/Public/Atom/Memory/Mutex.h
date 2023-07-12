#pragma once
#include <mutex>

#include "Atom/Core.h"
#include "Atom/Memory/Lockable.h"

namespace Atom
{
    /// --------------------------------------------------------------------------------------------
    /// SimpleMutex implementation.
    /// 
    /// @TODO Implement this class without {std::lock}.
    /// --------------------------------------------------------------------------------------------
    class SimpleMutex
    {
    public:
        /// ----------------------------------------------------------------------------------------
        /// DefaultConstructor.
        /// 
        /// @POST Mutex is not locked.
        /// ----------------------------------------------------------------------------------------
        SimpleMutex() noex { }

        /// ----------------------------------------------------------------------------------------
        /// CopyConstructor is deleted.
        /// ----------------------------------------------------------------------------------------
        SimpleMutex(const SimpleMutex& other) = delete;

        /// ----------------------------------------------------------------------------------------
        /// MoveConstructor is delete.
        /// ----------------------------------------------------------------------------------------
        SimpleMutex(SimpleMutex&& other) = delete;

        /// ----------------------------------------------------------------------------------------
        /// CopyOperator is deleted.
        /// ----------------------------------------------------------------------------------------
        SimpleMutex& operator = (const SimpleMutex& other) = delete;

        /// ----------------------------------------------------------------------------------------
        /// MoveOperator is delete.
        /// ----------------------------------------------------------------------------------------
        SimpleMutex& operator = (SimpleMutex&& other) = delete;

        /// ----------------------------------------------------------------------------------------
        /// Destructor.
        /// 
        /// @NOTE If lock is locked by some thread and lock is destroyed, behaviour is undefined.
        /// ----------------------------------------------------------------------------------------
        ~SimpleMutex() { }

    public:
        /// ----------------------------------------------------------------------------------------
        /// Locks the lock. If the lock is already locked by some thread then blocks the calling
        /// thread until lock is acquired.
        /// 
        /// @SEE TryLock().
        /// ----------------------------------------------------------------------------------------
        void Lock()
        {
            _impl.lock();
        }

        /// ----------------------------------------------------------------------------------------
        /// Tries to lock the lock. If the lock is already locked by some thread then returns but 
        /// doesn't blocks the thread.
        /// 
        /// @RETURNS {true} if lock acquired, else {false}.
        /// ----------------------------------------------------------------------------------------
        bool TryLock()
        {
            return _impl.try_lock();
        }

        /// ----------------------------------------------------------------------------------------
        /// Unlocks the lock.
        /// ----------------------------------------------------------------------------------------
        void Unlock()
        {
            _impl.unlock();
        }

    private:
        /// ----------------------------------------------------------------------------------------
        /// Mutex implementation.
        /// ----------------------------------------------------------------------------------------
        std::mutex _impl;
    };

    static_assert(RLockable<SimpleMutex>);
}