#include "../BitArray.h"
#include <gtest/gtest.h>
#include <typeinfo>

TEST(BitArray, DefaultConstructor)
{
    BitArray bitArray;
    ASSERT_EQ(bitArray.size(), 0);
    ASSERT_TRUE(bitArray.empty());
}

TEST(BitArray, ConstructorWithParameters)
{
    BitArray bitArray1(4, 2);
    ASSERT_EQ(bitArray1.toString(), "0010");
    ASSERT_EQ(bitArray1.size(), 4);
    BitArray bitArray2(8, 250);
    ASSERT_EQ(bitArray2.toString(), "11111010");
    ASSERT_EQ(bitArray2.size(), 8);
}

TEST(BitArray, CopyConstructor)
{
    BitArray bitArray1(4, 2);
    BitArray bitArray2(bitArray1);
    ASSERT_EQ(bitArray2.toString(), "0010");
    ASSERT_EQ(bitArray2.size(), 4);
}

TEST(BitArray, swap)
{
    BitArray bitArray1(4, 2);
    BitArray bitArray2(4, 1);
    bitArray1.swap(bitArray2);
    ASSERT_EQ(bitArray1.toString(), "0001");
    ASSERT_EQ(bitArray2.toString(), "0010");
}

TEST(BitArray, AssignmentOperator)
{
    BitArray bitArray1(4, 2);
    BitArray bitArray2;
    bitArray2 = bitArray1;
    ASSERT_EQ(bitArray2.toString(), "0010");
    ASSERT_EQ(bitArray2.size(), 4);
}

TEST(BitArray, resizeH)
{
    BitArray bitArray(4, 2);
    bitArray.resize(8, false);
    ASSERT_EQ(bitArray.toString(), "00100000");
    ASSERT_EQ(bitArray.size(), 8);
}

TEST(BitArray, resizeL)
{
    BitArray bitArray(8, 255);
    bitArray.resize(4);
    ASSERT_EQ(bitArray.toString(), "1111");
    ASSERT_EQ(bitArray.size(), 4);
}

TEST(BitArray, clear)
{
    BitArray bitArray(4, 1);
    ASSERT_EQ(bitArray.toString(), "0001");
    ASSERT_EQ(bitArray.size(), 4);
    bitArray.clear();
    ASSERT_EQ(bitArray.toString(), "");
    ASSERT_TRUE(bitArray.empty());
}

TEST(BitArray, pushBack)
{
    BitArray bitArray(7, 120);
    ASSERT_EQ(bitArray.toString(), "1111000");
    bitArray.pushBack(true);
    ASSERT_EQ(bitArray.toString(), "11110001");
    ASSERT_EQ(bitArray.size(), 8);
    bitArray.pushBack(false);
    ASSERT_EQ(bitArray.toString(), "111100010");
    ASSERT_EQ(bitArray.size(), 9);
}

TEST(BitArray, BitwiseANDAssignment)
{
    BitArray bitArray1(4, 2);
    BitArray bitArray2(4, 1);
    bitArray1 &= bitArray2;
    ASSERT_EQ(bitArray1.toString(), "0000");
}

TEST(BitArray, BitwiseORAssignment)
{
    BitArray bitArray1(4, 2);
    BitArray bitArray2(4, 1);
    bitArray1 |= bitArray2;
    ASSERT_EQ(bitArray1.toString(), "0011");
}

TEST(BitArray, BitwiseXORAssignment)
{
    BitArray bitArray1(4, 2);
    BitArray bitArray2(4, 1);
    bitArray1 ^= bitArray2;
    ASSERT_EQ(bitArray1.toString(), "0011");
}

TEST(BitArray, BitwiseLeftShiftAssignment)
{
    BitArray bitArray(4, 2);
    bitArray <<= 1;
    ASSERT_EQ(bitArray.toString(), "0100");
    bitArray <<= 2;
    ASSERT_EQ(bitArray.toString(), "0000");
}

TEST(BitArray, BitwiseRightShiftAssignment)
{
    BitArray bitArray(4, 2);
    bitArray >>= 1;
    ASSERT_EQ(bitArray.toString(), "0001");
}

TEST(BitArray, BitwiseLeftShift)
{
    BitArray bitArray(4, 2);
    BitArray result = bitArray << 1;
    ASSERT_EQ(result.toString(), "0100");
}

TEST(BitArray, BitwiseRightShift)
{
    BitArray bitArray(4, 2);
    BitArray result = bitArray >> 1;
    ASSERT_EQ(result.toString(), "0001");
}

TEST(BitArray, SetBit)
{
    BitArray bitArray(4, 0);
    bitArray.set(2, true);
    ASSERT_EQ(bitArray.toString(), "0010");
    ASSERT_EQ(bitArray.size(), 4);
    bitArray.set(2, false);
    bitArray.set(3, true);
    ASSERT_EQ(bitArray.size(), 4);
    ASSERT_EQ(bitArray.toString(), "0001");
}

