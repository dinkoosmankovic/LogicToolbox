#include <iostream>
#include "Parser/Expression.h"
#include "hello.h"



void hello() {
    string exp = "#((x&y)|(y|x|z)&$(z&x))";
    cout << exp << endl;
    Expression test = Expression(exp);
    vector<Token> tokens = test.getTokens();
    for(auto i = tokens.begin(); i != tokens.end(); i++){
        cout << i->value << endl;
    }
}

std::string get_message() {
    // There's a mistake here
    // Try running `make check` and observe the failing test case
    // Then correct the line below and repeat
    return "Hellx, World!";
}

std::string get_message1() {
    // There's a mistake here
    // Try running `make check` and observe the failing test case
    // Then correct the line below and repeat
    return "Hello, World!";
}

