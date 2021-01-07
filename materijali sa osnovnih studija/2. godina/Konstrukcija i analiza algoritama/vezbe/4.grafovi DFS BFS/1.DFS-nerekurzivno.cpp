#include<iostream>
#include<stack>
#include<vector>

using namespace std;




int main(){
vector<vector<int>> susedi= {{1, 2}, {3, 4}, {5}, {}, {6, 7}, {8}, {}, {}, {}};

vector<bool> posecen(susedi.size(),false);

stack<int> dfs_stek;

dfs_stek.push(0);

while(!dfs_stek.empty()){
		int cvor=dfs_stek.top();
		dfs_stek.pop();
		if(!posecen[cvor]){
		posecen[cvor]=true;

		for(int i=0;i<susedi[cvor].size();i++){   //for(int sused : susedi[cvor])
			if(!posecen[susedi[cvor][i]]){        //if(!posecen[sused]) ...
				dfs_stek.push(susedi[cvor[i]]);
			}
		}

		}
}

}