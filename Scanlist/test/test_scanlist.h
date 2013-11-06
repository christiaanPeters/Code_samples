#pragma once
#include "ScanList.h"
#include "Scan.h"

class ScanlistTest : public ::testing::Test {
public:
    void SetUp()
    {
        scanlist = new ScanList();
        for (int i = 10; i > 0; i--)
        {
            scanlist->AddScan(i);
        }
    }

    void TearDown()
    {
        delete scanlist;
    }
protected:
    ScanList *scanlist;
};
