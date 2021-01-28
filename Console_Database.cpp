#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

struct Student
{
    string nazwisko;
    string specjalnosc;
    float srednia;
    int id;
    Student* next;



};

int aktualne_id=0;
int rozmiarListy=0;

void wyswietlStudenta(Student* s)
{
    cout<<"Student #"<<s->id<<endl;
    cout<<"Nazwisko: "<<s->nazwisko<<endl;
    cout<<"Srednia z toku studiow: "<<s->srednia<<endl;
    cout<<"Specjalnosc studenta: "<<s->specjalnosc<<endl;

}

void dodaj(Student* &lista)
{
    Student* s = new Student();
    cout<<"Podaj nazwisko: "<<endl;
    cin>>(s->nazwisko);
    while(true)
    {
        try
        {
            cout<<"Podaj srednia: "<<endl;
            cin>>s->srednia;
            break;
        }
        catch(const char* msg)
        {
            cout<<msg<<endl;
        }
    }
    cout<<"Podaj specjalnosc: "<<endl;
    cin>>(s->specjalnosc);
    s->id = aktualne_id;
    s->next=NULL;
    aktualne_id++;
    if(lista==NULL) lista = s;
    else
    {
        Student* tmp = lista;
        while(tmp->next!=NULL)
        {
            tmp=tmp->next;
        }
        tmp->next = s;
    }
    rozmiarListy++;
    system("cmd /c cls");
}

void dodajStudenta(Student *s, Student* &lista){
    if(lista==NULL) lista = s;
    else
    {
        s->next = NULL;
        Student* tmp = lista;
        while(tmp->next!=NULL)
        {
            tmp=tmp->next;
        }
        tmp->next = s;
    }
}

void usun(Student* &lista, int szId)
{
    if(lista==NULL) return;
    if(lista->id==szId)
    {
        Student*tmp=lista->next;
        delete lista;
        lista=tmp;
        rozmiarListy--;
        return;
    }


    Student* tmp=lista;
    while (tmp-> next!=NULL)
    {
        if(tmp->next->id==szId)
        {
            Student* t2=tmp->next->next;
            delete tmp->next;
            tmp->next=t2;
            rozmiarListy--;
            return;

        }

        tmp=tmp->next;
    }
    system("cmd /c cls");
}

void edytuj(Student* lista, int szId )
{
    if(lista==NULL) return;//lista jest pusta
    while(lista->id!=szId)
    {
        lista=lista->next;
    }
    if(lista==NULL) return; //lista nie zawiera elementu
    cout<<"Podaj nowe nazwisko: "<<endl;
    cin>>lista->nazwisko;
    cout<<"Podaj nowa specjalnosc: "<<endl;
    cin>>lista->specjalnosc;
    while(true)
    {
        try
        {
            cout<<"Podaj srednia: "<<endl;
            cin>>lista->srednia;
            break;
        }
        catch(const char* msg)
        {
            cout<<msg<<endl;
        }

    }
    system("cmd /c cls");
}

void wyswietlListe(Student* lista)
{
    while(lista!=NULL)
    {
        wyswietlStudenta(lista);
        lista=lista->next;
    }
    return;
}




void szukanie_id(Student* lista, int szId)
{
    if(lista==NULL) return; //lista jest pusta
    while(lista!=NULL && lista->id!=szId)
    {
        lista=lista->next;
    }
    if(lista==NULL) {
        cout<<"NIe znaleziono"<<endl;
        return; //lista nie zawiera elementu
    }
    wyswietlStudenta(lista);
    getchar();

}

void szukanie_nazwisko(Student* lista, string szNazwisko)
{
    bool z = false;
    while(lista!=NULL)
    {
        if(lista->nazwisko==szNazwisko)
        {
            wyswietlStudenta(lista);
            z = true;
        }
        lista=lista->next;
    }
    if(!z) cout<<"Nie znaleziono"<<endl;
    getchar();

    return;
}
void szukanie_srednia(Student* lista, float szSrednia)
{
    bool z = false;
    while(lista!=NULL)
    {
        if(lista->srednia==szSrednia)
        {
            wyswietlStudenta(lista);
            z = true;
        }
        lista=lista->next;
    }
    if(!z) cout<<"Nie znaleziono"<<endl;
    getchar();

    return;
}

