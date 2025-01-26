#ifndef VALUE_H
#define VALUE_H

#include <stdexcept>
using namespace std;

class Value {
private:
    bool isBool;
    union {
        int intValue;
        bool boolValue;
    };

public:
    Value(int v);
    Value(bool v);

    bool isBoolean() const;
    int asInt() const;
    bool asBool() const;
};

#endif
