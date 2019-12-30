#pragma once

#include <string>

enum class possibleValue {
    True,
    False,
    Unknown,
    Any
};

struct Value {
    Value(): val(possibleValue::Unknown) {}
    Value(const possibleValue _val): val(_val) {}
    std::string name;
    possibleValue val;
};
