/*
To program stryka, kojarzysz to tak jak smak toffika
*/
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

void generateNewNames( const std::vector<std::string> &, std::vector<std::string> &, std::string = std::string(), int = 0 );

std::vector<std::string> loadSyllables( std::istream &istream )
{
	std::string temp;
	std::vector<std::string> ret;

	if( istream.good() )
	{
		while( istream >> temp )
			ret.push_back( temp );
	}

	return ret;
}

void generateNewNames( const std::vector<std::string> &syllables, std::vector<std::string> &allGeneratedNames, std::string name, int syllablesInWord )
{
	const unsigned int maxSyllablesInWord = 3;

	for( const std::string &syllable : syllables )
	{
		allGeneratedNames.push_back( name + syllable );

		if( syllablesInWord + 1 < maxSyllablesInWord )
			generateNewNames( syllables, allGeneratedNames, name + syllable, syllablesInWord + 1 );
	}
}

std::vector<std::string> generateNames( const std::vector<std::string> &syllables )
{
	std::vector<std::string> allGeneratedNames;

	generateNewNames( syllables, allGeneratedNames );

	return allGeneratedNames;
}

void printSignature()
{
	std::cout << "To program stryka, kojarzysz to tak jak smak toffika.\n\n";
}

void printVector( const std::vector<std::string> &v )
{
	for( const std::string &i : v )
		std::cout << i << "\n";
}

void printGeneratedNames( const std::vector<std::string> &names, std::vector<std::string> &syllables )
{
	std::cout << "Used syllables:\n\n";
	printVector( syllables );
	std::cout << "\n\nGenerated names:\n\n";
	printVector( names );
}

int main()
{
	std::vector<std::string> syllables, generatedNames;

	printSignature();
	syllables = loadSyllables( std::ifstream( "syllables.txt" ) );
	generatedNames = generateNames( syllables );
	printGeneratedNames( generatedNames, syllables );

	return 0;
}