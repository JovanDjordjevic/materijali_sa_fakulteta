#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;


//broj inverzija je zapravo zbir elemenata u intervalu [niz[i]+1,max]

int broj_inverzija(vector<int> &seg,int k, int x, int y, int a, int b){
  if(x>b || y<a) return 0;
  if(x>=a && y<=b) return seg[k];

  int m=(x+y)/2;
  return broj_inverzija(seg,2*k,x,m,a,b) + broj_inverzija(seg,2*k+1,m+1,y,a,b);
}



//zapravo pravimos eg stablo kao da u njega smestamo max elemenata, i na poozicije
//na kojima bi bili brojevi iz naseg niza upisujemo 1, npr ako niz[i]=12 onda
//u seg na poziciji max+12 stavimo 1 i to oznacava da se 12 javlja u nasem nizu
//index nam sluzi da usmerimo pretragu u jednu stranu
void dodaj(vector<int> &seg,int k, int x, int y, int index){
  if(x==y){
    seg[k]=1;
    return;
  }

  int m=(x+y)/2;

  if(index<=m)
        dodaj(seg,2*k,x,m,index);
  else
        dodaj(seg,2*k+1,m+1,y,index);
  

  seg[k]=seg[2*k]+seg[2*k+1];
}





int main(){

  vector<int> niz = { 3, 5, 1, 4, 6, 2, 4, 7, 8, 2, 3, 4 };

  int n=niz.size();
  
  int max=*max_element(niz.begin(),niz.end());
  int height=ceil(log2(max));  //!!!!!!!
  int size=2*pow(2,height);

  vector<int> seg(size,0);

  int rezultat=0;

  for(int i=0;i<n;i++){
      rezultat+= broj_inverzija(seg,1,1,max,niz[i]+1,max);
          //k=1, x=1 y=max deo seg koji obuhvata cvor k, a=niz[i]+1 b=max
      dodaj(seg,1,1,max,niz[i]);

  }


  cout<<rezultat<<endl;

  return 0;
}