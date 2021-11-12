//cwp - funkcja 'czy wystapil ciag'
//pnp - poczatek nadluzszego podciagu
//knp - koniec najdluzszego podciagu

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

int wypisz(int T[],int i_start,int i_koniec)
{
    cout << "[";
    for (int i=i_start;i<i_koniec;i++)
        cout << T[i]<<", ";
    cout << T[i_koniec] << "]"<<endl;
}                                                //wypisuje podciag zaczynajacy sie w indeksie i_start i konczacy sie w indeksie i_koniec


int zapisanie(int T[],int i_start,int i_koniec,ofstream &plik)
{
    plik << "[";
    for (int i=i_start;i<i_koniec;i++)
        plik << T[i]<<", ";
    plik << T[i_koniec] << "]"<<endl;
}

int cwp(int T[],int i_start,int i_koniec)
{
    int dlugosc=i_koniec-i_start+1;
    for(int i=0;i<i_start;i++)              //sprawdza czy w indeksie "i" zaczyna sie taki sam podciag jak zaczynajacy sie w indeksie i_start i konczacy sie w indeksie i_koniec juz wystapil
        for(int j=0;j<dlugosc;j++){
            if(T[i+j]!=T[i_start+j])
                break;
            if(j==dlugosc-1)
                return 1;
        }
    return 0;                              //funkcja sprawdza czy podciag zaczynajacy sie w indeksie i_start i konczacy sie w indeksie i_koniec juz wystapil
}


int szukaj(int T[],int n,int szukana_suma,ofstream &plik)
{
    int pnp=-1,knp=-2;              //zmienne przychowuje informacje o najdluzszym znalezionym podciagu
    cout << "Podciagi o sumie "<< szukana_suma<< " to:"<<endl;
    plik << "Podciagi o sumie "<< szukana_suma<< " to:"<<endl;
    for (int i=0;i<n;i++){
        int S=0;                                                                        //suma aktualnie sprawdzanego podciagu
        for(int j=i;j<n;j++){
            S+=T[j];
            if(S==szukana_suma&&!cwp(T,i,j))
            {                           //wypisywane sa podciagi o zadanej sumie, które wczesniej nie wystapily
                wypisz(T,i,j);
                zapisanie(T,i,j,plik);
                if(j-i>knp-pnp){    //jesli znaleziono dluzszy podciag modyfikuje informacje o najdluzszym podciagu
                    pnp=i;
                    knp=j;
                }
            }
        }
    }
    if(pnp==-1)
    {
        cout << "Brak takich podciagow"<<endl;
        plik  << "Brak takich podciagow"<<endl;
    }
    else{
        cout << "Najdluzszy podciag to:" << endl;
        plik << "Najdluzszy podciag to:" << endl;
        wypisz(T,pnp,knp);
        zapisanie(T,pnp,knp,plik);
        cout <<"o dlugosci " << (knp-pnp+1)<<endl;
        plik <<"o dlugosci " << (knp-pnp+1)<<endl;
    }
}                                                                                        //funkcja wypisuje podci¹gi o zadanej sumie


int testowy(int n, int minimalna_wartosc, int maksymalna_wartosc,int suma,ofstream &plik)
    {
        srand(time(NULL));
        int T[n];
        for(int i=0;i<n;i++)
            T[i]=rand()%(maksymalna_wartosc-minimalna_wartosc+1)+minimalna_wartosc;
        cout<<"Wygenerowany podciag to: "<<endl;
        plik <<"Wygenerowany podciag to: "<<endl;
        wypisz(T,0,n-1);
        zapisanie(T,0,n-1,plik);
        szukaj(T,n,suma,plik);
   }                                                                                     //funkcja generująca losowo tablice T[n] i testujaca funkcje szukaj


int main()
{
    ofstream plik;
    plik.open("plik.txt");
    cout<<"Przyklad z kartki:"<<endl;
    int T1[]={0,6,5,1,-5,5,3,5,3,-2,0};
    szukaj(T1,11,8,plik);
    cout<<endl;
    int suma, n,x=7;
    cout<<"PRZYKLAD"<<endl;
    cout<< "Przykladowy losowy ciag z testera: "<<endl;
    testowy(10,-5,5,x,plik);
    cout<<endl<<endl<<endl;
    cout<<"Program obliczy podana suma podanego ciagu"<<endl;
    cout<<"podaj dlugosc tablicy: ";
    cin>>n;
    if(n==0)
        cout<<"ilosc elementow nie moze byc rowna 0"<<endl;
    else if (n<0)
        cout<<"ilosc elementow ciagu nie moze byc ujemna"<<endl;
    else
    {
        int T[n];
        cout<<"podaj "<< n << " liczb"<<endl;
        for(int i=0;i<n;i++){
            cout<<"liczba "<<i+1<<": ";
            cin >> T[i];
        }
        cout<<"podaj sume: "<<endl;
        cin>>suma;
        szukaj(T,n,suma,plik);

        cout<<endl;
    }
    plik.close();
    return 0;
}
