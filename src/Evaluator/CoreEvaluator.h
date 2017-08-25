//
// Created by infloop on 8/17/17.
//

#ifndef LOGICTOOLBOX_COREEVALUATOR_H
#define LOGICTOOLBOX_COREEVALUATOR_H

#include "../Parser/Expression.h"
#include "../Universe/Universe.h"
#include "../rapidjson/document.h"
#include "ResultTree.h"

class CoreEvaluator {
    Universe universe;
public:
    CoreEvaluator();
    ~CoreEvaluator();
    ResultTree returnResultTree(string expression_string);
};


#endif //LOGICTOOLBOX_COREEVALUATOR_H
