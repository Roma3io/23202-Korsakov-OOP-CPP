#include "BitArray.h"
#include <cstring>
#include <stdexcept>
#include <string>

/***************************************************************************
*   Method     : BitArray (default constructor)
*   Description: Default constructor. Initializes an empty BitArray with 0 bits.
*   Parameters : None
*   Returned   : None
***************************************************************************/
BitArray::BitArray() : numBits(0), data(nullptr) {}

/***************************************************************************
*   Method     : ~BitArray (destructor)
*   Description: Destructor. Default destructor for BitArray.
*   Parameters : None
*   Returned   : None
***************************************************************************/
BitArray::~BitArray()
{
        delete[] data;
}

/***************************************************************************
*   Method     : BitArray (constructor with initial size and value)
*   Description: Constructor with initial size and value. The first sizeof(long) bits can be initialized using the value parameter.
*   Parameters : numBits - The number of bits in the array.
*                value - The initial value to set the bits(for the first sizeof(long) bits).
*   Returned   : None
***************************************************************************/
BitArray::BitArray(int numBits, unsigned long value) : numBits(numBits)
{
    data = new char[(numBits + 7) / 8];
    for (int i = 0; i < sizeof(long) * 8 && i < numBits; ++i) {
        set(numBits - i - 1, (value >> i) & 1);
    }
}

/***************************************************************************
*   Method     : BitArray (copy constructor)
*   Description: Copy constructor. Initializes a BitArray by copying the contents of another BitArray.
*   Parameters : b - The BitArray to copy.
*   Returned   : None
***************************************************************************/
BitArray::BitArray(const BitArray &b)
{
    numBits = b.numBits;
    data = new char[(numBits + 7) / 8];
    std::memcpy(data, b.data, (numBits + 7) / 8 * sizeof(char));
}

/***************************************************************************
*   Method     : swap
*   Description: Swap function. Swaps the contents of this BitArray with another BitArray.
*   Parameters : b - The BitArray to swap with.
*   Returned   : None
***************************************************************************/
void BitArray::swap(BitArray &b)
{
    std::swap(data, b.data);
    std::swap(numBits, b.numBits);
}

/***************************************************************************
*   Method     : operator=
*   Description: Assignment operator. Assigns the contents of another BitArray to this BitArray.
*   Parameters : b - The BitArray to assign.
*   Returned   : A reference to this BitArray.
***************************************************************************/
BitArray &BitArray::operator=(const BitArray &b)
{
    if (this != &b) {
        delete[] data;
        numBits = b.numBits;
        data = new char[(numBits + 7) / 8];
        std::memcpy(data, b.data, (numBits + 7) / 8 * sizeof(char));
    }
    return *this;
}

/***************************************************************************
*   Method     : resize
*   Description: Resize function. Resizes the BitArray to the specified number of bits and sets the new bits to the specified value.
*   Parameters : numBits - The new number of bits.
*                value - The value to set the new bits.
*   Returned   : None
***************************************************************************/
void BitArray::resize(int numBits, bool value)
{
    int newSize = (numBits + 7) / 8;
    char *newData = new char[newSize];
    std::memset(newData, 0, newSize * sizeof(char));
    if (data) {
        std::memcpy(newData, data, std::min(newSize, (this->numBits + 7) / 8) * sizeof(char));
    }
    delete[] data;
    data = newData;
    for (int i = this->numBits; i < numBits; ++i) {
        set(i, value);
    }
    this->numBits = numBits;
}

/***************************************************************************
*   Method     : clear
*   Description: Clear function. Clears the BitArray, setting the number of bits to 0 and clearing the data.
*   Parameters : None
*   Returned   : None
***************************************************************************/
void BitArray::clear()
{
    delete[] data;
    data = nullptr;
    numBits = 0;
}

/***************************************************************************
*   Method     : pushBack
*   Description: Push back function. Adds a bit to the end of the BitArray.
*   Parameters : bit - The bit to add.
*   Returned   : None
***************************************************************************/
void BitArray::pushBack(bool bit)
{
    if (numBits % 8 == 0) {
        resize(numBits + 1);
        set(numBits, bit);
    } else {
        set(numBits, bit);
        numBits++;
    }
}

