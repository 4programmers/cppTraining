#pragma once

#include <vector>
#include <array>
#include <string>
#include <random>

template<typename RandomEngine = std::default_random_engine>
class RandomNameGenerator{
public:
    typedef std::vector<std::string> Prefixes;
    typedef std::vector<std::string> Cores;
    typedef std::vector<std::string> Sufixes;
    typedef std::string Result;
public:
    RandomNameGenerator(
        const Prefixes &prefixes,
        const Cores &cores,
        const Sufixes &sufixes,
        RandomEngine &re
    ): _prefixes(prefixes), _cores(cores), _sufixes(sufixes), _re(re){}

    Result operator()(
        size_t minCoreRepeats,
        size_t maxCoreRepeats
    ){
        Result result;
        typedef std::uniform_int_distribution<int> distro;
        enum{ PrefixID, CoreID, SufixID, CoreRepeatsID, Count /* <-- Have to be the last!*/};
        std::array<distro, Count> distros = {
            distro(0, _prefixes.size()-1),
            distro(0, _cores.size()-1),
            distro(0, _sufixes.size()-1),
            distro(minCoreRepeats, maxCoreRepeats)
        };
        result += _prefixes[distros[PrefixID](_re)];
        size_t coreRepeats = distros[CoreRepeatsID](_re);
        while(coreRepeats--)
            result += _cores[distros[CoreID](_re)];
        return result += _sufixes[distros[SufixID](_re)];
    }
private:
    Prefixes _prefixes;
    Cores _cores;
    Sufixes _sufixes;
    RandomEngine &_re;
};
