#include <Arena.hpp>

int Arena::calcPoints(const Value& a, const Value& b) const
{
    int res;
    if (a.val == possibleValue::True && b.val == possibleValue::True)
        res = BothTrue;
    else if (a.val == possibleValue::True && b.val == possibleValue::False)
        res = OneTrue;
    else if (a.val == possibleValue::False && b.val == possibleValue::False)
        res = BothFalse;
    else if (a.val == possibleValue::False && b.val == possibleValue::True)
        res = OneFalse;
    return res;
}

void Arena::fight(std::shared_ptr<IStrategy> a, std::shared_ptr<IStrategy> b, const size_t times_number /* = DEFAULT_NUMBER_OF_TIMES */)
{
    // std::cout << "Before fight:\n\t";
    // a->show(std::cout);
    // std::cout << " = " << stats[a] << "\n\t";
    // b->show(std::cout);
    // std::cout << " = " << stats[b] << std::endl;
    Value aDecision, bDecision;
    int aPoints, bPoints;
    a->startFight();
    b->startFight();
    for (size_t i = 0; i < times_number; i++)
    {
        aDecision = a->makeDecision();
        bDecision = b->makeDecision();
        aPoints = calcPoints(aDecision, bDecision);
        bPoints = calcPoints(bDecision, aDecision);
        a->endRound(aDecision, bDecision, aPoints);
        b->endRound(bDecision, aDecision, bPoints);
        stats[a] += aPoints;
        stats[b] += bPoints;
    }
//     std::cout << "After fight:\n\t";
//     a->show(std::cout);
//     std::cout << " = " << stats[a] << "\n\t";
//     b->show(std::cout);
//     std::cout << " = " << stats[b] << std::endl;
}

void Arena::showResults(std::ostream& os)
{
    os << "Stats are:\n";
    for(auto strategy : stats)
    {
        strategy.first->show(os);
        std::cout << " has result " << strategy.second << "\n";
    }
}