//
// Created by infloop on 8/17/17.
//

#include "../../include/CoreEvaluator.h"

CoreEvaluator::CoreEvaluator(const char* PATH /* "UniverseConfig.json" */){

    //Read JSON file into Document class

    Document document;

    FILE* fp = fopen(const_cast<char*>(PATH), "r");
    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    ParseResult result = document.ParseStream(is);

    if(!result){
        cout << "JSON parse error:" << result.Code()<<  " " << result.Offset();
        return;
    }

    //Read universe name

    string universeName;

    if(document.HasMember("Name")){
        if(document["Name"].IsString()) universeName = document["Name"].GetString();
        else throw domain_error("[JSON ERROR] Universe name is not a string!");
    }else throw domain_error("[JSON ERROR] Unvierse doesn't have \"Name\" tag!");

    //Read universe logic

    string modalLogic;

    if(document.HasMember("Logic")){
        if(document["Logic"].IsString()) modalLogic = document["Logic"].GetString();
        else throw domain_error("[JSON ERROR] Universe logic is not a string!");
    }else throw domain_error("[JSON ERROR] Unvierse doesn't have \"Logic\" tag!");

    //Read variable names

    vector<string> variableNames;

    if(document.HasMember("VariableNames")){
        if(document["VariableNames"].IsArray()){
            const Value& vNames = document["VariableNames"];
            for(int i = 0; i < vNames.Size(); i++){
                if(vNames[i].IsString()) variableNames.push_back(vNames[i].GetString());
                else throw domain_error("[JSON ERROR] Array member of variable names is not a string!");
            }
        }else throw domain_error("[JSON ERROR] Variable names are not an array!");
    }else throw domain_error("[JSON ERROR] Universe doesn't have \"VariableNames\" tag!");

    //Read worlds

    vector<World*> worlds;

    if(document.HasMember("Worlds")){
        if(document["Worlds"].IsArray()){
            const Value& tmpWorlds = document["Worlds"];

            //Initial creation of worlds

            for(int i = 0; i < tmpWorlds.Size(); i++){

                World* newWorld;

                //if(tmpWorlds[i].IsObject()){

                    //Create world with name if exists

                    if(tmpWorlds[i].HasMember("Name")){
                        if(tmpWorlds[i]["Name"].IsString()) newWorld = new World(tmpWorlds[i]["Name"].GetString());
                        else throw domain_error("[JSON ERROR] World name is not a string!");
                    }else throw domain_error("[JSON ERROR] World doesn't have \"Name\" tag!");

                    //Add variables if exist

                    vector<Variable> variables;

                    if(tmpWorlds[i].HasMember("Variables")){
                        if(tmpWorlds[i]["Variables"].IsArray()){

                            const Value& tmpVariables = tmpWorlds[i]["Variables"];

                            //Create Variable

                            for(int j = 0; j < tmpVariables.Size(); j++){

                                //Variable name

                                Variable variable;

                                if(tmpVariables[j].HasMember("Name")){
                                    if(tmpVariables[j]["Name"].IsString()){

                                        string vName = tmpVariables[j]["Name"].GetString();

                                        //Check variable exists in the universe
                                        bool exists = false;
                                        for(auto v : variableNames) if(v == vName) {exists = true; break;}
                                        if(!exists) throw domain_error("[JSON ERROR] Variable with that name does not exist in this universe!");

                                        variable = Variable(vName);

                                    }else throw domain_error("[JSON ERROR] Variable name is not a string!");
                                }else throw domain_error("[JSON ERROR] Variable doesn't have \"Name\" tag!");

                                //Variable value

                                if(tmpVariables[j].HasMember("Value")){
                                    if(tmpVariables[j]["Value"].IsBool()) variable.setValue(tmpVariables[j]["Value"].GetBool());
                                    else throw domain_error("[JSON ERROR] Variable value is not a bool!");
                                }else throw domain_error("[JSON ERROR] Variable doesn't have \"Value\" tag!");

                                variables.push_back(variable);

                            }


                        }else throw domain_error("[JSON ERROR] Variables are not an array!");

                    }else throw domain_error("[JSON ERROR] World doesn't have \"Variables\" tag!");

                    if(variableNames.size() != variables.size()) throw domain_error("[JSON ERROR] Variable number doesn't match!");
                    else newWorld->setVariables(variables);

                //}
                //else throw domain_error("[JSON ERROR] Array member of worlds is not a object!");

                worlds.push_back(newWorld);
            }

            //Add adjacent worlds

            for(int i = 0; i < tmpWorlds.Size(); i++){

                if(tmpWorlds[i].HasMember("AdjWorlds")){
                    if(tmpWorlds[i]["AdjWorlds"].IsArray()){

                        const Value& adjWorlds = tmpWorlds[i]["AdjWorlds"];

                        for(int j = 0; j < adjWorlds.Size(); j++){

                            if(adjWorlds[j].IsString()){

                                string worldName = adjWorlds[j].GetString();

                                bool exists = false;

                                for(auto w : worlds){

                                    if(w->getName() == worldName){
                                        worlds[i]->addAdjacent(w);
                                        exists = true;
                                        break;
                                    }

                                }

                                if(!exists) throw domain_error("[JSON ERROR] World in adjecent worlds doesn't exist in this universe!");

                            }else throw domain_error("[JSON ERROR] Adjecent worlds member is not a string!");

                        }

                    }else throw domain_error("[JSON ERROR] Adjecent worlds is not an array!");
                }else throw domain_error("[JSON ERROR] World doesn't have \"AdjWorlds\" tag!");

            }

        }else throw domain_error("[JSON ERROR] Worlds are not an array!");
    }else throw domain_error("[JSON ERROR] Universe doesn't have \"Worlds\" tag!");

    universe = Universe(universeName);
    universe.setWorlds(worlds);
    universe.setVariableNames(variableNames);
    universe.setLogic(modalLogic);

    ToString();
}

void CoreEvaluator::ToString() {

    cout << "Universe name: " << universe.getName() << endl;
    cout << "Variable names: ";
    for(auto i : universe.getVariableNames()){
        cout << i << ", ";
    }
    cout << endl;
    cout << "Worlds: "<< endl;
    for(auto i : universe.getWorlds()){
        cout << "   Name: " << i->getName() << endl;
        cout << "   Variables: " << endl;
        for(auto j : i->getVariables()){
            cout << "       Name: " << j.getName() << endl;
            cout << "       Value: " << j.getValue() << endl;
            cout << endl;
        }
        cout << "   Adjecent worlds: ";
        for(auto j : i->getAdjacentList()) cout << j->getName() << ", ";
        cout << endl << endl;
    }

}

ResultTree CoreEvaluator::returnResultTree(string expression_string) {
    if(!graph.IsCreated()) graph = Graph(&universe);
    Expression newExpression = Expression(expression_string);
    resultTree = ResultTree(&universe,newExpression);
    graph.AddResults(resultTree);
    return resultTree;

}

void CoreEvaluator::CreateGraph(){
    graph = Graph(&universe);
}

void CoreEvaluator::RenderUniverse(string PATH) {

    graph.saveImage(PATH);

}

bool CoreEvaluator::CreateResultTreeGraph(string world, const char* FILE) {

    resultTree.Visualise(world, FILE);

}
