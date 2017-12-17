#include <iostream>
#include "../include/Expression.h"
#include "hello.h"
#include "../include/CoreEvaluator.h"



void hello() {
    CoreEvaluator coreEvaluator;
    //coreEvaluator.CreateGraph();
    //coreEvaluator.RenderUniverse();
    ResultTree resultTree = coreEvaluator.returnResultTree("#(x|y)");
    //coreEvaluator.RenderUniverse("result.png");
    //resultTree.Visualise("w3");
}

std::string get_message() {
    // There's a mistake here
    // Try running `make check` and observe the failing testCoverage case
    // Then correct the line below and repeat
    return "Hellx, World!";
}

std::string get_message1() {
    // There's a mistake here
    // Try running `make check` and observe the failing testCoverage case
    // Then correct the line below and repeat
    return "Hello, World!";
}

