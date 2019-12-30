#include <Gmdh.hpp>
#include <algorithm>

void Gmdh::train() {
    auto firstGen = createFirstGeneration();
    auto secondGen = createNextGeneration(firstGen);
    for(int i = 0; i < 1; i++)
    {
        secondGen = selection(secondGen, F);
        secondGen = createNextGeneration(secondGen);
    }
    decisionMaker = selection(secondGen, 1)[0];
}

Value Gmdh::makeDecision() {
    return decisionMaker.makeDecision(story);
}

void Gmdh::endRound(const Value& yourAnswer, const Value enemyAnswer, const int points) {
    story.push_back(yourAnswer.val);
    story.push_back(enemyAnswer.val);
}

void Gmdh::startFight() {
    story.clear();
}

void Gmdh::show(std::ostream& os) {
    decisionMaker.show(os);
};

std::vector<Rule> Gmdh::createFirstGeneration()
{
    std::vector<Rule> res;
    for(size_t i = 0; i < memory * 2; i++)
    {
        res.push_back({i / 2, i % 2 ? possibleValue::False : possibleValue::True});
    }
    return res;
}

typedef std::pair<std::shared_ptr<IStrategy>, size_t> mypair;

struct IntCmp {
    bool operator()(const mypair &lhs, const mypair &rhs) {
        return lhs.second < rhs.second;
    }
};

std::vector<Rule> Gmdh::selection(const std::vector<Rule>& gen, const size_t _F /* = F*/)
{
    const size_t N = gen.size();
    std::vector<std::shared_ptr<IStrategy>> training(gen.size());

    for(size_t i = 0; i < N; i++)
    {
        training[i] = std::make_shared<Gmdh>();
        dynamic_cast<Gmdh*>(training[i].get())->decisionMaker = gen[i];
    }
    Arena trainer;
    for(size_t i = 0; i < N; i++)
    {
        for(size_t j = i + 1; j < N; j++)
        {
            trainer.fight(training[i], training[j]);
        }
    }
    auto stats = trainer.getStats();
    std::vector<mypair> vec(stats.begin(), stats.end());
    std::partial_sort(vec.begin(), vec.begin() + _F, vec.end(), IntCmp());
    std::vector<Rule> res(_F);
    for(size_t i = 0; i < _F; i++)
    {
        res[i] = dynamic_cast<Gmdh*>(training[i].get())->decisionMaker;
    }
    return res;
}

std::vector<Rule> Gmdh::createNextGeneration(const std::vector<Rule>& previousGen)
{
    const size_t N = previousGen.size();
    std::vector<Rule> res;
    res.reserve(N * (N - 1) / 2);
    for(size_t i = 0; i < N; i++)
    {
        for(size_t j = i + 1; j < N; j++)
        {
            res.push_back({previousGen[i], previousGen[j]});
        }
    }
    return res;
}