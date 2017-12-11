#ifndef parser_h
#define parser_h
#include <string>
#include "lexer.h"
#include <map>

class Parser{
public:
    Parser(Lexer *l);
    bool end_term(token_type t);
    
    bool Program();
    
    bool Assignment();
    bool Assignment1();
    
    bool Exp();
    bool Exp_Prime();
    bool Exp_Prime1();
    bool Exp_Prime2();
    
    bool Term();
    bool Term1();
    bool Term_Prime();
    bool Term_Prime1();
    
    bool Fact();
    bool Fact1();
    bool Fact2();
    bool Fact3();
    bool Fact4();
    bool Fact5();
    
    bool Identifier();
    bool Letter();
    bool Literal();
    bool NonZeroDigit();
    bool Digit();
    
    string current_ident;
    int current_value;
    map<string, int> value_table;
private:
    Lexer *lex;
};

#endif