/***************************************************************************
*   Method     : operator&=
*   Description: Bitwise AND assignment operator. Performs a bitwise AND operation with another BitArray and assigns the result to this BitArray.
*   Parameters : b - The BitArray to perform the AND operation with.
*   Returned   : A reference to this BitArray.
***************************************************************************/
BitArray &BitArray::operator&=(const BitArray &b)
{
    if (numBits != b.numBits) {
        throw std::invalid_argument("Error: BitArrays must have the same size for bitwise AND operation");
    }
    for (int i = 0; i < numBits; ++i) {
        set(i, (*this)[i] & b[i]);
    }
    return *this;
}

/***************************************************************************
*   Method     : operator|=
*   Description: Bitwise OR assignment operator. Performs a bitwise OR operation with another BitArray and assigns the result to this BitArray.
*   Parameters : b - The BitArray to perform the OR operation with.
*   Returned   : A reference to this BitArray.
***************************************************************************/
BitArray &BitArray::operator|=(const BitArray &b)
{
    if (numBits != b.numBits) {
        throw std::invalid_argument("Error: BitArrays must have the same size for bitwise OR operation");
    }
    for (int i = 0; i < numBits; ++i) {
        set(i, (*this)[i] | b[i]);
    }
    return *this;
}

/***************************************************************************
*   Method     : operator^=
*   Description: Bitwise XOR assignment operator. Performs a bitwise XOR operation with another BitArray and assigns the result to this BitArray.
*   Parameters : b - The BitArray to perform the XOR operation with.
*   Returned   : A reference to this BitArray.
***************************************************************************/
BitArray &BitArray::operator^=(const BitArray &b)
{
    if (numBits != b.numBits) {
        throw std::invalid_argument("Error: BitArrays must have the same size for bitwise XOR operation");
    }
    for (int i = 0; i < numBits; i++) {
        set(i, (*this)[i] ^ b[i]);
    }
    return *this;
}

/***************************************************************************
*   Method     : operator<<=
*   Description: Bitwise left shift assignment operator. Performs a bitwise left shift operation on this BitArray.
*   Parameters : n - The number of bits to shift.
*   Returned   : A reference to this BitArray.
***************************************************************************/
BitArray &BitArray::operator<<=(int n)
{
    for (int i = 0; i < numBits - n; ++i) {
        set(i, (*this)[i + n]);
    }
    for (int i = numBits - n; i < numBits; ++i) {
        set(i, false);
    }
    return *this;
}

/***************************************************************************
*   Method     : operator>>=
*   Description: Bitwise right shift assignment operator. Performs a bitwise right shift operation on this BitArray.
*   Parameters : n - The number of bits to shift.
*   Returned   : A reference to this BitArray.
***************************************************************************/
BitArray &BitArray::operator>>=(int n)
{
    for (int i = numBits - 1; i >= n; i--) {
        set(i, (*this)[i - n]);
    }
    for (int i = 0; i < n; ++i) {
        set(i, false);
    }
    return *this;
}

/***************************************************************************
*   Method     : operator<<
*   Description: Bitwise left shift operator. Performs a bitwise left shift operation on this BitArray and returns the result as a new BitArray.
*   Parameters : n - The number of bits to shift.
*   Returned   : A new BitArray with the result of the shift.
***************************************************************************/
BitArray BitArray::operator<<(int n) const
{
    BitArray result(*this);
    result <<= n;
    return result;
}

/***************************************************************************
*   Method     : operator>>
*   Description: Bitwise right shift operator. Performs a bitwise right shift operation on this BitArray and returns the result as a new BitArray.
*   Parameters : n - The number of bits to shift.
*   Returned   : A new BitArray with the result of the shift.
***************************************************************************/
BitArray BitArray::operator>>(int n) const
{
    BitArray result(*this);
    result >>= n;
    return result;
}

