#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

class Ulamek {
	int p,q;
public:
	Ulamek(int _p, int _q) : p(_p), q(_q) {}
	Ulamek() : Ulamek(0,1) {}

	Ulamek& operator*=(const Ulamek& rhs) {
		p = p * rhs.p;
		q = q * rhs.q;

		return *this;
	}

	friend ostream& operator<<(ostream&, const Ulamek&);
	friend istream& operator>>(istream&, Ulamek&);
};

ostream& operator<<(ostream& os, const Ulamek& u) {
	return os << u.p << "/" << u.q;
}

istream& operator>>(istream& is, Ulamek& u) {
	is >> u.p;
	char tmp; is >> tmp;
	is >> u.q;

	return is;
}

int main(int argc, char* argv[])
{
	fstream f;

	// Czytanie danych
	f.open("test3.txt", ios::in);
	if (!f.is_open()) {
		cout << "Nie mogłem otworzyć pliku test3.txt do odczytu: tworzę nowy plik." << endl;

		f.open("test3.txt", ios::out | ios::trunc);
		if (!f.is_open()) {
			cout << "Nie mogłem utworzyć pliku test3.txt" << endl;
			return 1;
		}
	}

	vector<Ulamek> dane;
	Ulamek tmp;
	while (f >> tmp) {
		dane.push_back(tmp);
	}
	f.close();

	cout << "Liczba odczytanych obiektów: " << dane.size() << "." << endl;

	// Modyfikacja danych
	for (Ulamek &u: dane) { // uwaga na konstrukcję pętli for i referencję
		u *= Ulamek(3,4);
	}
	dane.push_back(Ulamek(1,2));

	// Zapisanie danych
	f.open("test3.txt", ios::out);
	if (!f.is_open()) {

		cout << "Nie mogłem otworzyć pliku test3.txt do zapisu" << endl;
		return 1;
	}
	for (const Ulamek& u: dane) {
		f << u << endl;
	}
	f.close();

	return 0;
}

