//
// Created by root on 7/14/17.
//

#ifndef LOGICTOOLBOX_UNIVERSE_H
#define LOGICTOOLBOX_UNIVERSE_H

#include <string>
#include <vector>

using namespace std;

class Universe {
    string name;
    vector<string> variableNames = nullptr;
    vector<&World> worlds = nullptr;
};


#endif //LOGICTOOLBOX_UNIVERSE_H
