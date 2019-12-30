#include <iostream>
#include <vector>
#include <Arena.hpp>
#include <AlwaysTrue.hpp>
#include <AlwaysFalse.hpp>
#include <EyeForEye.hpp>
#include <Gmdh.hpp>

int main()
{
    std::vector<Gmdh> gmdhs;
    gmdhs.resize(4);
    for(int i = 0; i < 4; i++){
        gmdhs[i].setF(5);
        gmdhs[i].train();
    }
    Arena arena;
    std::vector<std::shared_ptr<IStrategy>> strategies {
        std::make_shared<AlwaysTrue>(),
        std::make_shared<AlwaysTrue>(),
        std::make_shared<AlwaysTrue>(),
        std::make_shared<AlwaysFalse>(),
        std::make_shared<AlwaysFalse>(),
        std::make_shared<AlwaysFalse>(),
        std::make_shared<AlwaysFalse>(),
        std::make_shared<EyeForEye>(),
        std::make_shared<EyeForEye>(),
        std::make_shared<EyeForEye>(),
        std::make_shared<EyeForEye>(),
        std::make_shared<EyeForEye>(),
        std::make_shared<Gmdh>(gmdhs[0]),
        std::make_shared<Gmdh>(gmdhs[1]),
        std::make_shared<Gmdh>(gmdhs[2]),
        std::make_shared<Gmdh>(gmdhs[3])
    };
    for(auto a : strategies)
        for(auto b : strategies)
        {
            arena.fight(a, b);
        }
    arena.showResults(std::cout);
    return 0;
}
