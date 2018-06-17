/****************************************************/
/* I Poczatek */
/****************************************************/
/*
#include <iostream>

using namespace std;

int main()
{
    cout << "Mount Everest - 8850 m n.p.m." << endl;
    cout << "McKinley - 6194 m n.p.m." << endl;
    cout << "Mont Blanc - 4810 m n.p.m." << endl;
    return 0;
}
*/

/****************************************************/
/* II Zmienne i wczytywanie */
/****************************************************/

/**************************/
/* II.1. Na odwrót */
/**************************/
/*
#include <iostream>

using namespace std;

int main()
{
    int a, b, c;
    cin >> a >> b >> c;
    cout << a << " " << b << " " << c << endl;
    cout << c << " " << b << " " << a << endl;
    return 0;
}
*/

/**************************/
/* II.2. Prostopad³oœcian */
/**************************/
/*
#include <iostream>

using namespace std;

int main()
{
    long a, b, c;
    cin >> a >> b >> c;
    cout << a*b*c << endl;
    cout << a*b*2+b*c*2+a*c*2 << endl;
    return 0;
}
*/

/**************************/
/* II.3. Czas */
/**************************/
/*
#include <iostream>

using namespace std;

int main()
{
    long t;
    cin >> t;
    cout << t/3600 << "g" << t%3600/60 << "m" << t%3600%60 << "s" << endl;
    return 0;
}
*/

/****************************************************/
/* III Instrukcja warunkowa if */
/****************************************************/

/**************************/
/* III.1. Maksimum */
/**************************/
/*
#include <iostream>

using namespace std;

int main()
{
    long a, b;
    cin >> a >> b;
    if (a>b){
        cout << a << endl;
    }
    else
    cout << b << endl;
    return 0;
}
*/

/**************************/
/* III.2. Æwiartka */
/**************************/
/*
#include <iostream>

using namespace std;

int main()
{
    long a, b;
    cin >> a >> b;
    if (a>0){
        if(b>0){
            cout << "I" << endl;
        }
        else if(b==0){
            cout << "OX" << endl;
        }
        else {
            cout << "IV" << endl;
        }
    }
    else if (a==0){
        if(b==0){
            cout << 0 << endl;
        }
        else {
            cout << "OY" << endl;
        }
    }
    else {
        if(b>0){
            cout << "II" << endl;
        }
        else if(b==0){
            cout << "OX" << endl;
        }
        else {
            cout << "III" << endl;
        }
    }
    return 0;
}
 */

/**************************/
/* III.3. Trójk¹t */
/**************************/
/*
#include <iostream>

using namespace std;

int main()
{
    long a, b, c;
    cin >> a >> b >> c;
    if (a+b>c & a+c>b & b+c>a){
            cout << "TAK" << endl;
    }
    else cout << "NIE" << endl;
    return 0;
}
*/

/**************************/
/* III.4. Stó³ (*) */
/**************************/
/*
#include <iostream>

using namespace std;

int main()
{
    long A, B, K;
    cin >> A >> B >> K;
    if (A<K || B<K){
        cout << 0 << endl;
    }
    else if (A/K==1 or B/K==1){
        cout << A/K+B/K-1 << endl;
    }
    else{
    cout << A/K*2+B/K*2-4 << endl;
    }
    return 0;
}
*/

/****************************************************/
/* IV Instrukcja przypisania i typ znakowy char */
/****************************************************/

/**************************/
/* IV.1. £añcuszek */
/**************************/
/*
#include <iostream>

using namespace std;

int main()
{
    long numer, rok;
    cin >> numer >> rok;
    cout << (numer%10*2+5)*50+1764-rok << endl;
    return 0;
}
*/

/**************************/
/* IV.2. Kody szesnastkowe */
/**************************/
/*
#include <iostream>

using namespace std;

int main()
{
    char z1, z2;
    cin >> z1 >> z2;
    if (z2>64){ //czy z2 jest cyfr¹
        int liczba=((int)z1-48)*16+(int)z2-55;
        cout << liczba << endl << (char)liczba << endl;
     }
    else{
        int liczba=((int)z1-48)*16+(int)z2-48;
        cout << liczba << endl << (char)liczba << endl;
    }
    return 0;
}
*/

/**************************/
/* IV.3. Podzielne */
/**************************/
/*
#include <iostream>

using namespace std;

int main()
{
    unsigned long long a, b, k;
    cin >> a >> b >> k;
    unsigned long long liczba=b/k-a/k;
    if (a%k==0){
        liczba=liczba+1;
    }
    cout << liczba << endl;
    return 0;
}
*/

