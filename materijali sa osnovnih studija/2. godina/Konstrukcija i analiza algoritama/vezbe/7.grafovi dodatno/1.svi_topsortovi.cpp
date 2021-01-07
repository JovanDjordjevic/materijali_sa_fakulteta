#include<iostream>
#include<vector>

using namespace std;


class Graph{

public:
Graph(int v){
    V=v;
    susedi.resize(v);
    stepeni.resize(v);
    fill(stepeni.begin(),stepeni.end(),0);
}

void add_edge(int u, int v){
    susedi[u].push_back(v);
    stepeni[v]++;
}


void svi_topsort_rekurzivna(vector<int> &put,vector<bool> &discovered){
    for(int i=0;i<V;i++){
        if(stepeni[i]==0 && !discovered[i]){
            for(int sused : susedi[i]){
                stepeni[sused]--;
            }
            put.push_back(i);
            discovered[i]=true;
            svi_topsort_rekurzivna(put,discovered);
            for(int sused : susedi[i]){
                stepeni[sused]++;
            }
            put.pop_back();
            discovered[i]=false;
        }
    }
    
    if(put.size()==V){
        for(int j : put){
            cout<<j<<" ";
        }
        cout<<endl;
    }
}




void svi_topsort(){
   vector<int> put;  //trenutno topsort uredjenje
   vector<bool> discovered(V);
   svi_topsort_rekurzivna(put,discovered);
}



private:
int V;
vector<vector<int>>susedi;
vector<int>stepeni;

};



int main(){

Graph g(8);
g.add_edge(0,6);
g.add_edge(1,2);
g.add_edge(1,4);
g.add_edge(1,6);
g.add_edge(3,0);
g.add_edge(3,4);
g.add_edge(5,1);
g.add_edge(7,0);
g.add_edge(7,1);

g.svi_topsort();

return 0;
}


