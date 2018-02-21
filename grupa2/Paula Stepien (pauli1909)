#include<iostream>
#include<cstdlib>
using namespace std;

bool czy_pierwsza(int n)
{
	if(n<2)
		return false; //pierwsza

	for(int i=2;i*i<=n;i++)
		if(n%i==0)
			return false;//zlozona
	return true;
}

int main()
{
	int n;

	cout<<"Liczba: ";
	cin>>n;

	if(czy_pierwsza(n))
		cout<<"pierwsza"<<endl;
	else
		cout<<"zlozona"<<endl;

	system("pause");
	return 0;
}
