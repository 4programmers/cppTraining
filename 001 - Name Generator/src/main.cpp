#include "RandomNameGenerator.hpp"

#include <iostream>
using namespace std;

int main() {
    default_random_engine dre;
    size_t times, minCores, maxCores;
    cin >> times >> minCores >> maxCores;
    RandomNameGenerator rng(
        RandomNameGenerator::Prefixes{
            "Bal", "Ner",
            "Xerth", "Vorc", "Norm",
            "Vaz", "Treth", "Melr",
            "Jatr", "Urugd", "Petr"
        },
        RandomNameGenerator::Cores{
            "",
            "adur", "aes", "anim", "apoll", "imac",
            "educ", "equis", "extr", "guius", "haun",
            "equi", "amora", "hum", "iace", "ille",
            "inept", "iuv", "obe", "ocul", "orbis"
        },
        RandomNameGenerator::Sufixes{
            "us", "as", "es", "ex",
            "aus", "irg", "orex", "or",
            "ator", "arox", "urh"
        },
        dre
    );

    while(times--)
        cout << rng(minCores, maxCores) << endl;
    return 0;
}
