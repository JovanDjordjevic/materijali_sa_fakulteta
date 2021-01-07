#include<iostream>
#include<vector>

using namespace std;

class Graph{

public:
 Graph(int V){
   this->V=V;
   susedi.resize(V);
   visited.resize(V);
   fill(visited.begin(),visited.end(),false);
   broj_na_nivou=0;
 }


 void add_edge(int u, int v){
   susedi[u].push_back(v);
 }

 int get_broj(){
   return broj_na_nivou;
 }


 void dfs(int u, int level, int current_level){
   if(current_level==level){
     broj_na_nivou++;
   }
   for(int sused : susedi[u]){
     if(!visited[sused])
        dfs(sused,level,current_level+1);
   }
     
 }

  


private:
 int broj_na_nivou;               //!!
 int V;
 vector<vector<int>> susedi;
 vector<bool> visited;
};



int main(){

Graph g(8);

    g.add_edge(0, 1);
    g.add_edge(0, 4);
    g.add_edge(0, 7);
    g.add_edge(4, 6);
    g.add_edge(4, 5);
    g.add_edge(4, 2);
    g.add_edge(7, 3);

    int level;

    cin >> level;

    g.dfs(0,level,0);
  
    cout<<g.get_broj()<<endl;

  return 0;
}