void szukanie_specjalnosc(Student* lista, string szspecjalnosc)
{
    bool z = false;
    while(lista!=NULL)
    {
        if(lista->specjalnosc==szspecjalnosc)
        {
            wyswietlStudenta(lista);
            z = true;
        }
        lista=lista->next;
    }
    if(!z) cout<<"Nie znaleziono"<<endl;
    getchar();

    return;
}
void zapisz_do_pliku(Student* lista)
{
    try
    {
        ofstream plik("baza.txt", ios::trunc);
        plik << aktualne_id << endl << rozmiarListy << endl;
        if (lista != NULL)
        {
            while (lista != NULL)
            {
                plik << lista->id <<" "<< lista->nazwisko << " " << lista->specjalnosc << " "<< lista->srednia<< endl;
                lista = lista->next;
            }
        }
        plik.close();
    }

    catch(const char* msg)
    {
        cout<<msg<<endl;
    }
    system("cmd /c cls");
}




void wczytaj_z_pliku(Student* &lista)
{
    ifstream f1("baza.txt", ios::in);
    try
    {
        f1 >> aktualne_id;
        f1 >> rozmiarListy;
        int id;
        float srednia;
        string nazwisko;
        string spec;
        while(f1>>id>>nazwisko>>spec>>srednia)
        {
            Student* s=new Student();
            s->id = id;
            s->srednia=srednia;
            s->nazwisko=nazwisko;
            s->specjalnosc=spec;
            s->next = NULL;
            dodajStudenta(s, lista);
        }
        f1.close();
    }
    catch(const char* msg)
    {
        cout<<msg<<endl;
    }
}

int main()
{

    int wybor;
    Student* pierwszy=NULL;
    wczytaj_z_pliku(pierwszy);
    do
    {
        cout<<"BAZA DANYCH"<<endl;
        cout<<"-----------MENU GLOWNE--------------------"<<endl;
        cout<<"--------------WIDOK---------------------"<<endl;
        cout<<"1.Pokaz wszystkie osoby w bazie danych"<<endl;
        cout<<"2.Znajdz osobe w bazie danych"<<endl;
        cout<<"------------ZARZADZANIE-----------------"<<endl;
        cout<<"3. Dodaj nowa osobe do bazy danych" << endl;
        cout << "4.Edytuj dana osobe" << endl;
        cout << "5. Usun osobe z bazy" << endl;
        cout << "6. Zapisz zmiany" << endl;
        cout << "7. Wyjdz" << endl;
        cout<<"Podaj co chcesz zrobic: "<<endl;
        cin>>wybor;
        switch(wybor)
        {
        case 1:
        {
            wyswietlListe(pierwszy);

            break;

        }

        case 2:
        {
            float szSrednia;
            string szspecjalnosc, szNazwisko;
            int szId;
            char wyszukiwanie;
            cout<<"Wyszukiwanie i=po Id, s=po Sredniej, p=po Specjalnosci czy n=po Nazwisku?"<<endl;
            cin>>wyszukiwanie;
            cout<<"Podaj szukana wartosc : ";
            switch(wyszukiwanie)
                {
                case 'i':
                {
                    cin>>szId;
                    szukanie_id(pierwszy,szId);
                    break;

                }
                case 'n':
                {
                    cin>>szNazwisko;
                    szukanie_nazwisko(pierwszy,szNazwisko);
                    break;
                }
                case 's':
                {
                    cin>>szSrednia;
                    szukanie_srednia(pierwszy,szSrednia);
                    break;

                }
                case 'p':
                {
                    cin>>szspecjalnosc;
                    szukanie_specjalnosc(pierwszy,szspecjalnosc);
                    break;

                }
                break;
            }

            break;

        }

        case 3:
        {
            cout<<"Wpisz dane osoby ktora chcesz dodac: "<<endl;
            dodaj(pierwszy);
            break;
        }

        case 4:
        {
            cout<<"Podaj ID osoby, ktora chcesz edytowac: "<<endl;
            int szId;
            cin>>szId;
            edytuj(pierwszy, szId);

            break;
        }
        case 5:
        {
            cout<<"Podaj ID osoby, ktora chcesz usunac: "<<endl;
            int szId;
            cin>>szId;
            usun(pierwszy, szId);
            break;

        }
        case 6:
        {
            cout<<"Zapisuje..."<<endl;
            zapisz_do_pliku(pierwszy);
            break;
        }

        case 7:
        {

            getchar();
        }
        }
    }
    while(wybor!=7);

    return 0;
}
