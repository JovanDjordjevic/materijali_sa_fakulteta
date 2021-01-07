#include<iostream>
#include<vector>
#include<queue>

#define MAX 26
using namespace std;

class Graph{
public:
Graph(int v){
    V=v;
    visited.resize(v);
    fill(visited.begin(),visited.end(),false);
    matrica.resize(v);
    for(int i=0;i<v;i++){
        matrica[i].resize(v);
    }
    ulazni_stepeni.resize(v);
    fill(ulazni_stepeni.begin(),ulazni_stepeni.end(),0);
}

void add_edge(int u,int v){
    matrica[u][v]=1;
    ulazni_stepeni[v]++;
}

void topsort(){
    queue<int>red;
    for(int i=0;i<V;i++){
        if(ulazni_stepeni[i]==1) red.push(i);
    }
    int tmp;
    while(!red.empty()){
        tmp=red.front();
        red.pop();
        topsort_poredak.push_back(tmp);
        
        for(int i=0;i<V;i++){
            if(matrica[tmp][i]!=0){
                ulazni_stepeni[i]--;
                if(!ulazni_stepeni[i]) red.push;
            }
        }
    }
}


//proveravamo da li imamo granu izmedju svaka dva uzastopna cvora u topsort poretku
//i to od manjeg ka vece, (u pre v u topsort => trazimo granu u->v)
//ako nema neke od tih grana onda nema hamiltonog puta
bool has_hamilton_path(){
    topsort();
    for(int i=0;i<V-1;i++){
        if(matrica[topsort_poredak[i]][topsort_poredak[i+1]]==0)
          return false;
    }
    return true;
}



private:
vector<vector<int>>matrica;
int V;
vector<bool> visited;
vector<int> ulazni_stepeni;
vector<int>topsort_poredak;
};


int main(){

   Graph g(4);

  // Ima
  // g.add_edge(0, 1);
  // g.add_edge(1, 2);
  // g.add_edge(2, 3);

  // Nema
  g.add_edge(0, 1);
  g.add_edge(1, 2);
  g.add_edge(1, 3);
  g.add_edge(0, 3);

  if(g.has_hamilton_path()) cout<<"ima put"<<endl;
  else cout<<"nema"<<endl;

    return 0;
}