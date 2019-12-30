#pragma once

#include "Value.hpp"
#include <iostream>
class IStrategy {
public:
    virtual Value makeDecision() = 0;
    virtual void startFight() = 0;
    virtual void show(std::ostream& os) = 0;
    virtual void endRound(const Value& yourAnswer, const Value enemyAnswer, const int points) = 0;
};