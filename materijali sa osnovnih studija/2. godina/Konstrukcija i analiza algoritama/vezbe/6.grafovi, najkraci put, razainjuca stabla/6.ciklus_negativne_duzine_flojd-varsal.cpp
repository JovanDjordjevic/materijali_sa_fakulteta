#include<iostream>
#include<climits>
#include<vector>

using namespace std;

class Graph{
    public:
    Graph(int v){
        V=v;
        matrix.resize(v);
        for(int i=0;i<v;i++){
            matrix[i].resize(v);
            for(int j=0;j<v;j++){
                if(i==j) matrix[i][j]=0;                   //inic matricu tezina, na dijagonali je 0 svugde ostalo je INTMAX
                else matrix[i][j]=INT_MAX;
        }
    }
    }
    
    void add_edge(int u,int v, int tezina){
        matrix[u][v]=tezina;                    //u usmerenmo grafu smo
    }

   
    void flojd_varsal(){
        for(int k=0;k<V;k++){                  //uzimamo svaki cvor kao serdnji
            for(int i=0;i<V;i++){               //uzimamo svaki kao pocetni
                for(int j=0;j<V;j++){           //uzimamos vaki kao krajnji
                        if(matrix[i][j] > matrix[i][k] + matrix[k][j])
                                matrix[i][j]=matrix[i][k]+matrix[k][j];
                }
            }
        }

        for(int i=0;i<V;i++)
           if(matrix[i][i]<0){        //znaci ako je u matrici najkraciuh puteva cvor SAM DO SEBE negativno udaljen onda imamo cikllus negativne tezine
               cout<<"IMA"<<endl;
               return;
           }

        cout<<"NEMA"<<endl;
        return;   
    }



    private:
    int V;
    vector<vector<int>>matrix;
};


int main(){

   Graph g(4);

  g.add_edge(0, 1, 1);
  g.add_edge(1, 2, -1);
  g.add_edge(2, 3, -1);
  g.add_edge(3, 0, -1);

  g.flojd_varsal();


    return 0;
}


