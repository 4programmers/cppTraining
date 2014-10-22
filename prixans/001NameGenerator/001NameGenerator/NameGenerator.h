#pragma once
#include <string>
#include <vector>
#include "NameInfo.h"
#include "Name.h"

class NameGenerator
{
private:
  std::vector<Name> BaseNames;
  bool LoadNames(std::string path);

public:
  std::string GenName();
  NameGenerator(std::string path);
  void ListAllNames();
  ~NameGenerator();
};

