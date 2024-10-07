#include "../BitArray.h"
#include <gtest/gtest.h>

TEST(BitArray, swap)
{
    BitArray bitArray1(4, 1);
    BitArray bitArray2(4, 0);
    bitArray1.swap(bitArray2);
    ASSERT_EQ(bitArray1.toString(), "0000");
    ASSERT_EQ(bitArray2.toString(), "1111");
}

TEST(BitArray, AssignmentOperator)
{
    BitArray bitArray1(4, 1);
    BitArray bitArray2(10, 1);
    bitArray1 = bitArray2;
    ASSERT_EQ(bitArray1.size(), 10);
    ASSERT_EQ(bitArray1.toString(), "1111000000");
}

TEST(BitArray, resizeH)
{
    BitArray bitArray(4, 1);
    bitArray.resize(10);
    ASSERT_EQ(bitArray.toString(), "1111000000");
    ASSERT_EQ(bitArray.size(), 10);
}

TEST(BitArray, resizeL)
{
    BitArray bitArray(8, 1);
    bitArray.resize(4);
    ASSERT_EQ(bitArray.toString(), "1111");
    ASSERT_EQ(bitArray.size(), 4);
}

TEST(BitArray, clear)
{
    BitArray bitArray(4, 1);
    ASSERT_EQ(bitArray.toString(), "1111");
    ASSERT_EQ(bitArray.size(), 4);
    bitArray.clear();
    ASSERT_EQ(bitArray.toString(), "");
    ASSERT_EQ(bitArray.size(), 0);
}
