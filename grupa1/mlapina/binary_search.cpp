#include <iostream>
#include<vector>
using namespace std;


int binary_search(vector<int> &w, int l){
int a=0;
int b = w.size();
while(b-a > 1 ){
    int m = (a+b)/2;
    if(w[m]<= l){
        a = m;}
        else {b = m ;}

};
return a;
};

// zwraca indeks elementu a w wektorze w lub -1 jeżeli nie ma tego elementu
// wektor w jest uporządkowany w kolejności rosnącej

int main()
{
  vector<int> k  {1,3,10,15,20,78,89,123,123,123,123,456,789};
  int z =  binary_search(k, 123);
    cout << z << endl;
}
