#include<iostream>
#include<vector>
#include<climits>

using namespace std;


class Graph{
  public:
  Graph(int v){
      V=v;
      susedi.resize(v);
      matrix.resize(v);
      for(int i=0;i<v;i++){
          matrix[i].resize(v);
      }
      ukljucen_u_MST.resize(v);
      fill(ukljucen_u_MST.begin(),ukljucen_u_MST.end(),false);
      parents.resize(v);
      fill(parents.begin(),parents.end(),-1);
      edges.resize(v);
      fill(edges.begin(),edges.end(),INT_MAX);
  }

  void add_edge(int u, int v,int tezina){
      matrix[u][v]=tezina;
      matrix[v][u]=tezina;
  }  



  int min_not_in_MST(){
      int min=INT_MAX;
      int min_index=-1;
      for(int i=0;i<V;i++){
          if(ukljucen_u_MST[i]==false && edges[i]<min){
              min_index=i;
              min=edges[i];
          }
      }
      return min_index;      
  }


  void prim(int u){
      edges[u]=0;            //ovim omogucavamo da se pokrene alg, funckija iznad ce u prvom pozivu vratiti bas cvor u i on ce biti ubacen u mst
      int cvor;

      for(int i=0; i<V-1 ;i++){   //jer mst ima v-1 granu, u svakom koraku se ubacuje jedna grana(tj ubacuje se cvor kojim je odredjena grana)
            cvor=min_not_in_MST();
            ukljucen_u_MST[cvor]=true;
            for(int v=0 ; v<V; v++){
                if(matrix[cvor][v] && ukljucen_u_MST[v]==false && matrix[cvor][v] < edges[v]){
                    parents[v]=cvor;
                    edges[v]=matrix[cvor][v];
                }
            }
      }

      int cost=0;   //racunanje ukupne cene, preskacemo pocetni cvor u jer je njegov parent -1
      for(int i=0; i<V; i++)
            if(i!=u)
                cost+=matrix[i][parents[i]];

      cout<<cost<<endl;            
  }




  

  private:
  vector<vector<pair<int,int>>>susedi;
  int V;
  vector<vector<int>>matrix;//umesto distances, na poz [i][j] je tezina grane od i do j ili 0 ako ta grana ne postoji
  vector<bool>ukljucen_u_MST;  //da li je i-ti cvor u min razapinjucem stablu
  vector<int>parents;
  vector<int>edges;  //tezina grane koja povezuje i-ti cvor sa 
                     // parents[i]-tim cvorom 
};                   




int main(){ 

  Graph g(5);

  g.add_edge(0, 1, 1);
  g.add_edge(0, 2, 2);
  g.add_edge(0, 3, 3);
  g.add_edge(0, 4, 4);
  g.add_edge(1, 2, 5);
  g.add_edge(1, 4, 7);
  g.add_edge(2, 3, 6);

  g.prim(0);

    return 0;
}



