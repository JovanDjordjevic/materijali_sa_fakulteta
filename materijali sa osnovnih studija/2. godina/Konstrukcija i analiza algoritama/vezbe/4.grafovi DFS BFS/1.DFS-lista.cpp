#include<iostream>
#include<vector>
#include<list>
#include<cstdlib>

using namespace std;


void dfs(int cvor){

  //dolazna obrada

  posecen[cvor]=true;
  for(auto it: lista[cvor].begin() ; it!+lista[cvor].end(); it++){
    if(!visited[*it]){
      DFS(*it);
    }
  }
  //odlazna obrada

}



int main(){

 ...

  return 0;
}
