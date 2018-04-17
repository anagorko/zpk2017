#include <iostream>
#include <vector>

using namespace std;

int binary_search(vector<int> &w, int a)
{
    int p=0;
    int k=w.size()-1;

    while(p<k)
    {
        int m=(p+k)/2;
        if (w[m]<a) p=m+1;
        else k=m;
    }
    if (w[p]==a) return p;
    else return -1;
}

// zwraca indeks elementu a w wektorze w lub -1 jeżeli nie ma tego elementu
// wektor w jest uporządkowany w kolejności rosnącej

int main()
{
    vector<int> wektor;
    wektor.push_back(5);
    wektor.push_back(15);
    wektor.push_back(17);
    wektor.push_back(21);
    wektor.push_back(37);
    wektor.push_back(44);
    wektor.push_back(48);
    wektor.push_back(49);
    wektor.push_back(57);
    wektor.push_back(60);
    wektor.push_back(71);

    cout << "Pozycja 48: " << binary_search(wektor, 48) << endl;
    cout << "Pozycja 47: " << binary_search(wektor, 47) << " nie ma wiec -1"<< endl;
}
