#include <gtest/gtest.h>
#include "../BitArray.h"

TEST(BitArray, swap)
{
    BitArray bitArray1(4, 1);
    BitArray bitArray2(4, 0);
    bitArray1.swap(bitArray2);
    ASSERT_EQ(bitArray1.toString(), "0000");
    ASSERT_EQ(bitArray2.toString(), "1111");
}

TEST(BitArray, AssignmentOperator){
    BitArray bitArray1(4, 1);
    BitArray bitArray2(10, 1);
    bitArray1 = bitArray2;
    ASSERT_EQ(bitArray1.size(), 10);
    ASSERT_EQ(bitArray1.toString(), "1111000000");
}