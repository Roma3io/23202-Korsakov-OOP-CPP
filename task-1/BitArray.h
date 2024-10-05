#include <string>
#include <vector>
class BitArray
{
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

    bool operator[](int i) const;

    int size() const;

    bool empty() const;

    std::string toString() const;

private:
    int capacity;
    std::vector<unsigned char> data;
};

bool operator==(const BitArray &a, const BitArray &b);
bool operator!=(const BitArray &a, const BitArray &b);

BitArray operator&(const BitArray &b1, const BitArray &b2);
BitArray operator|(const BitArray &b1, const BitArray &b2);
BitArray operator^(const BitArray &b1, const BitArray &b2);