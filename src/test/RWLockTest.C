#include "RWLock.h"
#include <iostream>
#include <gtest/gtest.h>


using namespace std;


TEST(RWLockTest, multipleLockToRead)
{
    auto rwlock = RWLock{};
    auto r_lock = read_lock{rwlock};
    auto w_lock = write_lock{rwlock};

    auto lock = lock_guard{r_lock};
    ASSERT_EQ(true, rwlock.try_lock_to_read());
}


#if 0
int main()
{
    auto rwlock = RWLock{};
    auto r_lock = read_lock{rwlock};
    auto w_lock = write_lock{rwlock};

{
    auto lock = lock_guard{r_lock};
}

//    cout << rwlock.try_lock_to_read() << '\n';

    cout << rwlock.try_lock_to_write() << '\n';
}
#endif
