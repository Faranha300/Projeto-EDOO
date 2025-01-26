#include "Value.h"
using namespace std;

Value::Value(int v) : intValue(v), isBool(false) {}

Value::Value(bool v) : boolValue(v), isBool(true) {}

bool Value::isBoolean() const {
    return isBool;
}

int Value::asInt() const {
    if (isBool) throw runtime_error("Erro: Tentativa de acessar um bool como int.");
    return intValue;
}

bool Value::asBool() const {
    if (!isBool) throw runtime_error("Erro: Tentativa de acessar um int como bool.");
    return boolValue;
}
