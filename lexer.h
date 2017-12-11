#ifndef lexer_h
#define lexer_h
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>

#include "token.h"

using namespace std;

class Lexer{
public:
    Lexer();
    Lexer(string filename);
    Token get_next_token();
    Token peek_next_token();
    int get_cursor();
    int set_cursor(int value);
private:
    ifstream in;
    Token populate_stream();
    vector<Token> Tokenstream;
    int cursor; //point to our current location on the token stream
};

#endif

