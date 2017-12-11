#include "parser.h"
#include "lexer.h"

Lexer::Lexer():cursor(0){}

Lexer::Lexer(string filename):cursor(-1){
    in.open(filename);
    Token return_tok = populate_stream();

    while(return_tok.type != token_eof){
        Tokenstream.push_back(return_tok);
        return_tok = populate_stream();
    }
    //add sentinel at the end of the tokenstream to indicate the end of the stream
    Token sentinel_tok;
    sentinel_tok.type = token_eof;
    Tokenstream.push_back(sentinel_tok);
    in.close();
}

Token Lexer::get_next_token(){
    cursor++;
    return Tokenstream.at(cursor);
}

/*
Token Lexer::peek_next_token(){
    //if at the end of the token stream, then we just keep returning the last token (token eof)
    if(cursor > Tokenstream.size()-1){
        return Tokenstream.back();
    }
    else {
        return Tokenstream.at(cursor+1);
    }
}
*/
int Lexer::get_cursor(){
    return cursor;
}

int Lexer::set_cursor(int value){
    if(value < Tokenstream.size()-1){
        cursor = value;
        return 0;
    }
    else{
        return -1;
    }
}

//the given ifstream object from main will allow this function to read characters directly from the file given.
Token Lexer::populate_stream(){
    Token tok;
    int last_char = ' ';
    
    while (isspace(last_char)){
        last_char = in.get();
    }
    
    if(isalpha(last_char)){     // ([a-z][A-Z])*
        while(isalnum(last_char)){
            tok.identifier_str += last_char;
            last_char = in.peek();
            if(isalnum(last_char)){ //check the peek to see if next char is character.
                last_char = in.get();   //we only increment the stream pointer if it is a char
            }
        }
        tok.type = token_ident;
        return tok;
    }
    
    if(isdigit(last_char)){     // (0|[1-9][1-9]*)
        string num_str;
        bool first_is_zero = false;
        int count = 0;  //if first_is_zero is true, then we check the second number to see if 0
        bool invalid_flag = false;
        if(last_char == '0'){
            first_is_zero = true;
        }
        
        do{
            if(first_is_zero && count == 1){
                if(last_char == '0'){ //if the second digit is a zero while the first is a zero, then we pass invalid
                    invalid_flag = true;
                    tok.type = token_invalid_num;
                }
            }
            count++;
            num_str += last_char;
            last_char = in.peek();
            if(isdigit(last_char)){
                last_char = in.get();
            }
        }while(isdigit(last_char));
        
        tok.num_val = stoi(num_str);
        if(!invalid_flag){
            tok.type = token_num;
        }
        return tok;
    }
    
    if(last_char == '='){
        tok.type = token_assign;
        return tok;
    }
    
    if(last_char == '('){
        tok.type = token_open_paren;
        return tok;
    }
    
    if(last_char == ')'){
        tok.type =  token_close_paren;
        return tok;
    }
    
    if(last_char == '+'){
        tok.type = token_plus;
        return tok;
    }
    
    if(last_char == '-'){
        tok.type = token_minus;
        return tok;
    }
    
    if(last_char == '*'){
        tok.type = token_multi;
        return tok;
    }
    
    if(last_char == ';'){
        tok.type = token_semi_colon;
        return tok;
    }
    
    if(last_char == '\n'){
        tok.type = token_newline;
        return tok;
    }
    
    if(last_char == EOF){
        tok.type = token_eof;
        return tok;
    }
    
    tok.type = token_invalid;
    tok.identifier_str = last_char;
    return tok;
}
