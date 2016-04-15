#ifndef PARSER_H
#define PARSER_H

#include <string>

class Parser
{
  protected:
    std::string _data;
    int _index;
  
    static bool isSkippable(char c);
    //char getToken();
    void parse();
  public:
    Parser(std::string s) : _data(s), _index(0) { parse(); }
    char getToken();
};

#endif 