/**************************/
/* IV.4. Wielkanoc (*) */
/**************************/
/* https://pl.wikipedia.org/wiki/Wielkanoc#Dla_kalendarza_gregoria.C5.84skiego_2
Dzielimy liczbê roku na 19 i wyznaczamy resztê a.
Dzielimy liczbê roku przez 100, wynik zaokr¹glamy w dó³ (odcinamy czêœæ u³amkow¹) i otrzymujemy liczbê b.
Dzielimy liczbê roku przez 100 i otrzymujemy resztê c.
Liczymy: b : 4 i wynik zaokr¹glamy w dó³ i otrzymujemy liczbê d.
Liczymy: b : 4 i wyznaczamy resztê e.
Liczymy: (b + 8) : 25 i wynik zaokr¹glamy w dó³ i otrzymujemy liczbê f.
Liczymy: (b – f + 1) : 3 i wynik zaokr¹glamy w dó³ i otrzymujemy liczbê g.
Liczymy: (19 × a + b – d – g + 15) : 30 i wyznaczamy resztê h.
Liczymy: c : 4 i wynik zaokr¹glamy w dó³ i otrzymujemy cyfrê i.
Liczymy: c : 4 i wyznaczamy resztê k.
Liczymy: (32 + 2 × e + 2 × i – h – k) : 7 i otrzymujemy resztê l.
Liczymy: (a + 11 × h + 22 × l) : 451 i wynik zaokr¹glamy w dó³ i otrzymujemy liczbê m.
Liczymy: (h + l – 7 × m + 114) : 31 i otrzymujemy resztê p.
Dzieñ Wielkanocy = p + 1.
Miesi¹c = Zaokr¹glenie w dó³ dzielenia (h + l – 7 × m + 114) przez 31. */

/*
#include <iostream>

using namespace std;

int main()
{
    int r;
    cin >> r;
    int a = r%19;
    int b = r/100;
    int c = r%100;
    int d = b/4;
    int e = b%4;
    int f = (b+8)/25;
    int g = (b-f+1)/3;
    int h = (19 * a + b - d - g + 15)%30;
    int i = c/4;
    int k = c%4;
    int l = (32 + 2 * e + 2 * i - h - k)%7;
    int m = (a + 11 * h + 22 * l)/451;
    int p = (h + l - 7 * m +114)%31;
    int dzien = p+1;
    int miesiac = (h + l - 7 * m +114)/31;
    cout << dzien << " " << miesiac << endl;
    return 0;
}
*/

/****************************************************/
/* V Pętla while */
/****************************************************/

/**************************/
/* V.1. Potęgi dwójki */
/**************************/
/*
#include <iostream>

using namespace std;

int main()
{
    int i=1, n;
    cin >> n;
    cout << i << endl;
    while(i*2<=n){
            i=i*2;
    cout << i << endl;
    }
    return 0;
}
*/
/**************************/
/* V.2. Pomiary */
/**************************/
/*
#include <iostream>

using namespace std;

int main()
{
    int pomiar=0, ile_roznych=0, a=0;
    while(pomiar!=-1){
            cin >> pomiar;
            if(pomiar!=-1 & pomiar!=a)
                ile_roznych++;
            a=pomiar;
    }
    cout << ile_roznych << endl;
    return 0;
}
*/

/**************************/
/* V.3. Lustro */
/**************************/
/*
5123%10/1=3
5123%100/10=2
5123%1000/100=1
5123%10000/1000=5
*/
/*
#include <iostream>

using namespace std;

int main()
{
    int i=1, j=10, n, poczatek=0;
    cin >> n;
    while(i<=n){
        if(n==i) {cout << 1; return 0;}
        if(n%j/i!=0 || poczatek==1){
            cout << n%j/i;
            poczatek=1;
        }
        i=j;
        j=10*j;
        }
}
*/

/******************************/
/* V.4. Czy sie zatrzyma? (*) */
/******************************/
/*
#include <iostream>

using namespace std;

int main()
{
    long long i;
    cin >> i;
    while (i%2==0){
        i=i/2;
    }
    if(i==1) {
        cout << "TAK";
    }
    else {
        cout << "NIE";
    }
}
*/

/****************************************************/
/* VI Pętla for i tablice */
/****************************************************/

/******************************/
/* VI.1. Silnia */
/******************************/
/*
#include <iostream>

using namespace std;

int main()
{
    int n, p=1, silnia=1;
    cin >> n;
    for(int i=1; i<=n; i++){
        silnia=silnia*i;
    }
    cout << silnia;
    return 0;

}
*/

