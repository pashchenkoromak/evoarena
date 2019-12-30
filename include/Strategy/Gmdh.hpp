#pragma once

#include "IStrategy.hpp"
#include "../Arena.hpp"
#include "Rule.hpp"
class Gmdh : public IStrategy
{
public:
    void train();
    Value makeDecision() override;
    void endRound(const Value& yourAnswer, const Value enemyAnswer, const int points) override;
    void startFight() override;
    void show(std::ostream& os) override;
    void setF(const size_t _F) { F = _F; }
    ~Gmdh() = default;
private:
    Rule decisionMaker;
    std::vector<possibleValue> story;
    std::vector<Rule> createFirstGeneration();
    /**
     * @brief 
     * 
     * @param previousGen 
     * @param _F Count of members, that must survive.
     * @return std::vector<Rule> 
     */
    std::vector<Rule> selection(const std::vector<Rule>& previousGen, const size_t _F);
    std::vector<Rule> createNextGeneration(const std::vector<Rule>&);
    const size_t memory = 10;
    /**
     * @brief Gmdh const - count of best models to the next row
     */
    size_t F = 3;
};
