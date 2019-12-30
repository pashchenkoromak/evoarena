#pragma once

#include "IStrategy.hpp"

class AlwaysFalse : public IStrategy
{
public:
    Value makeDecision() override {
        Value res;
        res.val = possibleValue::False;
        return res;
    };
    void endRound(const Value& yourAnswer, const Value enemyAnswer, const int points) {}
    void startFight() {};
    void show(std::ostream& os) {
        os << "return False";
    };
};