/***************************************************************************
*   Method     : set
*   Description: Set function. Sets the bit at the specified index to the specified value.
*   Parameters : index - The index of the bit to set.
*                value - The value to set the bit to.
*   Returned   : A reference to this BitArray.
***************************************************************************/
BitArray &BitArray::set(int index, bool value)
{
    int byteIndex = index / 8;
    int bitIndex = index % 8;
    if (value) {
        data[byteIndex] |= (1 << bitIndex);
    } else {
        data[byteIndex] &= ~(1 << bitIndex);
    }
    return *this;
}

/***************************************************************************
*   Method     : set
*   Description: Set all bits function. Sets all bits in the BitArray to true.
*   Parameters : None
*   Returned   : A reference to this BitArray.
***************************************************************************/
BitArray &BitArray::set()
{
    for (int i = 0; i < numBits; i++) {
        set(i, true);
    }
    return *this;
}

/***************************************************************************
*   Method     : reset
*   Description: Reset function. Resets the bit at the specified index to false.
*   Parameters : index - The index of the bit to reset.
*   Returned   : A reference to this BitArray.
***************************************************************************/
BitArray &BitArray::reset(int index)
{
    set(index, false);
    return *this;
}

/***************************************************************************
*   Method     : reset
*   Description: Reset all bits function. Resets all bits in the BitArray to false.
*   Parameters : None
*   Returned   : A reference to this BitArray.
***************************************************************************/
BitArray &BitArray::reset()
{
    for (int i = 0; i < numBits; i++) {
        set(i, false);
    }
    return *this;
}

/***************************************************************************
*   Method     : any
*   Description: Any function. Checks if any bit in the BitArray is set to true.
*   Parameters : None
*   Returned   : True if any bit is set to true, false otherwise.
***************************************************************************/
bool BitArray::any() const
{
    for (int i = 0; i < numBits; i++) {
        if ((*this)[i])
            return true;
    }
    return false;
}

/***************************************************************************
*   Method     : none
*   Description: None function. Checks if no bits in the BitArray are set to true.
*   Parameters : None
*   Returned   : True if no bits are set to true, false otherwise.
***************************************************************************/
bool BitArray::none() const
{
    for (int i = 0; i < numBits; i++) {
        if ((*this)[i])
            return false;
    }
    return true;
}

/***************************************************************************
*   Method     : operator~
*   Description: Bitwise NOT operator. Performs a bitwise NOT operation on this BitArray and returns the result as a new BitArray.
*   Parameters : None
*   Returned   : A new BitArray with the result of the NOT operation.
***************************************************************************/
BitArray BitArray::operator~() const
{
    BitArray result(*this);
    for (int i = 0; i < numBits; ++i) {
        result.set(i, !(*this)[i]);
    }
    return result;
}

/***************************************************************************
*   Method     : count
*   Description: Count function. Counts the number of bits set to true in the BitArray.
*   Parameters : None
*   Returned   : The number of bits set to true.
***************************************************************************/
int BitArray::count() const
{
    int count = 0;
    for (int i = 0; i < numBits; i++) {
        if ((*this)[i]) {
            count++;
        }
    }
    return count;
}

/***************************************************************************
*   Method     : Wrapper (constructor)
*   Description: Wrapper constructor. Constructs a Wrapper object for accessing a bit in the BitArray.
*   Parameters : bitArray - The BitArray to access.
*                index - The index of the bit to access.
*   Returned   : None
***************************************************************************/
BitArray::Wrapper::Wrapper(BitArray &bitArray, int index) : bitArray(bitArray), index(index) {}

/***************************************************************************
*   Method     : operator[]
*   Description: Wrapper operator[]. Returns a Wrapper object.
*   Parameters : i - The index of the bit to access.
*   Returned   : A Wrapper object for accessing the bit.
***************************************************************************/
BitArray::Wrapper BitArray::operator[](int i)
{
    return Wrapper(*this, i);
}

/***************************************************************************
*   Method     : operator= (Wrapper)
*   Description: Wrapper assignment operator. Sets the bit at the specified index to the specified value.
*   Parameters : value - The value to set the bit to.
*   Returned   : A reference to the Wrapper object.
***************************************************************************/
BitArray::Wrapper &BitArray::Wrapper::operator=(bool value)
{
    bitArray.set(index, value);
    return *this;
}

