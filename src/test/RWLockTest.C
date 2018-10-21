#include "RWLock.h"
#include <iostream>
#include <gtest/gtest.h>


using namespace std;


/**
 * RWLock is not a recursive lock. If a thread attempts to aquire the lock
 * when it already has it, it will deadlock waiting for itself to release
 * the lock. That said, to simplify initial testing try_lock() is used in
 * a sigle thread to verify if it would have been able to get the lock
 * when it already has it for either read or write. This is possible since
 * RWLock is not aware of which thread is requesting the lock, but it should
 * not be done in production code.
 */


TEST(RWLockTest, thereCanBeMoreThanOneReader)
{
    auto rwlock = RWLock{};
    auto rlock = read_lock{rwlock};

    auto lock = lock_guard{rlock};
    ASSERT_EQ(true, rlock.try_lock());
}

TEST(RWLockTest, thereCanBeOnlyOneWriter)
{
    auto rwlock = RWLock{};
    auto wlock = write_lock{rwlock};

    auto lock = lock_guard{wlock};
    ASSERT_EQ(false, wlock.try_lock());
}

TEST(RWLockTest, aWriterCanGetTheLockIfThereAreReaders)
{
    auto rwlock = RWLock{};
    auto wlock = write_lock{rwlock};
    auto rlock = read_lock{rwlock};

    auto lock = lock_guard{rlock};
    ASSERT_EQ(false, wlock.try_lock());
}
