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
        topsort_poredak.resize(v);
        stepeni.resize(v);
        fill(stepeni.begin(),stepeni.end(),0);
    }
    
    void add_edge(int u, int v){
        susedi[u].push_back(v);
        stepeni[v]++;
        pair<int,int> p(u,v);
        edges.push_back(p);
    }

    void topsort(){
        queue<int> red;
        for(int i=0;i<V;i++){
            if(stepeni[i]==0) red.push(i);
        }
        int pom;
        while(!red.empty()){
            pom=red.front();
            red.pop();
            topsort_poredak.push_back(pom);       //!!!!!!!!!!!!!!!!
            for(int sused : susedi[pom]){
                stepeni[sused]--;
                if(stepeni[sused]==0) red.push(sused);
            }
        }
    }


   /* void dfs(int cvor){
        visited[cvor]=true;
        for(int sused : susedi[cvor]){
            if(visited[sused]) return true;
            else if(dfs(sused)) return true;
         }
        return false;
    }*/



   void dodaj_max_grana(){
       topsort();
       for(int i=0; i<V;i++){   //pozicije u topsort poretku
            for(int sused : susedi[topsort_poredak[i]])
                  visited[sused]=true;    //da nebismo dodavali grane koje vec postoje
            for(int j=i+1; j<V; j++){
                if(!visited[topsort_poredak[j]]){
                    pair<int,int> p(topsort_poredak[i],topsort_poredak[j]);
                    edges.push_back(p);
                    added_edges.push_back(p);
                }
                visited[topsort_poredak[j]]=false;   //akos tignemo do grane koja je bila visited treba da stavimo da nije posecena da nebi u sledecem koraku propustili da dodamo granu ka ovom cvoru ako je to potrebno
            }
       }

       /*//sad je radila proveru dfs-m da li postoji ciklus ali ja mislim da ne mora
       if(dfs(0)) //ima ciklus
       else   //neam ciklus

       //ispis svih grana...*/
   }
   




    private:
    int V;
    vector<vector<int>> susedi;
    vector<bool> visited;
    vector<int>stepeni;
    vector<pair<int,int>>edges;   //!!
    vector<pair<int,int>>added_edges;   //!!
    vector<int> topsort_poredak;  //!!
};



int main(){

    Graph g(6);

  g.add_edge(2, 3);
  g.add_edge(3, 1);
  g.add_edge(4, 0);
  g.add_edge(4, 1);
  g.add_edge(5, 0);
  g.add_edge(5, 2);

  g.dodaj_max_grana();


    return 0;
}