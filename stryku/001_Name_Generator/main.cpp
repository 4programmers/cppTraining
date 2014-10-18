/*
To program stryka, kojarzysz to tak jak smak toffika
*/
#include <fstream>
#include <vector>
#include <string>
#include <iostream>


bool getSyllables( std::vector<std::string> &syllables )
{
	std::ifstream syllablesFile;
	int syllablesCount;

	syllablesFile.open( "syllables.txt" );

	if( !syllablesFile.is_open() )
		return false;

	syllablesFile >> syllablesCount;
	syllables.resize( syllablesCount );

	while( syllablesCount-- )
		syllablesFile >> syllables[syllablesCount];

	syllablesFile.close();

	return true;
}

void generateNames( std::vector<std::string> &syllables, std::string &name, int lev )
{
	const int maxSyllablesInWord = 3;

	for( std::string &i : syllables )
	{
		std::cout << name << i << "\n";

		if( lev + 1 < maxSyllablesInWord )
			generateNames( syllables, name + i, lev + 1 );
	}
}

void printHelp()
{
	std::cout << "**** MANUAL ****\n\n";
	std::cout << "This program is generating names from syllables.\n"\
		<< "Put some syllables to \"syllables.txt\" file\n"\
		<< "Structure of file should be like this:\n\n"\
		<< "In first place number of syllables, after that, syllables seperated by white spaces.\n\n"\
		<< "For example see included file \"syllables.txt\"\n"\
		<< "Down there \\/ can you see generated names for that file\n\n"\
		<< "********************\n\n\n";
}

void checkArguments( int argc, char *argv[] )
{
	if( argc > 1 )
	{
		if( strcmp( "help", argv[1] ) == 0 )
			printHelp();
	}
}

int main(int argc, char *argv[])
{
	std::vector<std::string> syllables;

	std::cout << "To program stryka, kojarzysz to tak jak smak toffika.\n\n";

	checkArguments( argc, argv );

	if( !getSyllables( syllables ) )
	{
		std::cout << "File \"syllables.txt\" not found. Program will shut down.";
		return 1;
	}

	generateNames( syllables, std::string(), 0 );

	return 0;
}