#include <iostream>
#include <string>
#include <vector>

using namespace std;


int main(){
  
  string s;
  cin>>s;

  int N=2*s.size()+1;  //broj POZICIJ (indeksi i one poz na kojima je | )
  vector<int> d(N);    //na itoj poz je duzina najduzeg palindroma kom je centar na itoj POZICIJI

  int c=0;    //[l,r] je palindrom sa centrom u c
  int r=0;    //l=c-(r-c)  
  for(int i=0; i<N; i++){
        int i_sim=c-(i-c);  //karakter simetrican krakteru i u odnosu na c
        if(i<r && i+d[i_sim]<r)
             d[i]=d[i_sim];
        else{
            d[i]= i<=r ? r-i : 0;   
            if((i+d[i])%2==1) 
                d[i]++;
            while(i-d[i]-1 >=0 && i+d[i]+1<N && s[(i-d[i]-1)/2]==s[(i+d[i]+1)/2])
                d[i]+=2;        
        }  

        if(i+d[i]>r){
                c=i;
                r=i+d[i];
        }        
  }
  
  
  int maxDuzina=0,maxCentar;
  for(int i=0;i<N;i++){
          if(d[i]>maxDuzina){
                  maxDuzina=d[i];
                  maxCentar=i;
          }
  }

  int maxPocetak=(maxCentar-maxDuzina)/2;
  
  cout<<s.substr(maxPocetak,maxDuzina)<<endl;
  

  return 0;
}