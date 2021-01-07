#include<iostream>
#include<vector>

using namespace std;


void kmpPreprocesiraj(const string &uzorak, vector<int>&b){
    int m=uzorak.size();   //u knjizi stoji da bi ovoo trebalo da bude b.size() ali mislim da je to greska
    int i=0;
    int j=-1;
    b[i]=j;

    while(i<m){
        while(j>=0 && uzorak[i]!=uzorak[j])
                j=b[j];
        i++;
        j++;
        b[i]=j;        
    }
}



void kmpTrazi(string &tekst,string &uzorak, vector<int>&b){
    int n=tekst.size();
    int m=uzorak.size();
    int i=0;
    int j=0;
    while(i<n){
        while(j>=0 && tekst[i]!=uzorak[j])
                j=b[j];
        i++;
        j++;
        if(j==m){
            cout<<"uzorak se nalazi na poz "<<i-j<<endl;
            j=b[j];
        }        
    }
}




int main(){
   string tekst="abrakadabra";
   string uzorak="ra";

   int m=uzorak.size();
   vector<int> b(m+1);

   kmpPreprocesiraj(uzorak, b);
   kmpTrazi(tekst,uzorak,b);

   return 0;
}