#pragma once
#include <string>

/**/

class Name
{
public:
  std::string name;
  bool sex;
  int syllables;

public:
  Name(std::string n, bool s, int sy) : name(n), sex(s), syllables(sy)
  {

  }

  ~Name();
};

