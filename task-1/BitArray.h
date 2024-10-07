#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H

#include <string>
#include <vector>

class BitArray
{
private:
    class Wrapper
    {
    private:
        BitArray &bitArray;
        int index;
    public:
        Wrapper(BitArray &bitArray, int index);
        Wrapper &operator=(bool value);
        operator bool() const;
    };
    int numBits;
    std::vector<unsigned char> data;

public:
    BitArray();
    ~BitArray();
    explicit BitArray(int numBits, unsigned long value = 0);
    BitArray(const BitArray &b);

    void swap(BitArray &b);

    BitArray &operator=(const BitArray &b);

    void resize(int numBits, bool value = false);

    void clear();

    void pushBack(bool bit);

    BitArray &operator&=(const BitArray &b);
    BitArray &operator|=(const BitArray &b);
    BitArray &operator^=(const BitArray &b);

    BitArray &operator<<=(int n);
    BitArray &operator>>=(int n);
    BitArray operator<<(int n) const;
    BitArray operator>>(int n) const;

    BitArray &set(int index, bool value = true);

    BitArray &set();

    BitArray &reset(int index);

    BitArray &reset();

    bool any() const;

    bool none() const;

    BitArray operator~() const;

    int count() const;

    Wrapper operator[](int i);

    bool operator[](int i) const;

    int size() const;

    bool empty() const;

    std::string toString() const;
};

bool operator==(const BitArray &a, const BitArray &b);
bool operator!=(const BitArray &a, const BitArray &b);

BitArray operator&(const BitArray &b1, const BitArray &b2);
BitArray operator|(const BitArray &b1, const BitArray &b2);
BitArray operator^(const BitArray &b1, const BitArray &b2);

#endif