#pragma once
#include "Scan.h"

class ScanTest : public ::testing::Test {
public:
    void SetUp()
    {
        scan = new Scan(1234);
    }

    void TearDown()
    {
        delete scan;
    }

protected:
    Scan *scan;
};
