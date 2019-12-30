#pragma once
#include <vector>
#include <Value.hpp>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

class Rule {
public:
    Rule() = default;
    Rule(const Rule&) = default;
    Rule& operator=(const Rule&) = default;
    Rule(Rule&&) = default;
    Rule(const size_t index, const possibleValue val): isTale(true), neededValue(val), neededIndex(index) {}
    Rule(const Rule l, const Rule r) : isTale(false), rules(std::make_pair(std::make_shared<Rule>(l), std::make_shared<Rule>(r))) {}
    void show(std::ostream& os)
    {
        if (isTale)
        {
            os << "(x[" << neededIndex << "] is " << static_cast<int>(neededValue) << ")";
        } else
        {
            rules.first->show(os);
            os << " AND ";
            rules.second->show(os);
        }
    }

    Value makeDecision(const std::vector<possibleValue>& answers)
    {
        if (!isTale)
        {
            possibleValue lAnswer = rules.first->makeDecision(answers).val,
                        rAnswer = rules.second->makeDecision(answers).val;
            if (lAnswer == possibleValue::True && rAnswer == possibleValue::True)
                return Value{possibleValue::True};
            return Value{possibleValue::False};
        } else {
            if (answers.size() <= neededIndex || answers[neededIndex] == possibleValue::Unknown)
                return makeRandom(0.5);
            if (neededValue == answers[neededIndex])
                return Value{possibleValue::True};
            return Value{possibleValue::False};
        }
    }
private:
    Value makeRandom(double probability)
    {
        int random_value = std::rand() % 100000;
        if (random_value < probability * 100000)
            return Value{possibleValue::True};
        else return Value{possibleValue::False};
    }
    bool isTale;
    int neededIndex;
    std::pair<std::shared_ptr<Rule>, std::shared_ptr<Rule>> rules;
    std::pair<possibleValue, possibleValue> results;
    possibleValue neededValue;
};
