#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Cvor{
    int brojac;
    int nzd_segmenta;
    int min_element;
};


void build_tree(vector<int> &niz, vector<Cvor>&seg, int k, int x, int y){

if(x==y){
  seg[k].brojac=1;
  seg[k].nzd_segmenta=niz[x];
  seg[k].min_element=niz[x];
  return;
} 
int m=(x+y)/2;
build_tree(niz,seg,2*k,x,m);
build_tree(niz,seg,2*k+1,m+1,y);

//nzd roditelja je nzd( levo.nzd , desno,nzd )
seg[k].nzd_segmenta=__gcd(seg[2*k].nzd_segmenta,seg[2*k+1].nzd_segmenta);

if(seg[2*k].min_element < seg[2*k+1].min_element){
    seg[k].min_element=seg[2*k].min_element;
    seg[k].brojac=seg[2*k].brojac;  
}
else if(seg[2*k+1].min_element < seg[2*k].min_element){
    seg[k].min_element=seg[2*k+1].min_element;
    seg[k].brojac=seg[2*k+1].brojac;  
}
else{
  seg[k].min_element=seg[2*k].min_element;
  seg[k].brojac=seg[2*k].brojac + seg[2*k+1].brojac;  
}

}




Cvor broj_delilaca(vector<Cvor>&seg,int k, int x, int y, int a , int b){
  
  Cvor rez;

  if(x>b || y<a){
    rez.brojac=0;
    rez.min_element=0;
    rez.nzd_segmenta=0;
    return rez;
  }
  if(x>=a && y<=b) {
    rez.nzd_segmenta=seg[k].nzd_segmenta;
    rez.min_element=seg[k].min_element;
    if(rez.min_element != rez.nzd_segmenta)
        rez.brojac=0;
    else
        rez.brojac=seg[k].brojac;    

    return rez;
  }

  int m=(x+y)/2;

  Cvor levo=broj_delilaca(seg,2*k,x,m,a,b);
  Cvor desno=broj_delilaca(seg,2*k+1,m+1,y,a,b);
 
  if(levo.nzd_segmenta  && desno.nzd_segmenta){
    rez.nzd_segmenta=__gcd(levo.nzd_segmenta,desno.nzd_segmenta);
    int min=std::min(levo.min_element,desno.min_element);
    if(min != rez.nzd_segmenta){
      rez.brojac=0;
      rez.min_element=0;
      rez.nzd_segmenta=0;
    }
    else{
      if(levo.min_element == desno.min_element){
        rez.min_element=levo.min_element;
        rez.brojac=levo.brojac + desno.brojac;
      }
      else if(levo.min_element< desno.min_element){
        rez.min_element=levo.min_element;
        rez.brojac=levo.brojac;
      }
      else{
        rez.min_element=desno.min_element;
        rez.brojac=desno.brojac;
      }
    }
    return rez;
  }
  
  else if(levo.nzd_segmenta) return levo;
  else return desno;
}










int main(){

   vector<int> niz={5,2,3,4,6,4,7,8};
   int n=niz.size();

   int height=ceil(log2(n));
   int size=2*pow(2,height);

   vector<Cvor> seg(size);

   build_tree(niz,seg,1,0,n-1);

   Cvor rez=broj_delilaca(seg,1,0,n-1,0,3);
          //a=0 b=3 seg u pocetnom nizu na ko  trazimo delioce

   cout<<rez.brojac<<" "<<rez.nzd_segmenta<<" "<<rez.min_element<<endl;        

  return 0;
}


