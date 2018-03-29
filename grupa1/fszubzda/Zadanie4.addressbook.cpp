#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

class Person
{
    string name, surname, phone, email;
    int id;

public:
	Person() {}

	void setName(string _name) {name = _name;}
	void setSurname(string _surname) {surname=_surname;}
	void setPhone(string _phone) {phone=_phone;}
	void setEmail(string _email) {email=_email;}
	void setId(int _id) {id=_id;}

	string getName() const  {return name;}
	string getSurname() const {return surname;}
	string getPhone() const {return phone;}
	string getEmail() const {return email;}
	int getId() const {return id;}

	bool operator<(const Person& p) const {
		return name < p.name;
	}

	friend ostream& operator<<(ostream &os, const Person &w){
        return os<< w.getName() <<", " << w.getSurname() <<", "<< w.getPhone() <<", "<<w.getEmail()<<", "<<w.getId()<<endl;
    }

	friend istream& operator>>(istream &is, Person &w){
        is >> w.name;
        is >> w.surname;
        is >> w.phone;
        is >> w.email;
        is >> w.id;

        return is;

	};
};

class Addressbook{
    //private: wektor który przetrzymuje Persony, metoda getFreeId sprawdza maxa w tym wektorze i dopisuje +1 jako nowe ID dla pers.
	vector<Person> p;

	int getFreeId()
	{
		int max_id = 0;
		for (auto &r: p) {
			if (r.getId() > max_id) { max_id = r.getId(); }
		}
		return max_id+1;
	}
//ios::out | ios::trunc – zawartość pliku zostanie usunięta przed zapisem
//ios::out | ios::app – informacja zostanie dopisana na końcu istniejącego pliku


public:
	Addressbook() {} //konstruktor

	void read(string filename) {   //metoda read: otwiera filename (string) i dopisuje
		Person r;

		fstream f;
		f.open(filename, ios::in);

		while (f>>r) {
			p.push_back(r);
		}
		f.close();
	}

	void write(string filename) { //usuwana jest wczesniejsza zawartosc pliku
		fstream f;

		f.open(filename, ios::out | ios::trunc);

		for (auto& r: p) {
			f << r;
		}
		f.close();
	}

	void add(Person &r) {
		r.setId(getFreeId()); // ustaw nowe Id takie jak wskazuje funkcja getFreeId()(a ona działa  tak: znajduje najwieksze Id, a zwraca te Id+1) setId bierze tylko_id
		p.push_back(r);       // dodaje do końca tablicy element podany w nawiasie.
	}

	void remove(int id) { //auto - zastępczy typ zmiennej ktory zostanie wydedukowany na podst. zmiennej.
		for (auto i = p.begin(); i < p.end(); i++) { //petla leci od poczatku do konca dynamicznej tablicy (tablica musi posiadac przynajmniej 1 element zeby uzyc)
			if (i -> getId() == id) {   //zapis i->getId() to wskaźnik (to samo co: (i).getId()?) czyli: jeżeli i.getId()==id (wskazane przez nas)=> skasuj z listy nr i
				p.erase(i); return;
			}
		}
	}

	Person& get(int id) { //to jest do modyfikowania, zwraca typ Person
		for (auto &r: p) {// idz po wektorze p i jak bedzie zadane id to zwroc ten wpis
			if (r.getId() == id) return r;
		}
		Person r;
		r.setId(id); // ustaw id na zadane
		p.push_back(r);  //dodaj ten nowy r na koniec vectora p (wiec jak uzyje sie potem funkcji sort to nie bedzie do konca po kolei wzgledem I)
		return p.back();//zwroc ostatni element
	}

	vector<Person>& getAll() { return p; }
};

string rekord(int liczba)
{
	if (liczba == 0 || liczba >= 5) {
		return "rekordow";
	} else if (liczba == 1) {
		return "rekord";
	} else {
		return "rekordy";
	}
}

void askForData(Person &p)
{
	string tmp;
	getline(cin,tmp);

	cout << "Podaj imie: ";
	if (p.getName() != "") { cout << "[" << p.getName() << "] "; }
	getline(cin,tmp); if (tmp != "") { p.setName(tmp); }

	cout << "Podaj nazwisko: ";
	if (p.getSurname() != "") { cout << "[" << p.getSurname() << "] "; }
	getline(cin,tmp); if (tmp != "") { p.setSurname(tmp); }

	cout << "Podaj telefon: ";
	if (p.getPhone() != "") { cout << "[" << p.getPhone() << "] "; }
	getline(cin,tmp); if (tmp != "") { p.setPhone(tmp); }

	cout << "Podaj email: ";
	if (p.getEmail() != "") { cout << "[" << p.getEmail() << "] "; }
	getline(cin,tmp); if (tmp != "") { p.setEmail(tmp); }
}

int main(int argc, char* argv[])
{
	string filename;

	cout<<"Podaj nazwe ksiazki adresowej: ";
	cin >> filename;

	Addressbook a;
	a.read(filename);

	cout << endl << "Odczytalem " << a.getAll().size() << " " << rekord(a.getAll().size()) << "." << endl;


	while(true) {
		string cmd;

		cout << "? "; cin >> cmd;

		if (cmd == "list") {
			string tmp; getline(cin, tmp);

			vector<Person>& p = a.getAll();
			for (const auto &r: p) {
				cout << r.getId() << ": " << r.getName() << " " << r.getSurname() << " "
				     << r.getPhone() << " " << r.getEmail() << endl;
			}

		} else if (cmd == "add") {
			Person r;
			askForData(r);
			a.add(r);
		} else if (cmd == "modify") {
			int id;
			cin >> id;
			Person &r = a.get(id);
			askForData(r); //jesli istnieje to domyslna wartosc w [] i ta sama.
		} else if (cmd == "remove") {
			int id;
			cin >> id;
			a.remove(id);
		} else if (cmd == "quit") {
			break;
		} else if (cmd == "sort") {
			sort(a.getAll().begin(), a.getAll().end());
		} else {
			cout << "Podaj instrukcje: list, add, modify, remove, sort, quit" << endl;
		}

	}

	a.write(filename);

	cout << "Zapisalem " << a.getAll().size() << " " << rekord(a.getAll().size()) << "." << endl;
	return 0;
}
