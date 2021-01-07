#include<iostream>
#include<vector>
#include<queue>
#include<climits>

using namespace std;

struct compare{
    bool operator()(pair<int,int>&p1,pair<int,int>&p2){
        return p2.second > p2.second;
    }
};




class Graph{
   public:
   Graph(int v){
       V=v;
       susedi.resize(v);
       distances.resize(v); 
       pronadjen_put.resize(v); 
   }

   void add_edge(int u, int v, int tezina){
       susedi[u].push_back(make_pair(v,tezina));
       susedi[v].push_back(make_pair(u,tezina));
   }
 

    //u hipu su parovi (cvor,rastojanje do cvora) i na vrhu je apr kom je rastojanje najmanje
     //ovde VISE PUTA pozivamo dijsktrim pa fill MORA svaki put umesto u konstruktoru
   int dijkstra(int u, int v, int izbegni){
       priority_queue<pair<int,int>,vector<pair<int,int>>,compare> heap;
       fill(distances.begin(),distances.end(),INT_MAX);
       fill(pronadjen_put.begin(),pronadjen_put.end(),false);

       distances[u]=0;
       heap.push(make_pair(u,distances[u]));
         
       pair<int,int>tmp;
       while(!heap.empty()){
           tmp=heap.top();
           heap.pop();
           if(pronadjen_put[tmp.first]) continue;

           pronadjen_put[tmp.first]=true;
           for(auto sused : susedi[tmp.first]){
               if(sused.first==izbegni) continue;
               if(distances[sused.first] > distances[tmp.first]+sused.second){
                   distances[sused.first]=distances[tmp.first]+sused.second;
                   heap.push(make_pair(sused.first,distances[sused.first]));
               }
           }
       }
       return distances[v];
   }

   
   int put_sa_cvorom(int start,int finish, int middle){
       return dijkstra(start,middle,-1) + dijkstra(middle,finish,-1);  //-1 jer ne mroamo da izbegavamo nijedan
   }

   int put_bez_cvora(int start,int finish,int avoid){
       return dijkstra(start,finish,avoid);
   }







    private:
    vector<vector<pair<int,int>>>susedi;
    int V;
    vector<int>distances;
    vector<bool>pronadjen_put;
};







int main ()
{
  Graph g(4);

  g.add_edge(0, 1, 1);
  g.add_edge(1, 3, 3);
  g.add_edge(1, 2, 2);
  // Dodati ovu granu i videti ponasanje
  // g.add_edge(0, 2, 8);


  cout<<g.put_sa_cvorom(0,2,3)<<endl;   //(od,do,sa)

  int rezultat = g.put_bez_cvora(0,2,1);   //(od,do,bez)
  
  if(rezultat==INT_MAX) cout<<"nema puta";
  else cout<<rezultat<<endl;
  
  return 0;
}