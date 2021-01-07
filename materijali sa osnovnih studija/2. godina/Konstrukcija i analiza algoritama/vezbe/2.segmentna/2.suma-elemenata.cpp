#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;


void build_tree(vector<int>&niz, vector<int>&seg, int k, int x,int y){
  if(x==y){
    seg[k]=niz[x]; 
    return;
  }

  int m=(x+y)/2;

  build_tree(niz,seg,2*k,x,m);
  build_tree(niz,seg,2*k+1,m+1,y);

  seg[k]=seg[2*k]+seg[2*k+1];
}






int sum_seg(vector<int>&seg,int x, int y, int a, int b, int k){   //!!!!

if(x>b || y<a) return 0;
if(x>=a && y<=b) return seg[k];

int m=(x+y)/2;

return sum_seg(seg,x,m,a,b,2*k) + sum_seg(seg,m+1,y,a,b,2*k+1);
}






int main(){

  vector<int> niz = { 1, 2, 3, 4, 5, 6, 7, 8 };
  int n=niz.size();

  int height=ceil(log2(n));
  int size=2*pow(2,height);

  vector<int> seg(size);

  build_tree(niz,seg,1,0,n-1);

  cout<<sum_seg(seg,0,n-1,0,2,1)<<endl;
  //seg,x=0 y=n-1 to je deo pocetnog niza koji obuhvata cvor u seg na poz k,
  //a=0 b=2  to je segment u pocetnom nizu ciji zbir trazimo, k=1 je tekuci cvor u seg

  return 0;
}
