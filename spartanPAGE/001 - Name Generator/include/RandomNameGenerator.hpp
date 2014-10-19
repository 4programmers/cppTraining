#pragma once

#include <vector>
#include <array>
#include <string>
#include <random>
#include <algorithm>

template<typename RandomEngine = std::default_random_engine>
class RandomNameGenerator{
    struct DataCorrector{
        void operator()(RandomNameGenerator *rng){
            std::for_each(
                std::begin(rng->_containers),
                std::end(rng->_containers),
                [](ContainerType *container){
                    if(container->empty())
                        container->push_back("");
                }
            );
        }
    };
public:
    typedef std::vector<std::string> ContainerType;
    typedef ContainerType Prefixes;
    typedef ContainerType Cores;
    typedef ContainerType Sufixes;
    typedef std::string Result;
public:
    RandomNameGenerator(
        const Prefixes &prefixes,
        const Cores &cores,
        const Sufixes &sufixes,
        RandomEngine &re
    ): _prefixes(prefixes), _cores(cores), _sufixes(sufixes), _re(re){
        constructContainersArray();
        DataCorrector()(this);
        constructDistros();
    }

    Result operator()(
        size_t minCoreRepeats,
        size_t maxCoreRepeats
    ){
        Result result;
        Distro coreRepeatsDistribution(minCoreRepeats, maxCoreRepeats);
        result += _prefixes[_distros[PrefixID](_re)];

        size_t coreRepeats = coreRepeatsDistribution(_re);
        while(coreRepeats--)
            result += _cores[_distros[CoreID](_re)];

        return result += _sufixes[_distros[SufixID](_re)];
    }
private:
    void constructDistros(){
        _distros = std::array<Distro, Count>{
            Distro(0, _prefixes.size()-1),
            Distro(0, _cores.size()-1),
            Distro(0, _sufixes.size()-1)
        };
    }
    void constructContainersArray(){
         _containers = std::array<ContainerType *, Count>{
             &_prefixes, &_cores, &_sufixes
        };
    }
private:
    typedef std::uniform_int_distribution<int> Distro;
    enum{ PrefixID, CoreID, SufixID, Count /* <-- Have to be the last!*/};
    std::array<Distro, Count> _distros;
    std::array<ContainerType *, Count> _containers;
private:
    Prefixes _prefixes;
    Cores _cores;
    Sufixes _sufixes;
    RandomEngine &_re;
};
