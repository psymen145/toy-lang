#include <iostream>
#include <stdlib.h>
#include <string>

#include "parser.h"
#include "lexer.h"

Parser::Parser(Lexer *l):lex(l){}

bool Parser::end_term(token_type t){
    Token temp_tok = lex->get_next_token();
    if(temp_tok.type == token_ident){
        current_ident = temp_tok.identifier_str;
        value_table[temp_tok.identifier_str];
    }
    if(temp_tok.type == token_num){
        value_table[current_ident] = temp_tok.num_val;
    }
    return temp_tok.type == t;
}

//start the parser and check if the tokens returned from the lexer program
bool Parser::Program(){
    //perform recursive descent
    int save;
    while(Assignment()){
        save = lex->get_cursor();
        if(end_term(token_eof)){
            return true;
        }
        else{
            lex->set_cursor(save);
        }
    }
    return false;
}

bool Parser::Assignment(){
    return Assignment1();
}

bool Parser::Assignment1(){
    return Identifier() && end_term(token_assign) && Exp() && end_term(token_semi_colon);
}

bool Parser::Exp(){
    return Term() && Exp_Prime();
}

bool Parser::Exp_Prime(){
    int save = lex->get_cursor();
    return (lex->set_cursor(save), Exp_Prime1()) || (lex->set_cursor(save), Exp_Prime2()) || (lex->set_cursor(save), true); //episilon
}

bool Parser::Exp_Prime1(){
    return end_term(token_plus) && Term() && Exp_Prime();
}

bool Parser::Exp_Prime2(){
    return end_term(token_minus) && Term() && Exp_Prime();
}

bool Parser::Term(){
    int save = lex->get_cursor();
    return (lex->set_cursor(save), Term1());
}

bool Parser::Term1(){
    return Fact() && Term_Prime();
}

bool Parser::Term_Prime(){
    int save = lex->get_cursor();
    return (lex->set_cursor(save), Term_Prime1()) || (lex->set_cursor(save), true);
}

bool Parser::Term_Prime1(){
    return end_term(token_multi) && Fact() && Term_Prime();
}

bool Parser::Fact(){
    int save = lex->get_cursor();
    return (lex->set_cursor(save), Fact1()) || (lex->set_cursor(save), Fact2()) ||
            (lex->set_cursor(save), Fact3()) || (lex->set_cursor(save), Fact4()) ||
            (lex->set_cursor(save), Fact5());
}

bool Parser::Fact1(){
    return end_term(token_open_paren) && Exp() && end_term(token_close_paren);
}

bool Parser::Fact2(){
    return end_term(token_minus) && Fact();
}

bool Parser::Fact3(){
    return end_term(token_plus) && Fact();
}

bool Parser::Fact4(){
    return Literal();
}

bool Parser::Fact5(){
    return Identifier();
}

bool Parser::Identifier(){
    return end_term(token_ident);
}

bool Parser::Literal(){
    return end_term(token_num);
}
