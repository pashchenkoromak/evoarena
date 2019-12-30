#include <iostream>
#include <vector>
#include <Arena.hpp>
#include <AlwaysTrue.hpp>
#include <AlwaysFalse.hpp>
#include <EyeForEye.hpp>

int main()
{
    Arena arena;
    std::vector<std::shared_ptr<IStrategy>> strategies{
        std::make_shared<AlwaysTrue>(),
        std::make_shared<AlwaysFalse>(),
        std::make_shared<EyeForEye>()
    };
    for(auto a : strategies)
        for(auto b : strategies)
        {
            arena.fight(a, b);
        }
    arena.showResults(std::cout);
    return 0;
}
