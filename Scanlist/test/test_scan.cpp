#include "gtest/gtest.h"

#include "Scan.h"
#include "test_scan.h"
#include <iostream>

TEST(ScanSetup, ScanNumber)
{
    Scan scan = Scan(5432);
    EXPECT_EQ(5432, scan.getSerialNumber());
}

TEST(ScanSetup, ZeroTimesRecycled)
{
    Scan scan = Scan(5432);
    EXPECT_EQ(0, scan.getTimesRecycled());
}

TEST_F(ScanTest, Recycle)
{
    for (int i = 0; i < 10; i++)
    {
        scan->recycle();
    }
    ASSERT_EQ(10, scan->getTimesRecycled());
}

TEST_F(ScanTest, SetNext)
{
    Scan next = Scan(542);
    scan->setNext(&next);
    ASSERT_EQ(&next, scan->getNext());
}

TEST_F(ScanTest, SetNextDataIntact)
{
    Scan next = Scan(542);
    scan->setNext(&next);
    ASSERT_EQ(542, scan->getNext()->getSerialNumber());
}
