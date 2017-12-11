#ifndef token_h
#define token_h

using namespace std;

enum token_type{
    token_eof = -1,
    token_ident = -2,
    token_num = -3,
    token_plus = -4,
    token_minus = -5,
    token_multi = -6,
    token_semi_colon = -7,
    token_open_paren = -8,
    token_close_paren = -9,
    token_assign = -10,
    token_invalid = -11,
    token_newline = -12,
    token_invalid_num = -13
};

struct Token {
    token_type type;
    string identifier_str;
    int num_val;
};

#endif
