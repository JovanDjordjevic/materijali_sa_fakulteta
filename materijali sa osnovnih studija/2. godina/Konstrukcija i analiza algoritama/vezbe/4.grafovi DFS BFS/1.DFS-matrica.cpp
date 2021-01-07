#include<iostream>
#include<vector>

using namespace std;

void DFS<vector<vector<int>>&matrica, vector<bool>&oznaceni,int cvor){
    oznaceni[cvor]=true;
    for(int i=0;i<matrica[cvor].size();i++){
        if(matrica[cvor][i]!=0 && !oznaceni[i]){
                    DFS(matrica,oznaceni, i)
        }
    }
}


int main(){
int n;
cin>>n;

vector<vector<int>>matrica(n);
vector<bool> oznaceni(n);

for(i=0;i<n;i++) oznaceni[i]=false;

for(i=0;i<n;i++){
  matrica[i].resize(n);
  for(int j=0;j<n;j++) cin>>matrica[i][j];

}

DFS(matrica, oznaceni,0);

}