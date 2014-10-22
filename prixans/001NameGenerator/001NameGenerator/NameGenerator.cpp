#include "NameGenerator.h"
#include "Name.h"
#include <fstream>
#include <string>
#include <cstdlib>
#include <time.h>  

NameGenerator::NameGenerator(std::string path)
{
  LoadNames(path);
}


NameGenerator::~NameGenerator()
{
  BaseNames.clear();
}

void NameGenerator::ListAllNames()
{
  
  for (int i = 0; i != BaseNames.size(); i++)
  {
    std::string s = BaseNames[i].name;
    s += " \n";
    printf(s.c_str());
  }
}

bool NameGenerator::LoadNames(std::string path)
{
  std::fstream plik;
  std::string s;
  char cs[256];

  std::string name;
  bool sex;
  int sy;
  int col;
  plik.open(path, std::ios::in);
  if (plik.good() == true)
    while (!plik.eof())
    {
    name = "";
    sex = false;
    sy = 0;
    col = 0;
    plik.getline(cs, 256); 
    std::string p = "";
    int j = 0;
    do
    {
      p += cs[j];
      j++;
    } while (cs[j] != '\0');

    for (int i = 0; i < p.length(); i++)
    {      
      if (p[i] == ';' || p[i] == '\0')
      {
        switch (col)
        {
        case 0:
          name = s;
          s.clear();
          col++;
          break;

        case 1:
          s.clear();
          col++;
          break;

        case 2:
          sex = s == "M";
          s.clear();
          col++;
          break;

        case 3:
          sy = atoi(s.c_str());
          s.clear();
          col++;
          break;
        }
        if (i == 4)
          break;
      }
      else
        if (p[i] != '"')
          s.push_back(p[i]);
    }
    Name *n = new Name(name, sex, sy);
    s.clear();
    this->BaseNames.push_back(*n);
    }
  else
    throw "B³¹d otwarcia pliku";
}

std::string NameGenerator::GenName()
{
  int NameCount = this->BaseNames.size();
  srand(time(NULL));
  std::string name = "";
  int numberOfPart = rand() % 3 + 1;
  for (int i = 0; i < numberOfPart; i++)
  { 
    int word = rand() % NameCount;
    name += " ";
    name += BaseNames[word].name;
  }
  return name;
}
