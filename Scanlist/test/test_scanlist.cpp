#include "gtest/gtest.h"

#include "ScanList.h"
#include "test_scanlist.h"
#include <iostream>

TEST_F(ScanlistTest, EnoughScansPresent)
{
    for (int i = 0; i < 10; i++)
    {
        ASSERT_NE((Scan*)NULL, scanlist->getScanByNr(i));
    }
}

TEST_F(ScanlistTest, NotTooManyScans)
{
    for (int i = 10; i < 20; i++)
    {
        ASSERT_EQ((Scan*)NULL, scanlist->getScanByNr(i));
    }
}

TEST_F(ScanlistTest, ScansOrdered)
{
    for (int i = 0; i < 10; i++)
    {
        ASSERT_EQ(scanlist->getScanByNr(i)->getSerialNumber(), i + 1);
    }
}

TEST_F(ScanlistTest, Recycling)
{
    scanlist->AddScan(3);
    EXPECT_EQ(1, scanlist->getTimesRecycled(3));
    scanlist->AddScan(3);
    EXPECT_EQ(2, scanlist->getTimesRecycled(3));
}

TEST_F(ScanlistTest, Removal)
{
    scanlist->AddScan(3);
    scanlist->RemoveScan(3);
    ASSERT_EQ(0, scanlist->getTimesRecycled(3));
}
