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

	void setName(string _name);
	void setSurname(string _surname);
	void setPhone(string _phone);
	void setEmail(string _email);
	void setId(int _id);

	string getName() const;
	string getSurname() const;
	string getPhone() const;
	string getEmail() const;
	int getId() const;

	bool operator<(const Person& p) const {
		return name < p.name;
	}

	friend ostream& operator<<(ostream&, const Person&);
	friend istream& operator>>(istream&, Person&);
};

void Person::setName(string _name)
{
    name=_name;
}
void Person::setSurname(string _surname)
{
    surname=_surname;
}
void Person::setPhone(string _phone)
{
    phone=_phone;
}
void Person::setEmail(string _email)
{
    email=_email;
}
void Person::setId(int _id)
{
    id=_id;
}
string Person::getName() const
{
    return name;
}
string Person::getSurname() const
{
    return surname;
}
string Person::getPhone() const
{
    return phone;
}
string Person::getEmail() const
{
    return email;
}
int Person::getId() const
{
    return id;
}

ostream& operator<<(ostream& os, const Person& p)
{
    return os << "ID: " << p.getId() << "; Imiê: " << p.getName() << "; Nazwisko: " << p.getSurname() << "; Telefon: " << p.getPhone() << "; Email: " << p.getEmail() << "; " << endl;
}
istream& operator>>(istream& is, Person& p)
{
    is >> p.id >> p.name >> p.surname >> p.phone >> p.email;
}
class Addressbook
{
	vector<Person> p;

	int getFreeId()
	{
		int max_id = 0;
		for (auto &r: p) {
			if (r.getId() > max_id) { max_id = r.getId(); }
		}
		return max_id+1;
	}

public:
	Addressbook() {}

	void read(string filename) {
		Person r;

		fstream f;
		f.open(filename, ios::in);

		while (f>>r) {
			p.push_back(r);
		}
		f.close();
	}

	void write(string filename) {
		fstream f;

		f.open(filename, ios::out | ios::trunc);

		for (auto& r: p) {
			f << r;
		}
		f.close();
	}

	void add(Person &r) {
		r.setId(getFreeId());
		p.push_back(r);
	}

	void remove(int id) {
		for (auto i = p.begin(); i < p.end(); i++) {
			if (i -> getId() == id) {
				p.erase(i); return;
			}
		}
	}

	Person& get(int id) {
		for (auto &r: p) {
			if (r.getId() == id) return r;
		}
		Person r;
		r.setId(id);
		p.push_back(r);
		return p.back();
	}

	vector<Person>& getAll() { return p; }
};

string rekord(int liczba)
{
	if (liczba == 0 || liczba >= 5) {
		return "rekordów";
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

	cout << "Podaj nazwê ksi¹¿ki adresowej: ";
	cin >> filename;

	Addressbook a;
	a.read(filename);

	cout << endl << "Odczyta³em " << a.getAll().size() << " " << rekord(a.getAll().size()) << "." << endl;


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
			askForData(r);
		} else if (cmd == "remove") {
			int id;
			cin >> id;
			a.remove(id);
		} else if (cmd == "quit") {
			break;
		} else if (cmd == "sort") {
			sort(a.getAll().begin(), a.getAll().end());
		} else {
			cout << "Podaj instrukcjê: list, add, modify, remove, sort, quit" << endl;
		}

	}

	a.write(filename);

	cout << "Zapisa³em " << a.getAll().size() << " " << rekord(a.getAll().size()) << "." << endl;

	return 0;
}
