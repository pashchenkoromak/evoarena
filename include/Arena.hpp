#pragma once

#include "Strategy/IStrategy.hpp"
#include <memory>
#include <map>

/**
 * @brief  Class to manage fights between strategies.
 */
class Arena {
public:
/**
 * @brief Fight between strategies. It calls "startFight" method of strategies, then repeat "times_number" of fight.
 *
 * @param a First strategy
 * @param b Second strategy
 * @param times_number Number of iterations
 */
    void fight(std::shared_ptr<IStrategy> a, std::shared_ptr<IStrategy> b, const size_t times_number = DEFAULT_NUMBER_OF_TIMES);
    void showResults(std::ostream& os);
    std::map<std::shared_ptr<IStrategy>, long long int> getStats() const { return stats; };
private:
    /**
     * @brief calculate, how to change points of strategy, which makes first decision
     *
     * @param a first decision
     * @param b second decision
     * @return int
     */
    int calcPoints(const Value& a, const Value& b) const;
    constexpr static size_t DEFAULT_NUMBER_OF_TIMES = 200;
    int BothTrue = 5;
    int BothFalse = 0;
    int OneTrue = -10;
    int OneFalse = 10;

/**
 * @brief Map to store results of fighting
 */
    std::map<std::shared_ptr<IStrategy>, long long int> stats;
};
