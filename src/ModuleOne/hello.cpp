#include <iostream>
#include "../../include/Expression.h"
#include "hello.h"
#include "../../include/CoreEvaluator.h"



void hello() {
    CoreEvaluator coreEvaluator;
    coreEvaluator.CreateGraph();
    ResultTree resultTree = coreEvaluator.returnResultTree("#(x|y)>$(x&y)");
    resultTree.Visualise("w1");
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

