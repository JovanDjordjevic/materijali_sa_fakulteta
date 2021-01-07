#include<iostream>
#include<vector>

using namespace std;

class Graph{

    public:
    Graph(int v){
        V=v;
        time=0;
        susedi.resize(v);
        visited.resize(v);
        fill(visited.begin(),visited.end(),false);
        parents.resize(v);
        fill(parents.begin(),parents.end(),-1);
        times.resize(v);
        fill(times.begin(),times.end(),-1);
        lower_times.resize(v);
        fill(lower_times.begin(),lower_times.end(),-1);
        mostovi.resize(v);                                  //!!!!
    }



    void add_edge(int u, int v){
        susedi[u].push_back(v);
        susedi[v].push_back(u);
    }

/*void DFS(int u)
  {
    visited[u] = true;
    times[u] = lower_times[u] = time;
    time++;
    int children = 0;
    auto begin = adjacency_list[u].begin();
    auto end = adjacency_list[u].end();

    while (begin != end) {
        if (!visited[*begin]) {
        parents[*begin] = u;
        DFS(*begin);
        children++;
         lower_times[u] = lower_times[*begin] < lower_times[u] ? lower_times[*begin] : lower_times[u];
         if (times[u] < lower_times[*begin])
          std::cout << u << " -> " << *begin << "\n";
        }
         else if (*begin != parents[u]) {
        lower_times[u] = lower_times[u] < lower_times[*begin] ? lower_times[u] : lower_times[*begin];
        }
      begin++;
    }
  }*/

    void dfs(int u){
        visited[u]=true;
        times[u]=lower_times[u]=time;
        time++;
        //int broj_dece=0;
        for(int sused : susedi[u]){
            if(!visited[sused]){
                parents[sused]=u;
                dfs(sused);
                //broj_dece++;
                lower_times[u]=min(lower_times[u],lower_times[sused]);
                if(times[u]<lower_times[sused])
                        cout<<u<<" "<<sused<<endl;  
            }
            else if(sused!=parents[u]){
                    lower_times[u]=min(lower_times[u],lower_times[sused]);
                }
        }
    }
    

    void ispisi_mostove(){
        for(auto p : mostovi){
            cout<<p.first<<" "<<p.second<<endl;
        }
    }



    private:
    int V;
    vector<vector<int>>susedi;
    vector<bool>visited;
    vector<int>parents;
    int time;
    vector<int>times;
    vector<int>lower_times;
    vector<pair<int,int>> mostovi;            //!!!
};





int main(){

    Graph g(5);

  g.add_edge(0, 2);
  g.add_edge(0, 3);
  g.add_edge(1, 0);
  g.add_edge(2, 1);
  g.add_edge(3, 4);

  g.dfs(0);
  // g.ispisi_mostove();

    return 0;
}