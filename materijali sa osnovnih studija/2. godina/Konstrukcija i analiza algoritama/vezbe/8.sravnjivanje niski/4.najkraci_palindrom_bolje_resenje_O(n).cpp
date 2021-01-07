#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<utility>

using namespace std;

//kada se ovaj njen deop za kmp zameni samo obicnom funkcijom za pravljenje niza B u kmp algoritmu dobije se isto resenje, izgleda da je to isto samo drugacije napisano
int duzinaNajduzegPalindromPrefiksa(string &s){
    string sObrnuto=s;
    reverse(sObrnuto.begin(),sObrnuto.end());

    string str=s+'.'+sObrnuto;

    vector<int> kmp(str.size()+1,0);
    kmp[0]=-1;

    for(int i=0;i<str.size();i++){
        int k=i;
        while(k>0 && str[i]!=str[kmp[k]])  
                k=kmp[k];
        kmp[i+1]=kmp[k]+1;        
    }
    return min(kmp[kmp.size()-1] , (int)s.size());

    /*int i=0;
    int j=-1;
    kmp[i]=j;
    while(i<str.size()){
            while(j>=0 && str[i]!=str[j])
                j=kmp[j];
            i++;
            j++;
            kmp[i]=j;    
    }
    return min(kmp[kmp.size()-1],(int)s.size());*/
}





int main(){

   string s;
   cin>>s;
  
   int duzinaPrefiksa=duzinaNajduzegPalindromPrefiksa(s);
   int duzinaSufiksa=s.size()-duzinaPrefiksa;
   
   cout<<duzinaSufiksa + duzinaPrefiksa + duzinaSufiksa<<endl;
 
   return 0;
}