/***************************************************************************
*   Method     : operator bool (Wrapper)
*   Description: Wrapper conversion operator. Converts the Wrapper object to a bool, representing the value of the bit.
*   Parameters : None
*   Returned   : The value of the bit.
***************************************************************************/
BitArray::Wrapper::operator bool() const
{
    int byteIndex = index / 8;
    int bitIndex = index % 8;
    return (bitArray.data[byteIndex] >> bitIndex) & 0x01;
}

/***************************************************************************
*   Method     : operator[] (const)
*   Description: Operator[] const. Returns the value of the bit at the specified index.
*   Parameters : i - The index of the bit to access.
*   Returned   : The value of the bit.
***************************************************************************/
bool BitArray::operator[](int i) const
{
    int byteIndex = i / 8;
    int bitIndex = i % 8;
    return (data[byteIndex] >> bitIndex) & 0x01;
}

/***************************************************************************
*   Method     : size
*   Description: Size function. Returns the number of bits in the BitArray.
*   Parameters : None
*   Returned   : The number of bits.
***************************************************************************/
int BitArray::size() const
{
    return numBits;
}

/***************************************************************************
*   Method     : empty
*   Description: Empty function. Checks if the BitArray is empty.
*   Parameters : None
*   Returned   : True if the BitArray is empty, false otherwise.
***************************************************************************/
bool BitArray::empty() const
{
    return numBits == 0;
}

/***************************************************************************
*   Method     : toString
*   Description: ToString function. Returns a string representation of the BitArray.
*   Parameters : None
*   Returned   : A string representation of the BitArray.
***************************************************************************/
std::string BitArray::toString() const
{
    std::string result;
    for (int i = 0; i < numBits; i++) {
        result += (*this)[i] ? '1' : '0';
    }
    return result;
}

/***************************************************************************
*   Method     : operator==
*   Description: Equality operator. Checks if two BitArrays are equal.
*   Parameters : a - The first BitArray to compare.
*                b - The second BitArray to compare.
*   Returned   : True if the BitArrays are equal, false otherwise.
***************************************************************************/
bool operator==(const BitArray &a, const BitArray &b)
{
    if (a.size() != b.size())
        return false;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i])
            return false;
    }
    return true;
}

/***************************************************************************
*   Method     : operator!=
*   Description: Inequality operator. Checks if two BitArrays are not equal.
*   Parameters : a - The first BitArray to compare.
*                b - The second BitArray to compare.
*   Returned   : True if the BitArrays are not equal, false otherwise.
***************************************************************************/
bool operator!=(const BitArray &a, const BitArray &b)
{
    if (a.size() != b.size())
        return true;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i])
            return true;
    }
    return false;
}

/***************************************************************************
*   Method     : operator&
*   Description: Bitwise AND operator. Performs a bitwise AND operation on two BitArrays and returns the result as a new BitArray.
*   Parameters : b1 - The first BitArray to perform the AND operation with.
*                b2 - The second BitArray to perform the AND operation with.
*   Returned   : A new BitArray with the result of the AND operation.
***************************************************************************/
BitArray operator&(const BitArray &b1, const BitArray &b2)
{
    BitArray result(b1);
    result &= b2;
    return result;
}

/***************************************************************************
*   Method     : operator|
*   Description: Bitwise OR operator. Performs a bitwise OR operation on two BitArrays and returns the result as a new BitArray.
*   Parameters : b1 - The first BitArray to perform the OR operation with.
*                b2 - The second BitArray to perform the OR operation with.
*   Returned   : A new BitArray with the result of the OR operation.
***************************************************************************/
BitArray operator|(const BitArray &b1, const BitArray &b2)
{
    BitArray result(b1);
    result |= b2;
    return result;
}

/***************************************************************************
*   Method     : operator^
*   Description: Bitwise XOR operator. Performs a bitwise XOR operation on two BitArrays and returns the result as a new BitArray.
*   Parameters : b1 - The first BitArray to perform the XOR operation with.
*                b2 - The second BitArray to perform the XOR operation with.
*   Returned   : A new BitArray with the result of the XOR operation.
***************************************************************************/
BitArray operator^(const BitArray &b1, const BitArray &b2)
{
    BitArray result(b1);
    result ^= b2;
    return result;
}
