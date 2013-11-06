#include <iostream>
#include <string>
#include "gtest/gtest.h"

/* Tests launcher, no need to edit for the basic case */

using namespace std;

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
