#include "BitArray.h"
#include <iostream>
#include <stdexcept>
#include <string>

BitArray::BitArray() : numBits(0) {}

BitArray::~BitArray() = default;

BitArray::BitArray(int numBits, unsigned long value) : numBits(numBits)
{
    data.resize((numBits + 7) / 8);
    for (int i = 0; i < sizeof(long); i++) {
        set(i, value & 0x01);
    }
}

BitArray::BitArray(const BitArray &b)
{
    data = b.data;
    numBits = b.numBits;
}

void BitArray::swap(BitArray &b)
{
    data.swap(b.data);
    std::swap(numBits, b.numBits);
}

BitArray &BitArray::operator=(const BitArray &b)
{
    resize(b.data.size());
    data = b.data;
    numBits = b.numBits;
    return *this;
}

void BitArray::resize(int numBits, bool value)
{
    data.resize((numBits + 7) / 8);
    for (int i = this->numBits; i < numBits; ++i) {
        set(i, value);
    }
    this->numBits = numBits;
}

void BitArray::clear()
{
    numBits = 0;
    data.clear();
}

void BitArray::pushBack(bool bit)
{
    if (numBits % 8 != 0) {
        resize(numBits + 1);
        set(numBits - 1, bit);
    } else {
        set(numBits - 1, bit);
    }
}

BitArray &BitArray::operator&=(const BitArray &b)
{
    if (numBits != b.numBits) {
        throw std::invalid_argument("BitArrays must have the same size for bitwise AND operation");
    }
    for (int i = 0; i < numBits; ++i) {
        set(i, (*this)[i] & b[i]);
    }
    return *this;
}

BitArray &BitArray::operator|=(const BitArray &b)
{
    if (numBits != b.numBits) {
        throw std::invalid_argument("BitArrays must have the same size for bitwise OR operation");
    }
    for (int i = 0; i < numBits; ++i) {
        set(i, (*this)[i] | b[i]);
    }
    return *this;
}

BitArray &BitArray::operator^=(const BitArray &b)
{
    if (numBits != b.numBits) {
        throw std::invalid_argument("BitArrays must have the same size for bitwise XOR operation");
    }
    for (int i = 0; i < numBits; i++) {
        set(i, (*this)[i] ^ b[i]);
    }
    return *this;
}
BitArray &BitArray::operator<<=(int n)
{
    for (int i = numBits - 1; i >= n; i--) {
        set(i, (*this)[i - n]);
    }
    for (int i = 0; i < n; ++i) {
        set(i, false);
    }
    return *this;
}

BitArray &BitArray::operator>>=(int n)
{

    for (int i = 0; i < numBits - n; ++i) {
        set(i, (*this)[i + n]);
    }
    for (int i = numBits - n; i < numBits; ++i) {
        set(i, false);
    }
    return *this;
}

BitArray BitArray::operator<<(int n) const
{
    BitArray result(*this);
    result <<= n;
    return result;
}

BitArray BitArray::operator>>(int n) const
{
    BitArray result(*this);
    result >>= n;
    return result;
}

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

BitArray &BitArray::set()
{
    for (int i = 0; i < numBits; i++) {
        set(i, true);
    }
    return *this;
}

BitArray &BitArray::reset(int index)
{
    set(index, false);
    return *this;
}

BitArray &BitArray::reset()
{
    for (int i = 0; i < numBits; i++) {
        set(i, false);
    }
    return *this;
}

bool BitArray::any() const
{
    for (int i = 0; i < numBits; i++) {
        if ((*this)[i])
            return true;
    }
    return false;
}

bool BitArray::none() const
{
    for (int i = 0; i < numBits; i++) {
        if ((*this)[i])
            return false;
    }
    return true;
}

BitArray BitArray::operator~() const
{
    BitArray result(*this);
    for (int i = 0; i < numBits; ++i) {
        result.set(i, !(*this)[i]);
    }
    return result;
}

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

BitArray::Wrapper::Wrapper(BitArray &bitArray, int index) : bitArray(bitArray), index(index) {}

BitArray::Wrapper BitArray::operator[](int i)
{
    return Wrapper(*this, i);
}

BitArray::Wrapper &BitArray::Wrapper::operator=(bool value)
{
    bitArray.set(index, value);
    return *this;
}

BitArray::Wrapper::operator bool() const
{
    int byteIndex = index / 8;
    int bitIndex = index % 8;
    return (bitArray.data[byteIndex] >> bitIndex) & 0x01;
}

bool BitArray::operator[](int i) const
{
    int byteIndex = i / 8;
    int bitIndex = i % 8;
    return (data[byteIndex] >> bitIndex) & 0x01;
}

int BitArray::size() const
{
    return numBits;
}

bool BitArray::empty() const
{
    return numBits == 0;
}

std::string BitArray::toString() const
{
    std::string result;
    for (int i = 0; i < numBits; i++) {
        result += (*this)[i] ? '1' : '0';
    }
    return result;
}

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

bool operator!=(const BitArray &a, const BitArray &b)
{
    if (a.size() != b.size())
        return true;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == b[i])
            return false;
    }
    return true;
}

BitArray operator&(const BitArray &b1, const BitArray &b2)
{
    BitArray result(b1);
    result &= b2;
    return result;
}

BitArray operator|(const BitArray &b1, const BitArray &b2)
{
    BitArray result(b1);
    result |= b2;
    return result;
}

BitArray operator^(const BitArray &b1, const BitArray &b2)
{
    BitArray result(b1);
    result ^= b2;
    return result;
}
