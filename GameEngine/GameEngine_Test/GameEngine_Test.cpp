// GameEngine_Test.cpp : Defines the entry point for the console application.
//

#include "gtest/gtest.h"
#include <iostream>

TEST(testEq, myFirstTest) {
	EXPECT_EQ(1000, 1000);
	EXPECT_EQ(90, 90);
}

TEST(testEq, mySecondTest) {
	EXPECT_EQ(5, 1);
}