/******************************/
/* VI.2. Na przemian */
/******************************/
/*
#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int t[n];
    for (int i=0; i<n; i++){
        cin >> t[i];
        if (i%2==0){
            cout << t[i] << " ";
        }
    }
    cout << endl;
    for (int i=1; i<n; i=i+2){
        if (i%2!=0){
            cout << t[i] << " ";
        }
    }
}
*/

/******************************/
/* VI.3. Pierwszy i ostatni */
/******************************/
/*
#include <iostream>

using namespace std;

int main()
{
    int n;
    long long x;
    int pierwsza=-1, ostatnia=-1;
    cin >> n >> x;
    long long t[n];
    for(int i=0; i<n; i++){
        cin >> t[i];
    }
    for(int i=0; i<n; i++){
        if (t[i]==x){
            if(pierwsza==-1){
            pierwsza=i+1;
            ostatnia=i+1;
            }
            else ostatnia=i+1;
        }
    }
    cout << pierwsza << " " << ostatnia;
    return 0;

}
*/

/*************************************/
/* VI.4. Papryczki logarytmiczne (*) */
/*************************************/
/* do optymalizacji */
/*
#include <iostream>

using namespace std;

int main()
{
    int k, p=1, j=0, a=1;
    cin >> k;
    int t[k+1];
    int t2[k+1];
    int w[k+1];
    for(int i=0; i<=k; i++){
        cin >> t[i];
        w[i]=p;
        p=p*2;
    }
    while(j==0){
        j=a;
        for(int i=k; i>=0 & j!=0; i--){
            t2[i]=t[i];
            while(t2[i]!=0 & w[i]<=j & j!=0){
                j=j-w[i];
                t2[i]--;
            }
        }
    a++;
    }
    cout << a-1;
}
*/

/****************************************************/
/* VII Więcej o pętlach i tablicach */
/****************************************************/

/*************************************/
/* VII.1. Liczby pierwsze */
/*************************************/
/*
#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    bool pierwsza=true;
    for(int i=2; i<=n/2; i++){
        if(n%i==0) pierwsza=false;
    }
    if(pierwsza==true) cout << "pierwsza";
    else cout << "zlozona";
}
*/

/*************************************/
/* VII.2. Palindrom */
/*************************************/
/*
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s;
    cin >> s;
    for(int i=0; i<s.size(); i++){
        if(s[i]!=s[s.size()-1-i]){
            cout << "NIE";
            return 0;
        }
    }
    cout << "TAK";
    return 0;
}
*/

/*************************************/
/* VII.3. Oceny */
/*************************************/
/*
#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int s[6]={0};
    int t[n];
    for(int i=0; i<n; i++){
        cin >> t[i];
        if(t[i]==1) s[0]++;
        else if(t[i]==2) s[1]++;
        else if(t[i]==3) s[2]++;
        else if(t[i]==4) s[3]++;
        else if(t[i]==5) s[4]++;
        else s[5]++;
    }
    for(int i=0; i<6; i++)
    cout << s[i] << " ";
    return 0;
}
*/

/*************************************/
/* VII.4. Szyfr Cezara (*) */
/*************************************/
/*
#include <iostream>
#include <string>
using namespace std;

int main()
{
    int operacja, k, znak=1;
    cin >> operacja;
    cin >> k;
    if (operacja==2) {k=-k; znak=-1;}
    string napis1, napis2;
    cin >> napis1;
    for(int i=0; i<napis1.size(); i++){
        if(65<=int(napis1[i]) & int(napis1[i])<=90){
            if(65<=int(napis1[i]+k) & int(napis1[i]+k)<=90)
                napis2[i]=(char)(napis1[i]+k);
            else
                napis2[i]=(char)(int(napis1[i])-znak*26+k);
        }

        else if(97<=int(napis1[i]) & int(napis1[i])<=122){
            if(97<=int(napis1[i]+k) & int(napis1[i]+k)<=122)
                napis2[i]=(char)(napis1[i]+k);
            else
                napis2[i]=(char)(int(napis1[i])-znak*26+k);
        }
        else
            napis2[i]=(char)(napis1[i]);
        cout << napis2[i];
    }
}
*/

/****************************************************/
/* VIII Funkcje */
/****************************************************/

