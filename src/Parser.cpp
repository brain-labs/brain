
#include "Parser.h"
#include <iostream>

bool Parser::isSkippable(char c)
{
  return (c != '<' && c != '>' &&
          c != '+' && c != '-' &&
          c != '.' && c != ',' &&
          c != '[' && c != ']');
}

char Parser::getToken()
{
  char c = 0;
  while ( (c = _data[_index++]) && isSkippable(c) ) { }
  return c;
}

void Parser::parse()
{
   char c = 0;
   while ( (c = getToken()) ) {
     switch (c)
     {
       case '<':
         std::cout << "go to left" << std::endl; break;
       case '>':
        std::cout << "go to right" << std::endl; break;
       case '+':
        std::cout << "add one" << std::endl; break;
       case '-':
         std::cout << "substract one" << std::endl; break;
       case '.':
         std::cout << "print" << std::endl; break;
       case ',':
         std::cout << "ask for value" << std::endl; break;
       case '[':
         std::cout << "start loop" << std::endl; break;
       case ']':
         std::cout << "end loop" << std::endl; break;
       default: break; // Ignored character
     }
   }
}


