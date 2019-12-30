#pragma once

#include "IStrategy.hpp"

class AlwaysTrue : public IStrategy
{
public:
    Value makeDecision() override {
        Value res;
        res.val = possibleValue::True;
        return res;
    };
    void endRound(const Value& yourAnswer, const Value enemyAnswer, const int points) {}
    void startFight() {};
    void show(std::ostream& os) {
        os << "return True";
    };
};