#include <iostream>
#include<vector>
using namespace std;


int number_of(vector<int> &w, int a){
int b = w.size();
int n = 0;
for (int m = 0; m <= b; m++ ){
    if(w[m] == a){
        n=n+1;
    } else {
    n = n ;}
}
return n;
};
// zwraca liczbę wystąpień elementu a w wektorze w (0 jeżeli nie ma tego elementu)
// wektor w jest uporządkowany w kolejności rosnącej

int main()
{
  vector<int> k  {1,3,10,15,20,78,89,123,123,123,123,456,789};
  int z =  number_of(k, 123);
    cout << z << endl;
}
