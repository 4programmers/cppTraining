#include <iostream>
#include "NameGenerator.h"

using namespace std;

int main()
{
  NameGenerator* NameGen = new NameGenerator("imiona.csv");
  printf(NameGen->GenName().c_str());
  return 0;
}