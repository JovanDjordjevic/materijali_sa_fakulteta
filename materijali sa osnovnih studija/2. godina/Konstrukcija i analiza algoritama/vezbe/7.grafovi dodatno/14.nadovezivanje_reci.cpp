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
    ulazni_stepeni.resize(v);
    fill(ulazni_stepeni.begin(),ulazni_stepeni.end(),0);
}

void add_edge(int u,int v){
    susedi[u].push_back(v);
    ulazni_stepeni[v]++;
}
void dfs(int u){
    visited[u]=true;
    for(int sused : susedi[u]){
        if(!visited[sused]) dfs(sused);
    }
}





bool ojler(){
    //upotrebimo kosaraju algoritam, ako psotoji ojlerov ciklus
    //onda je nadovezivanje moguce
}




//dodajemo rec kao granu od prvog do poslednjeg slova
void dodaj_reci(vector<string> reci){
    for(string rec : reci)
        add_edge(rec[0]-'a' , rec[rec.size()-1]-'a');
}

private:
vector<vector<int>>susedi;
int V;
vector<bool> visited;
vector<int> ulazni_stepeni;
};


int main(){

    Graph g(MAX);
    vector<string>reci={"programmer", "ridiculous", "speed", "deep"};
    g.dodaj_reci(reci);

    cout<<(g.ojler(reci[0][0]-'1') ? "mogu\n" : "ne mogu\n";


    return 0;
}