//
// Created by infloop on 7/16/17.
//

#include "../../include/Token.h"

Token::Token(const char read){

    if(read == '\000' || read == '\0' || read == '\n'){
        type = TokenType::EXPR_END;
        value = "";
        return;
    }

    if(token_map.find(read) != token_map.end()){
        type = token_map[read].first;
        value = token_map[read].second;
    } else{

        type = TokenType::LITERAL;
        value = read;

    }

}