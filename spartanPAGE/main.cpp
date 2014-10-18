/*
    Whole following code was written in ideone.com, so here is just a one file
*/

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <random>
using namespace std;

class RandomNameGenerator{
public:
	typedef vector<string> Prefixes;
	typedef vector<string> Cores;
	typedef vector<string> Sufixes;
public:
	RandomNameGenerator(
		const Prefixes &, 
		const Cores &, 
		const Sufixes &,
		default_random_engine
	);
	
	string operator()(size_t, size_t);
private:
	Prefixes _prefixes;
	Cores _cores;
	Sufixes _sufixes;
	default_random_engine &_dre;
};

RandomNameGenerator::RandomNameGenerator(
	const Prefixes &prefixes,
	const Cores &cores,
	const Sufixes &sufixes,
	default_random_engine dre
): _prefixes(prefixes), _cores(cores), _sufixes(sufixes), _dre(dre){}

string RandomNameGenerator::operator()(
	size_t minCoreRepeats,
	size_t maxCoreRepeats
){
	string result;
	typedef uniform_int_distribution<int> distro;
	enum{ PrefixID, CoreID, SufixID, CoreRepeatsID, Count };
	array<distro, Count> distros = {
		distro(0, _prefixes.size()-1),
		distro(0, _cores.size()-1),
		distro(0, _sufixes.size()-1),
		distro(minCoreRepeats, maxCoreRepeats)
	};
	result += _prefixes[distros[PrefixID](_dre)];
	size_t coreRepeats = distros[CoreRepeatsID](_dre);
	while(coreRepeats--)
		result += _cores[distros[CoreID](_dre)];
	return result += _sufixes[distros[SufixID](_dre)];
}

/*
  How to use THIS application?
  You have to provide (using program input) these 3 following values:
    - times; That program should generate random names
    - minCores; The minimal count of name-cores, that app have to use
    - maxCores; The maximal -||-
*/
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
