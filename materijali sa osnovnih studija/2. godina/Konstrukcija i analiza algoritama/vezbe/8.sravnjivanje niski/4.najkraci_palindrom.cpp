#include<iostream>
#include<vector>
#include<string>

using namespace std;


bool jePalindrom(string &s, int n){
    for(int i=0,j=n-1; i<j; i++,j--)
        if(s[i]!=s[j]) return false;
    return true;    
}


//ide sa desna na levo pa je prvi koji se vrati zapravo najduzi
int duzinaNajduzegPalindromPrefiksa(string &s){
    for(int n=s.size(); n>=1; n--){
        if(jePalindrom(s,n)) return n;
    }
    return 1;      
}



int main(){

   string s;
   cin>>s;
  
   int duzinaPrefiksa=duzinaNajduzegPalindromPrefiksa(s);
   int duzinaSufiksa=s.size()-duzinaPrefiksa;
   
   cout<<duzinaSufiksa + duzinaPrefiksa + duzinaSufiksa<<endl;
 
   return 0;
}