//ne radi mi dfs lepo, dobijam da je svaki cvor zasebna komponenta povezanosti

#include<iostream>
#include<vector>
#include<queue>

using namespace std;


class Graph{
    public:
    Graph(int v){
        V=v;
        susedi.resize(v);
        visited.resize(v);
        fill(visited.begin(),visited.end(),false);
    }

    void add_edge(int u, int v, int tezina){
        susedi[u].push_back(make_pair(v,tezina));
        susedi[v].push_back(make_pair(u,tezina));
    }




    void dfs(int u,int k){
        visited[u]=true;
        for(auto sused : susedi[u]){
            if(!visited[sused.first] && sused.second>=k) dfs(sused.first,k);
        }
    }
    
    void jezera(int k){
        int broj_komponenti=0;
        queue<int>red;

        for(int i=0;i<V;i++){
            if(!visited[i]) dfs(i,k);
            broj_komponenti++;
        }

        cout<<broj_komponenti-1<<endl;
    }


    private:
    int V;
    vector<vector<pair<int,int>>> susedi;
    vector<bool>visited;
};


int main(){
  
  Graph g(6);
  g.add_edge(0,3,3);
  g.add_edge(0,1,4);
  g.add_edge(0,5,1);
  g.add_edge(3,4,5);
  g.add_edge(3,2,4);
  g.add_edge(1,4,2);
  g.add_edge(4,5,2);
  g.add_edge(1,2,3);
  g.add_edge(2,5,2);

  g.jezera(4);  //k=4 npr

    return 0;
}