/***************************************/
/* VIII.1. Największy wspólny dzielnik */
/***************************************/
/* wersja bez funkcji*/
/*
#include <iostream>
#include <string>
using namespace std;

int main()
{
    int n, ile, minimum, dzielnik=1;
    cin >> n;
    int t[n];
    for (int i=0; i<n; i++){
        cin >> t[i];
        if(i==0) minimum=t[i];
        if(minimum>t[i]) minimum=t[i];
    }
    for(int j=1; j<=minimum; j++){
        ile=0;
        for (int i=0; i<n; i++){
            if(t[i]%j==0) ile ++;
        }
        if(ile==n){
            dzielnik=j;
        }
    }
    cout << dzielnik;
}
*/

/* wersja Euklidesowa */
/*
#include <iostream>
#include <string>
using namespace std;

int nwd(int a, int b) {
    int r = a % b;
    while (r != 0) {
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}

int nwd2(int t[], int n){
    int temp=t[0];
    for(int i=1; i<n; i++){
        temp=nwd(temp,t[i]);
    }
    return temp;
}
int main()
{
    int n;
    cin >> n;
    int t[n];
    for (int i=0; i<n; i++){
        cin >> t[i];
    }
    cout << nwd2(t, n);
}
*/

/***************************************/
/* VIII.2. Wicemistrz */
/***************************************/
/*
#include <iostream>
using namespace std;


int wice(int t[], int n){
    int mistrz, wice, temp=0;
    if(t[0]>t[1]){
        mistrz=t[0];
        wice=t[1];
    }
    else{
        mistrz=t[1];
        wice=t[0];
    }
    for(int i=2; i<n; i++){
        if(t[i]>mistrz){
            temp=mistrz;
            mistrz=t[i];
            wice=temp;
        }
        else if(t[i]>wice){
            wice=t[i];
        }
    }
    return wice;
}
int main()
{
    int n;
    cin >> n;
    int t[n];
    for(int i=0; i<n; i++){
        cin >> t[i];
    }
    cout << wice(t, n);
    return 0;
}
*/

/***************************************/
/* VIII.3. Duże liczby */
/***************************************/
/*
#include <iostream>

using namespace std;

string rowne(string x, string y){
    if(x==y) return "TAK";
    else return "NIE";
}

string nierowne(string x, string y){
    if(x!=y) return "TAK";
    else return "NIE";
}

string mniejsze(string x, string y){
    if(rowne(x,y)=="TAK") return "NIE";
    if(x.length()<y.length()) return "TAK";
    else if(x.length()>y.length()) return "NIE";
    else{
        for(int i=0; i<x.length(); i++){
            if(x[i]<y[i]) return "TAK";
            else if(x[i]>y[i]) return "NIE";
        }
    }
}

string wieksze(string x, string y){
    if(mniejsze(x,y)=="NIE" & rowne(x,y)=="NIE")
        return "TAK";
    else return "NIE";
}

string mniejszerowne(string x, string y){
    if(wieksze(x,y)=="NIE")
        return "TAK";
    else return "NIE";
}

string wiekszerowne(string x, string y){
    if(mniejsze(x,y)=="NIE")
        return "TAK";
    else return "NIE";
}

int main()
{
    string a, b, znak;
    cin >> a >> znak >> b;
    if(znak=="==") cout << rowne(a,b);
    else if(znak=="!=") cout << nierowne(a,b);
    else if(znak=="<") cout << mniejsze(a,b);
    else if(znak==">") cout << wieksze(a,b);
    else if(znak=="<=") cout << mniejszerowne(a,b);
    else if(znak==">=") cout << wiekszerowne(a,b);
    return 0;
}
*/

/***************************************/
/* VIII.4. Wesoła małpka (*) */
/***************************************/
/* błąd przy sprawdzaniu */
/*
#include <iostream>
using namespace std;

int ile(int n, int d){
    int *t=new int[n-1];
    t[n-1]={1};
    t[0]=0;
    int i=1, wolne=1;
    while(t[d*i%n]!=0){
        wolne++;
        t[d*i%n]=0;
        i++;
    }
    return wolne;
}

int main(){
    int z, n, d;
    cin >> z;
    int t[z];
    for(int i=0; i<z; i++){
        cin >> n >> d;
        t[i]=ile(n,d);
    }
    for(int i=0; i<z; i++){
        cout << t[i] << endl;
    }
    return 0;
}
*/

/****************************************************/
/* IX Efektywność programów */
/****************************************************/

/***************************************/
/* IX.1. Koło */
/***************************************/
/*
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main()
{
    double r;
    cin >> r;
    cout << setprecision(3) << fixed;
    cout << M_PI*r*r << endl << 2*M_PI*r;
    return 0;
}
*/

