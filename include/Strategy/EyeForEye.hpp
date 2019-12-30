#pragma once

#include "IStrategy.hpp"

class EyeForEye : public IStrategy
{
public:
    Value makeDecision() override {
        Value res;
        if (m_enemyAnswer.val == possibleValue::Unknown)
            res.val = possibleValue::True;
        else res.val = m_enemyAnswer.val;
        return res;
    };
    void endRound(const Value& yourAnswer, const Value enemyAnswer, const int points) {
        m_enemyAnswer = enemyAnswer;
    }
    void startFight() {
        m_enemyAnswer.val = possibleValue::Unknown;
    };
    void show(std::ostream& os) {
        os << "return EyeForEye";
    };
private:
    Value m_enemyAnswer;
};