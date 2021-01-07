#include<iostream>
#include<vector>
#include<string>

#define MAX 26
using namespace std;

class Graph{
public:
Graph(int v){
    V=v;
    susedi.resize(v);
    visited.resize(v);
    fill(visited.begin(),visited.end(),false);
}

void add_edge(int u,int v){
    susedi[u].push_back(v);
    susedi[v].push_back(u);
}


void svi_putevi(int u){
    visited[u]=true;
    put.push_back(u);
    if(put.size()==V){
        for(int x : put)
            cout<<x<<" -> ";
        cout<<endl;    
    }

    for(int sused : susedi[u]){
        if(!visited[sused]){
            svi_putevi(sused);
            visited[u]=false;
            put.pop_back();
        }
    }
}




private:
vector<vector<int>>susedi;
int V;
vector<bool> visited;
vector<int> put;  //cuva hamiltonov put
};


int main(){

   Graph g(4);

  g.add_edge(0, 1);
  g.add_edge(0, 2);
  g.add_edge(0, 3);
  g.add_edge(1, 2);
  g.add_edge(1, 3);
  g.add_edge(2, 3);

  g.svi_putevi(0);

    return 0;
}