/***************************************/
/* IX.2. Ostatnia cyfra */
/***************************************/
/*
#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    if(n==0) cout << 1;
    else if(n%4==1) cout << 2;
    else if(n%4==2) cout << 4;
    else if(n%4==3) cout << 8;
    else cout << 6;
    return 0;
}
*/

/***************************************/
/* IX.3. Dwa markety */
/***************************************/
/*
#include <iostream>
using namespace std;

int main()
{
    int n, m, koszyk=0, koszyk_min=-1;
    cin >> n >> m;
    int t[n][m];
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> t[i][j];
        }
    }
    for(int l=0; l<=n; l++){
        for(int i=l+1; i<n; i++){
            for(int j=0; j<m; j++){
                if(t[l][j]<=t[i][j]) koszyk+=t[l][j];
                else koszyk+=t[i][j];
            }
            if(koszyk_min==-1 || koszyk_min>koszyk)
                koszyk_min=koszyk;
            koszyk=0;
        }
    }
    cout << koszyk_min;
    return 0;
}
*/

/***************************************/
/* IX.4. Taśma (*) */
/***************************************/
/* do optymalizacji */
/*
#include <iostream>
using namespace std;

int main()
{
    int n, rozne=0;
    cin >> n;
    int t[n];
    for(int i=0; i<n; i++){
        cin >> t[i];
    }
    int i=0, j=n-1;
    while(n-1-i>rozne & i<n-1){
        j=n-1;
        while(t[i]==t[j] & j-i>rozne)j--;
        if(j-i>rozne) rozne=j-i;
        i++;
    }
    if(rozne==0) cout << "BRAK";
    else cout << rozne;
    return 0;
}
*/

/****************************************************/
/* X Projekt graficzny i quiz */
/****************************************************/

/***************************************/
/* X.1. Jakie to działanie? */
/***************************************/
/*
#include <iostream>
using namespace std;

int main()
{
    int a, b, c;
    cin >> a >> b >> c;
    if(a+b==c) cout << a << " + " << b << " == " << c << endl;
    if(a-b==c) cout << a << " - " << b << " == " << c << endl;
    if(a*b==c) cout << a << " * " << b << " == " << c << endl;
    if(b!=0){
        if(a/b==c) cout << a << " / " << b << " == " << c << endl;
        if(a%b==c) cout << a << " % " << b << " == " << c << endl;
    }
    return 0;
}
*/

/***************************************/
/* X.2. Król */
/***************************************/
/*
#include <iostream>
using namespace std;

int main()
{
    char k;
    int w;
    cin >> k >> w;
    if(k=='a' || k=='h' || w==1 || w==8){
        if((k=='a' || k=='h') & (w==1 || w==8))
            cout << 3;
        else
            cout << 5;
    }
    else
        cout << 8;
    return 0;
}
*/

/***************************************/
/* X.3. Sad */
/***************************************/
/*
#include <iostream>
using namespace std;

int main()
{
    int n, x_min, x_max, y_min, y_max;
    cin >> n;
    int t[n][2];
    for(int i=0; i<n; i++){
        cin >> t[i][0] >> t[i][1];
        if(i==0){
            x_min=t[i][0];
            x_max=t[i][0];
            y_min=t[i][1];
            y_max=t[i][1];
        }
        if(t[i][0]<x_min) x_min=t[i][0];
        else if(t[i][0]>x_max) x_max=t[i][0];
        if(t[i][1]<y_min) y_min=t[i][1];
        else if(t[i][1]>y_max) y_max=t[i][1];
    }
    cout << 2*(x_max-x_min)+2*(y_max-y_min);
    return 0;
}
*/

/***************************************/
/* X.4. Ciąg bitoniczny */
/***************************************/
/*
#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int t[n];
    bool zmiana=false;
    cin >> t[0];
    for(int i=1; i<n; i++){
        cin >> t[i];
        if(t[i]==t[i-1]) {
            cout << "NIE";
            return 0;
        }
        else if(zmiana==false & t[i]<t[i-1])
            zmiana=true;
        else if(zmiana==true & t[i]>t[i-1]){
            cout << "NIE";
            return 0;
        }
    }
    cout << "TAK";
    return 0;
}
*/

/***************************************/
/* X.5. Choinka */
/***************************************/
/*
#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int spacje=n-1;
    int gwiazdki=1;
    for(int i=0; i<n; i++){
        cout << string(spacje, ' ') << string(gwiazdki, '*') << endl;
        spacje--;
        gwiazdki+=2;
    }
    for(int i=0; i<2; i++)
        cout << string(n-1, ' ') << string(1, '*') << endl;
    return 0;
}
*/
