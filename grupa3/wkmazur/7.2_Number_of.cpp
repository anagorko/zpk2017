#include <iostream>
#include <vector>

using namespace std;

int number_of(vector<int> &w, int a)
{
    int p=0;
    int k=w.size()-1;
    int licznik;

    while(p<k)
    {
        int m=(p+k)/2;
        if (w[m]<a) p=m+1;
        else k=m;
    }
    if (w[p]==a) licznik=1;
    else licznik=0;

    while(w[p+1]==a){
        licznik++;
        p++;
    }

    return licznik;
}

// zwraca liczbę wystąpień elementu a w wektorze w (0 jeżeli nie ma tego elementu)
// wektor w jest uporządkowany w kolejności rosnącej

int main()
{
    vector<int> wektor;
    wektor.push_back(5);
    wektor.push_back(15);
    wektor.push_back(15);
    wektor.push_back(15);
    wektor.push_back(15);
    wektor.push_back(15);
    wektor.push_back(15);
    wektor.push_back(15);
    wektor.push_back(15);
    wektor.push_back(15);
    wektor.push_back(15);
    wektor.push_back(15);
    wektor.push_back(15);
    wektor.push_back(15);
    wektor.push_back(15);
    wektor.push_back(15);
    wektor.push_back(15);
    wektor.push_back(15);
    wektor.push_back(15);
    wektor.push_back(15);
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

    cout << "Ilosc 15: " << number_of(wektor, 15) << endl;
    cout << "Ilosc 47: " << number_of(wektor, 47) << " nie ma wiec 0"<< endl;
    cout << "Ilosc 71: " << number_of(wektor, 71) << endl;
}
