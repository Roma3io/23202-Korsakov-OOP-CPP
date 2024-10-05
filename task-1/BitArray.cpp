#include "BitArray.h"
#include <iostream>
#include <stdexcept>
#include <string>
BitArray::BitArray()
{
    capacity = 0;
}

BitArray::~BitArray() = default;

BitArray::BitArray(int capacity, unsigned long value)
{
    this->capacity = capacity;
    data.resize((capacity + 7) / 8);
    for (int i = 0; i < sizeof(long); i++) {
        set(i, value & 0x01);
    }
}

BitArray::BitArray(const BitArray &b)
{
    data = b.data;
    capacity = b.capacity;
}

void BitArray::swap(BitArray &b)
{
    data.swap(b.data);
    std::swap(capacity, b.capacity);
}

BitArray &BitArray::operator=(const BitArray &b)
{
    resize(b.data.size());
    data = b.data;
    capacity = b.capacity;
    return *this;
}

void BitArray::resize(int capacity, bool value)
{
    data.resize((capacity + 7) / 8);
    for (int i = this->capacity; i < capacity; ++i) {
        set(i, value);
    }
    this->capacity = capacity;
}

void BitArray::clear()
{
    capacity = 0;
    data.clear();
}

void BitArray::pushBack(bool bit)
{
    if (capacity % 8 != 0) {
        resize(capacity + 1);
        set(capacity - 1, bit);
    } else {
        set(capacity - 1, bit);
    }
}

BitArray &BitArray::operator&=(const BitArray &b)
{
    if (capacity != b.capacity) {
        throw std::invalid_argument("BitArrays must have the same size for bitwise AND operation");
    }
    for (int i = 0; i < capacity; ++i) {
        set(i, (*this)[i] & b[i]);
    }
    return *this;
}

BitArray &BitArray::operator|=(const BitArray &b)
{
    if (capacity != b.capacity) {
        throw std::invalid_argument("BitArrays must have the same size for bitwise OR operation");
    }
    for (int i = 0; i < capacity; ++i) {
        set(i, (*this)[i] | b[i]);
    }
    return *this;
}

BitArray &BitArray::operator^=(const BitArray &b)
{
    if (capacity != b.capacity) {
        throw std::invalid_argument("BitArrays must have the same size for bitwise XOR operation");
    }
    for (int i = 0; i < capacity; ++i) {
        set(i, (*this)[i] ^ b[i]);
    }
    return *this;
}
BitArray &BitArray::operator<<=(int n)
{
    for (int i = capacity - 1; i >= n; --i) {
        set(i, (*this)[i - n]);
    }
    for (int i = 0; i < n; ++i) {
        set(i, false);
    }
    return *this;
}

BitArray &BitArray::operator>>=(int n)
{

    for (int i = 0; i < capacity - n; ++i) {
        set(i, (*this)[i + n]);
    }
    for (int i = capacity - n; i < capacity; ++i) {
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
    for (int i = 0; i < capacity; i++) {
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
    for (int i = 0; i < capacity; i++) {
        set(i, false);
    }
    return *this;
}

bool BitArray::any() const
{
    for (int i = 0; i < capacity; i++) {
        if ((*this)[i])
            return true;
    }
    return false;
}

bool BitArray::none() const
{
    for (int i = 0; i < capacity; i++) {
        if ((*this)[i])
            return false;
    }
    return true;
}

BitArray BitArray::operator~() const
{
    BitArray result(*this);
    for (int i = 0; i < capacity; ++i) {
        result.set(i, !(*this)[i]);
    }
    return result;
}

int BitArray::count() const
{
    int count = 0;
    for (int i = 0; i < capacity; i++) {
        if ((*this)[i]) {
            count++;
        }
    }
    return count;
}

bool BitArray::operator[](int i) const
{
    int byteIndex = i / 8;
    int bitIndex = i % 8;
    return (data[byteIndex] >> bitIndex) & 0x01;
}

int BitArray::size() const
{
    return capacity;
}


bool BitArray::empty() const
{
    return capacity == 0;
}

std::string BitArray::toString() const
{
    std::string result;
    for (int i = 0; i < capacity; i++) {
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

int main()
{
    BitArray bitArray1(4, 1);
    BitArray bitArray2(4, 0);
    std::cout << 'a';
}