#include <iostream>
#include <string>
#include <fstream>

#include "parser.h"
#include "lexer.h"

int main(int argc, const char *argv[]) {
    if(argc < 2){
        cout << "Please supply a file" << endl;
        return 1;
    }

    Lexer l(argv[1]);   //pass the file name to the lexer to extract the tokens
    Parser parse(&l);   //the lexer then passes the tokens to the parser
    if(parse.Program()){
        cout << "Program successful" << endl;
        for(map<string,int>::const_iterator it=parse.value_table.begin(); it!=parse.value_table.end(); ++it){
            cout << it->first << " = " << it->second << endl;
        }
    }
    else {
        cout << "error" << endl;
    }
    return 0;
}
