#include "Parser.h"
#include <string>
#include <iostream>

int main()
{
  std::string s = ">>+++ <<3 + >++ < 123 abc .>.>.";
  Parser parser(s);
  char c = 0;
  while ( (c = parser.getToken()) ) 
  {
    std::cout << c << " ";
  }
 
  return 0;
}
