//njeno resenje, ovo NE ispisuje put sa najmanjim brojem grana ako puteva ima vise iako se trazi u zadataku (vidi se kada se doda poslednja grana)

#include<iostream>
#include<vector>
#include<queue>
#include<climits>
#include<stack>

using namespace std;



struct compare{
    bool operator()(pair<int,int> &p1, pair<int,int>&p2){
        return p1.second > p2.second;
    }
};


class Graph{

    public:
    Graph(int v){
        V=v;
        susedi.resize(v);
        distances.resize(v);
        fill(distances.begin(),distances.end(),INT_MAX);  //kad ne znamo rastojanja na pocetku onda su beskonacno
        pronadjen_put.resize(v);
        fill(pronadjen_put.begin(),pronadjen_put.end(),false);
        najkraci_put.resize(v);
        fill(najkraci_put.begin(),najkraci_put.end(),INT_MAX);  //isto
        parents.resize(v);
        fill(parents.begin(),parents.end(),-1);
     } 

     void add_edge(int u, int v, int tezina){
         susedi[u].push_back(make_pair(v,tezina));
         susedi[v].push_back(make_pair(u,tezina));

     }




     void dijkstra(int u, int v){
         priority_queue<pair<int,int>,vector<pair<int,int>>,compare> heap;
         distances[u]=0;
         heap.push(make_pair(u,distances[u]));
         najkraci_put[u]=0;

         pair<int,int> tmp;
         while(!heap.empty()){
             tmp=heap.top();
             heap.pop();
             if(pronadjen_put[tmp.first])   
                        continue;    //!!!!

             pronadjen_put[tmp.first]=true;

             for(auto sused : susedi[tmp.first]){
                 if(distances[sused.first]>=distances[tmp.first] + sused.second && 
                 najkraci_put[sused.first] > najkraci_put[tmp.first]+1){             //ovi sa +1 sluze za brojanje grana na putu, u standardnom dijkstrinom nam ne trebaju
                     najkraci_put[sused.first] = najkraci_put[tmp.first]+1;
                     parents[sused.first]=tmp.first;
                     distances[sused.first]=distances[tmp.first]+sused.second;
                     heap.push(make_pair(sused.first,distances[sused.first]));
                 }
             }
         }
        
        stack<int> put;
        while(parents[v]!=-1){
            put.push(v);
            v=parents[v];
        }
        put.push(v);
        int n=put.size();
        int node;
        while(n>0){
            node=put.top();
            put.pop();
            n--;
            if(n>0) cout<<node<<" -> ";
            else cout<<node<<endl;
        }
     }



    private:
    vector<vector<pair<int,int>>>susedi;
    int V;
    vector<int> distances;         //duzine do svakog
    vector<bool>pronadjen_put;      
    vector<int>najkraci_put;        //duzina najkraceg do itog cvora
    vector<int>parents;             //roditelji svakog cvora, za rekonstrukciju
};



int main(){

   Graph g(5);

  g.add_edge(0, 1, 1);
  g.add_edge(1, 2, 4);
  g.add_edge(2, 3, 7);
  g.add_edge(3, 4, 2);
  g.add_edge(4, 0, 11);
  // testirati kvalitet resenja po pitanju broja grana, ako je poslednja grana
  //g.add_edge(4, 0, 10);

  // g.add_edge(0, 1, 1);
  // g.add_edge(1, 2, 2);
  // g.add_edge(2, 3, 3);
  // g.add_edge(0, 4, 1);
  // g.add_edge(4, 5, 2);
  // g.add_edge(5, 6, 3);
  // g.add_edge(6, 7, 4);
  // g.add_edge(7, 3, 5);

  g.dijkstra(0, 3);

    return 0;
}