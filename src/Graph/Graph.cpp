#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

struct node{
  typedef pair<int, node*> no;
  vector<no> adj;
  string name;
  node(string n) : name(n){}
}

class graph{

public:
  typedef map<string, node*> node_map;
  node_map nodes;
  void addnode(const string& name);
  void addedge(const string& from, const string& to, double cost);
}

void graph::addnode(const string &name){
  node_map::iterator it = nodes.find(name);
  if(it == nodes.end()){
    node *n;
    n = new node(name);
    nodes[name] = n;
    return;
  }
  throw "Node already exists!";
}

vodi graph::addedge(const string &from, const string &to, double cost){
  node *f = (nodes.find(from)->second);
  node *t = (nodes.find(to)->second);
  if(f == null || t == null) throw "Node(s) doesn't exist!";
  pair<int, node*> edge = make_pair(cost, t);
  f->adj.push_back(edge);
}
