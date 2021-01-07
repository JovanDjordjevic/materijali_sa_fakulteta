#include<iostream>
#include<vector>
#include<climits>
#include<queue>

using namespace std;

struct compare{
    bool operator()(pair<int,int> &p1,pair<int,int>&p2){
        return p1.second > p2.second;
    }
};

class Graph{
   public:
   Graph(int v){
       V=v;
       susedi.resize(v);
       distances.resize(v);
       fill(distances.begin(),distances.end(),INT_MAX);
       pronadjen_put.resize(v);
       fill(pronadjen_put.begin(),pronadjen_put.end(),false);
   }

  void add_edge(int u, int v){
      susedi[u].push_back(v);
      susedi[v].push_back(u);
  }
  void dodaj_policijsku_stanicu(int station){
      policijske_stanice.push_back(station);
  }
  

//ovde nam je heap polje grafa jer prvo u njega ubacujemo cvorove u kojima 
//su policijske stanice pa nemroamo u dijkstrinom da pravimo heap, ovim 
//se postize da ce se cvoru bez policijske prici sa strane sa kojoj joj je najbliza policijska
//(vidi se u grafu datom u mainu)

    void dijkstra(){
        pair<int,int> tmp;
        while(!heap.empty()){
            tmp=heap.top();
            heap.pop();
            if(pronadjen_put[tmp.first]) continue;
            
            pronadjen_put[tmp.first]=true;

            for(auto sused : susedi[tmp.first]){
                if(distances[sused] > distances[tmp.first] + 1){   //+1 jer neammo date tezine pa pretpostavljamo da su sve duzine 1
                    distances[sused]=distances[tmp.first]+1;
                    heap.push(make_pair(sused,distances[sused]));
                }
            }
        }
    }


    void najblize_stanice(){
        for(int stanica : policijske_stanice){
            distances[stanica]=0;
            heap.push(make_pair(stanica,distances[stanica]));
        }
        dijkstra();

        for(int i=0;i<V;i++){
            cout<<i<<" "<<distances[i]<<endl;
        }
    }

   



    private:
    vector<vector<int>>susedi;  
    vector<int>distances;
    int V;
    vector<bool>pronadjen_put;
    vector<int>policijske_stanice;
    priority_queue<pair<int,int>,vector<pair<int,int>>,compare> heap;
};






int main(){
    
    Graph g(6);

  g.add_edge(0, 1);
  g.add_edge(0, 5);
  g.add_edge(1, 2);
  g.add_edge(1, 5);
  g.add_edge(2, 3);
  g.add_edge(2, 4);
  g.add_edge(2, 5);
  g.add_edge(3, 4);

  g.dodaj_policijsku_stanicu(0);
  g.dodaj_policijsku_stanicu(4);

  g.najblize_stanice();
    return 0;
}