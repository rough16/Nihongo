#include <iostream>
#include <string>
using namespace std;

template <typename T1, typename T2>
auto genericFunc(T1 t1, T2 t2)
{
    return t1 + t2;
}

class One
{
    int x;

public:
    One(int val) : x(val) {}

    int getValue() const {
        return x;
    }
};

class Two
{
    string x;

public:
    Two(string val) : x(val) {}

    string getValue() const {
        return x;
    }
};

// Non-member operator overload
string operator+(const One& obj1, const Two& obj2)
{
    return to_string(obj1.getValue()) + obj2.getValue();
}

int main()
{
    cout << genericFunc<int, float>(10, 12.5f) << "\n";

    cout << genericFunc<One, Two>(
        One(10),
        Two("30.24")
    ) << "\n";

    return 0;
}
