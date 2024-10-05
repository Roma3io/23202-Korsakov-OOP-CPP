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
