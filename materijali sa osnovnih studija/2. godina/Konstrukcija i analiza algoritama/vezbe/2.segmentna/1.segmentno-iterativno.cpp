#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;


void build_tree(vector<int> &niz, vector<int> &segmentno, int n){
  
   for(int i=0,x=n; i<n; i++,x++){
       segmentno[x]=niz[i];
   }
   
   for(int k=n-1; k>=1 ;k--){
     segmentno[k]=segmentno[2*k]+segmentno[2*k+1];
   }

}




int main(){

  vector<int> niz={1,2,3,4,5,6,7,8};
  int n=niz.size();

  int height=ceil(log2(n));   //mora ovako, treba naci prvi stepen dvojke veci od duzine niza 
  int size=2*pow(2,height);   //i pomnoziti ga sa dva da se dobije visina seg stabla

  vector<int> segmentno(size);

  build_tree(niz,segmentno,n);

  for(int x : segmentno){
    cout<<x<<" ";
  }

  return 0;
}