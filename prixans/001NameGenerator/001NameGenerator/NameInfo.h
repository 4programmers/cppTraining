#pragma once
#include <string>

/*Klasa zawieraj¹ca informacje o generatorze*/
class NameInfo
{
public:
  int LengthOfWorld;
  int NumberOfParts;
  int RandomDegree;
  std::string path;

  NameInfo(int low, int nop, int rd, std::string s) : LengthOfWorld(low), NumberOfParts(nop), RandomDegree(rd), path(s)
  {
  }
  ~NameInfo();
};

