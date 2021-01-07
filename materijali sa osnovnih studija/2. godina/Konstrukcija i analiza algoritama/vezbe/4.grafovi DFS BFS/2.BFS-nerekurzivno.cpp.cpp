#include<iostream>
#include<vector>
#include<stack>

using namespace std;

vector<vector<int>> susedi { lista suseda  }

void bfs(int cvor){
 int brojCvorova=susedi.size();
 vector<bool> visited(brojCvorova,false);
 
 queue<int> red;
 queue.push(cvor);
 while(!queue.empty()){
     cvor=red.front();
     red.pop();
     if(!visieted[cvor]){
	visited[cvor]=true;
	cout<<cvor;
	for(auto it : susedi[cvor]){
		if(!visited[*it]);
		red.push(*it);
	}
     }

  }

}

int main(){

bfs(0);
return 0;

}