TEST(BitArray, SetAllBits)
{
    BitArray bitArray(4, 0);
    bitArray.set();
    ASSERT_EQ(bitArray.toString(), "1111");
}

TEST(BitArray, ResetBit)
{
    BitArray bitArray(4, 15);
    bitArray.reset(2);
    ASSERT_EQ(bitArray.toString(), "1011");
}

TEST(BitArray, ResetAllBits)
{
    BitArray bitArray(4, 15);
    bitArray.reset();
    ASSERT_EQ(bitArray.toString(), "0000");
}

TEST(BitArray, Any)
{
    BitArray bitArray(4, 2);
    ASSERT_TRUE(bitArray.any());
    bitArray.reset();
    ASSERT_FALSE(bitArray.any());
}

TEST(BitArray, None)
{
    BitArray bitArray(4, 0);
    ASSERT_TRUE(bitArray.none());
    bitArray.set(2, true);
    ASSERT_FALSE(bitArray.none());
}

TEST(BitArray, BitwiseNOT)
{
    BitArray bitArray(4, 2);
    BitArray result = ~bitArray;
    ASSERT_EQ(result.toString(), "1101");
    bitArray.set();
    result = ~bitArray;
    ASSERT_FALSE(bitArray.any());
}

TEST(BitArray, Count)
{
    BitArray bitArray(8, 0);
    ASSERT_EQ(bitArray.count(), 0);
    bitArray.set();
    ASSERT_EQ(bitArray.count(), bitArray.size());
    bitArray.set(0, false);
    bitArray.set(1, false);
    bitArray.set(2, false);
    bitArray.set(3, false);
    ASSERT_EQ(bitArray.count(), 4);
}

TEST(BitArray, SubscriptOperator)
{
    BitArray bitArray(4, 2);
    bitArray[0] = true;
    ASSERT_EQ(bitArray.toString(), "1010");
    ASSERT_TRUE(bitArray[0]);
}

TEST(BitArray, size){
    BitArray bitArray1;
    ASSERT_EQ(bitArray1.size(), 0);
    BitArray bitArray2(4, 2);
    ASSERT_EQ(bitArray2.size(), 4);
    BitArray bitArray3;
    bitArray3.resize(10, false);
    ASSERT_EQ(bitArray3.size(), 10);
}

TEST(BitArray, empty){
    BitArray bitArray1;
    ASSERT_TRUE(bitArray1.empty());
    BitArray bitArray2(4, 2);
    ASSERT_FALSE(bitArray2.empty());
    BitArray bitArray3;
    bitArray3.resize(10, false);
    ASSERT_FALSE(bitArray3.empty());
    BitArray bitArray4(4, 2);
    bitArray4.clear();
    ASSERT_TRUE(bitArray4.empty());
}

TEST(BitArray, ToString){
    BitArray bitArray1;
    ASSERT_EQ(bitArray1.toString(), "");
    BitArray bitArray2(4, 2);
    ASSERT_EQ(bitArray2.toString(), "0010");
    BitArray bitArray3(4, 0);
    bitArray3.set(0, true);
    bitArray3.set(2, true);
    ASSERT_EQ(bitArray3.toString(), "0101");
    BitArray bitArray4(4, 15);
    ASSERT_EQ(bitArray4.toString(), "1111");
    BitArray bitArray5(4, 1);
    bitArray5.clear();
    ASSERT_EQ(bitArray5.toString(), "");
}

TEST(BitArray, EqualityOperator)
{
    BitArray bitArray1(4, 2);
    BitArray bitArray2(4, 2);
    ASSERT_TRUE(bitArray1 == bitArray2);
    BitArray bitArray3(4, 1);
    ASSERT_FALSE(bitArray1 == bitArray3);
}

TEST(BitArray, InequalityOperator)
{
    BitArray bitArray1(4, 2);
    BitArray bitArray2(8, 2);
    ASSERT_TRUE(bitArray1 != bitArray2);
    BitArray bitArray3(4, 1);
    ASSERT_TRUE(bitArray1 != bitArray3);
}

TEST(BitArray, BitwiseAND)
{
    BitArray bitArray1(4, 15);
    BitArray bitArray2(4, 1);
    BitArray result = bitArray1 & bitArray2;
    ASSERT_EQ(result.toString(), "0001");
}

TEST(BitArray, BitwiseOR)
{
    BitArray bitArray1(4, 2);
    BitArray bitArray2(4, 1);
    BitArray result = bitArray1 | bitArray2;
    ASSERT_EQ(result.toString(), "0011");
}

TEST(BitArray, BitwiseXOR)
{
    BitArray bitArray1(4, 2);
    BitArray bitArray2(4, 1);
    BitArray result = bitArray1 ^ bitArray2;
    ASSERT_EQ(result.toString(), "0011");
}
