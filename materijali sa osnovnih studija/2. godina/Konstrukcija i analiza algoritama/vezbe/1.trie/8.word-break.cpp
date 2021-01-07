#include<iostream>
#include<unordered_map>
#include<vector>
#include<string>

using namespace std;


struct Cvor{
	Cvor(){
		is_leaf=false;
	}
	bool is_leaf;
	unordered_map<char,Cvor*> nodes;
};

void dodaj(Cvor *koren, string &rec,int i){
	if(i==rec.size()){
		koren->is_leaf=true;
		return;
	}
	auto it=koren->nodes.find(rec[i]);
	if(it==koren->nodes.end()){
		koren->nodes[rec[i]]=new Cvor();
	}
	dodaj(koren->nodes[rec[i]],rec,i+1);
}





bool word_break(Cvor *koren, string &rec){
	int n=rec.size();
	vector<bool> valid(n);

	valid[0]=true;
	Cvor *tmp;

	for(int i=0;i<n; i++){
			if(valid[i]){
				tmp=koren;
				for(int j=i; j<n; j++){
					auto it=tmp->nodes.find(rec[j]);
					if(it==tmp->nodes.end()){
						break;
					}

					tmp=tmp->nodes[rec[j]];

					if(tmp->is_leaf){
						valid[j+1]=true;
					}

					if(j==n-1){
						return true;
					}
				}
			}
	}

	return false;
}




int main(){

	vector<string> words = { "this", "th", "is", "famous", "word", "break", "b", "r", "e", "a", "k", "br", "bre", "brea", "ak", "prob", "lem" };
	//vector<string> words = { "word", "br", "k", "b", "ea", "oblem" };		

	Cvor *koren=new Cvor();

	for(string s : words){
		dodaj(koren,s,0);
	}

    
	string str="wordbreakproblem";

	if(word_break(koren,str)){
		cout<<"moze"<<endl;
	}
	else{
		cout<<"ne moze"<<endl;
	}


	return  0;
}