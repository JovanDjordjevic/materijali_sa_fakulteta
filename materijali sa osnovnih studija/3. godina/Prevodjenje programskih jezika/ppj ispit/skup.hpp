#include<iostream>
#include<cstdlib>
#include<vector>

using namespace std;

class Skup{
    public:
         Skup(){};
         Skup(int broj1,int broj2);
         Skup(int broj);
         
         void print();
         
         void ubaci(int broj);
         
         int card();
         bool check();
         
         vector<int>skup;
};
