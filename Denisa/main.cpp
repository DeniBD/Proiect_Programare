#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <conio.h>
#include "Data.h"
#include "Produs.h"
#include "Comanda.h"
#include "CosCumparaturi.h"
#include <ctime>

#define GREEN 2
#define BLUE 9
#define LIGHT_BLUE 11
#define RED 12
#define YELLOW 14
#define WHITE 15

void set_color(int color_code) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color_code);
}
vector<Produs> produseStoc;
vector<Comanda> comenzi;
vector<Produs> produse_cos;
CosCumparaturi cos;

void MENIU_PRINCIPAL();
void SELECTARE_PRODUS();
void AFISARE_COS_CUMPARATURI();
void GOLIRE_COS_CUMPARATURI();
void PRODUSE_MAGAZIN();
void COS_CUMPARATURI();

void read_stoc()
{
    ifstream fin("C:/Users/Denisa/PP2/proiect2pp/proiect2pp/stoc.txt");
    int nr, cantitate;
    string content, nume, data, codBare;
    vector<string> items;
    double pret;
    string delim = " ";
    while (getline(fin, content))
    {
        size_t pos = 0;
        //codBare
        pos = content.find(delim);
        codBare = content.substr(0, pos);
        content = content.substr(pos + delim.length());
        //nume_produs
        pos = content.find(delim);
        nume = content.substr(0, pos);
        content = content.substr(pos + delim.length());
        //cantitate_produs
        pos = content.find(delim);
        string temp = content.substr(0, pos);
        cantitate = stoi(temp);
        content = content.substr(pos + delim.length());
        //pret
        pos = content.find(delim);
        pret = stod(content.substr(0, pos));
        content = content.substr(pos + delim.length());
        //data
        pos = content.find(delim);
        data = content.substr(0, pos);
        content = content.substr(pos + delim.length());

        Data *d = new Data(data);
        //cout << *d;
        Produs produs(nume, codBare, cantitate, pret, d);
        // cout << produs;
        produseStoc.push_back(produs);
    }
    fin.close();
}
void read_comenzi()
{
    ifstream fin("C:/Users/Denisa/PP2/proiect2pp/proiect2pp/comenzi.txt");
    int cantitate, nr;
    string data, content, codBare;
    string delim = " ";
    while (getline(fin, content))
    {
        size_t pos = 0;
        //data_comanda
        pos = content.find(delim);
        data = content.substr(0, pos);
        content = content.substr(pos + delim.length());
        //creare_data_comanda
        Data *d = new Data(data);
        //nr_produse_comanda
        pos = content.find(delim);
        nr = stoi(content.substr(0, pos));
        content = content.substr(pos + delim.length());
        vector<string> cod_bare;
        vector<int> nr_prod;
        string content2;
        for (int i = 1; i <= nr; i++)
        {
            getline(fin, content2);
            size_t pos = 0;
            //codBare
            pos = content2.find(delim);
            codBare = content2.substr(0, pos);
            content2 = content2.substr(pos + delim.length());
            cod_bare.push_back(codBare);
            //cantitate_produs
            pos = content2.find(delim);
            cantitate = stoi(content2.substr(0, pos));
            content2 = content2.substr(pos + delim.length());
            nr_prod.push_back(cantitate);
        }
        Comanda c(d, cod_bare, nr_prod);
        // cout << c;
        comenzi.push_back(c);
    }
    fin.close();
}
void MODIFICARE_STOC_FISIER()
{
    ofstream fout("C:/Users/Denisa/PP2/proiect2pp/proiect2pp/stoc.txt");
    for(auto i : produseStoc)
        fout << i.get_cod_bare() << " " << i.get_nume() << " " << i.get_cantitate() << " " << i.get_pret() << " " << *i.get_data() << endl;
    fout.close();
}
void PLASARE_COMANDA()
{
    ofstream fout("C:/Users/Denisa/PP2/proiect2pp/proiect2pp/comenzi.txt", ofstream::app);
    vector <string> x1;
    vector <int> x2;
    time_t now = time(0);
    tm *ltm = localtime(&now);

    int an = 1900 + ltm->tm_year;
    int luna = 1 + ltm->tm_mon;
    int zi = ltm->tm_mday;
    Data* d = new Data(zi, luna, an);
    fout << zi <<"."<< luna << "."<< an << " " << cos.get_map().size() << endl;
    for(auto it : cos.get_map())
    {
        x1.push_back(it.first.get_cod_bare());
        x2.push_back(it.second);
    }
    Comanda c (d, x1, x2);
    fout << c;
    fout.close();

}
string getKeyAtIndex (int index)
{
    map<Produs, int>::const_iterator end = cos.get_map().end();
    int counter = 0;
    for (map<Produs, int>::const_iterator it = cos.get_map().begin(); it != end; ++it)
    {
        counter++;

        if (counter == index)
            return it->first.get_cod_bare();
    }
}
void SELECTARE_PRODUS_STERGERE()
{
    set_color(WHITE);
    int optiune_selectata = 0, cantitate_selectata = 0;
    if(cos.get_pret_total())
    {
        set_color(YELLOW);
        printf("\nIntroduceti numar produs si apasati ENTER: ");
        set_color(GREEN);
        cin >> optiune_selectata;
        while(optiune_selectata < 0 || optiune_selectata > cos.get_map().size())
        {
            SELECTARE_PRODUS_STERGERE();
            cin >> optiune_selectata;
        }
        string cod = getKeyAtIndex(optiune_selectata);
        for(auto &x: produseStoc) {
            if(x.get_cod_bare() == cod){
                x.set_stoc_modificare_cantitate(0, cos.get_map()[x]);
                cos.del(x,0);
                cos.delete_produs(x);
            }
        }
    }

}
void STERGERE_PRODUS_COS_CUMPARATURI()
{
    system("cls");
    int optiune_selectata = 0;
    set_color(WHITE);
    printf("\n------------------------------------------------------------------------------------------------------\n");
    set_color(LIGHT_BLUE);
    printf("                                            COS CUMPARATURI                                          \n");
    set_color(WHITE);
    printf("------------------------------------------------------------------------------------------------------\n\n");
    set_color(BLUE);
    printf("[");
    set_color(GREEN);
    printf("1");
    set_color(BLUE);
    printf("]");
    set_color(RED);
    printf(" Selectare produs dorit din cos\n");
    set_color(BLUE);
    printf("[");
    set_color(GREEN);
    printf("2");
    set_color(BLUE);
    printf("]");
    set_color(RED);
    printf(" Inapoi\n");
    set_color(YELLOW);
    printf("\nIntroduceti optiunea dorita si apasati ENTER: ");
    set_color(GREEN);
    cin >> optiune_selectata;
    while (optiune_selectata < 1 || optiune_selectata > 2)
    {
        cin >> optiune_selectata;
    }
    if(optiune_selectata == 1)
    {
        AFISARE_COS_CUMPARATURI();
        SELECTARE_PRODUS_STERGERE();
        COS_CUMPARATURI();

    }
    if(optiune_selectata == 2)
        COS_CUMPARATURI();
}
void SELECTARE_PRODUS_MODIFICARE_CANTITATE()
{
    int optiune_selectata = 0, cantitate_selectata = 0;
    set_color(WHITE);
    if(cos.get_pret_total())
    {
        set_color(YELLOW);
        printf("\nIntroduceti numar produs si apasati ENTER: ");
        set_color(GREEN);
        cin >> optiune_selectata;
        while(optiune_selectata < 0 || optiune_selectata > cos.get_map().size())
        {
            SELECTARE_PRODUS_MODIFICARE_CANTITATE();
            cin >> optiune_selectata;
        }
        set_color(YELLOW);
        printf("\nActualizati cantitatea dorita si apasati ENTER: ");
        set_color(GREEN);
        cin >> cantitate_selectata;
        while(cantitate_selectata < 0 || cantitate_selectata > produseStoc[optiune_selectata-1].get_cantitate())
        {
            SELECTARE_PRODUS_MODIFICARE_CANTITATE();
            cin >> optiune_selectata;
        }
        string cod = getKeyAtIndex(optiune_selectata);
        for(auto& x: produseStoc)
        {
            if(x.get_cod_bare() == cod)
            {
                x.set_stoc_modificare_cantitate(cantitate_selectata, cos.get_map()[x]);
                cos.del(x, cantitate_selectata);
            }
        }
        //cout << endl << cos.get_map()[p];
    }
    set_color(YELLOW);
    printf("\n\n\n\t\t\tApasati orice tasta pentru a reveni la 'COS CUMPARATURI'");
    getch();
    COS_CUMPARATURI();

}
void MODIFICARE_CANTITATE()
{
    system("cls");
    int optiune_selectata = 0;
    set_color(WHITE);
    printf("\n------------------------------------------------------------------------------------------------------\n");
    set_color(LIGHT_BLUE);
    printf("                                            COS CUMPARATURI                                          \n");
    set_color(WHITE);
    printf("------------------------------------------------------------------------------------------------------\n\n");
    set_color(BLUE);
    printf("[");
    set_color(GREEN);
    printf("1");
    set_color(BLUE);
    printf("]");
    set_color(RED);
    printf(" Selectare produs dorit din cos\n");
    set_color(BLUE);
    printf("[");
    set_color(GREEN);
    printf("2");
    set_color(BLUE);
    printf("]");
    set_color(RED);
    printf(" Inapoi\n");
    set_color(YELLOW);
    printf("\nIntroduceti optiunea dorita si apasati ENTER: ");
    set_color(GREEN);
    cin >> optiune_selectata;
    while (optiune_selectata < 1 || optiune_selectata > 2)
    {
        cin >> optiune_selectata;
    }
    if(optiune_selectata == 1)
    {
        AFISARE_COS_CUMPARATURI();
        SELECTARE_PRODUS_MODIFICARE_CANTITATE();
    }
    if(optiune_selectata == 2)
        COS_CUMPARATURI();

}
void GOLIRE_COS_CUMPARATURI()
{
    //cos.get_map().erase (cos.get_map().begin(), cos.get_map().end() );
    //cos.get_map().clear();

    for(auto &x: produseStoc) {
        map<Produs, int>::iterator it = cos.get_map().find(x);
        if( it != cos.get_map().end() ) {
            x.set_stoc_modificare_cantitate(0, cos.get_map()[x]);
            cos.del(x,0);
            cos.set_pret_total();
        }
    }
    cos.delete_cos();
    COS_CUMPARATURI();
}
void AFISARE_COS_CUMPARATURI()
{
    system("cls");
    //for (auto x:produse_cos)
    //cout << x;
    set_color(WHITE);
    printf("\n------------------------------------------------------------------------------------------------------\n");
    set_color(LIGHT_BLUE);
    printf("                                            COS CUMPARATURI                                          \n");
    set_color(WHITE);
    printf("------------------------------------------------------------------------------------------------------\n\n");
    set_color(RED);
    if(cos.get_pret_total())
    {
        set_color(WHITE);
        cout<<cos;
        set_color(GREEN);
        cout<<"Pret total Cos Cumparaturi: ";
        set_color(RED);
        cout << cos.get_pret_total() << "lei";
    }
    else
        cout << "\n\t\t\t\t     COSUL DE CUMPARATURI ESTE GOL";

}
void COS_CUMPARATURI()
{
    system("cls");
    int optiune_selectata = 0;
    set_color(WHITE);
    printf("\n------------------------------------------------------------------------------------------------------\n");
    set_color(LIGHT_BLUE);
    printf("                                            COS CUMPARATURI                                          \n");
    set_color(WHITE);
    printf("------------------------------------------------------------------------------------------------------\n\n");

    set_color(BLUE);
    printf("[");
    set_color(GREEN);
    printf("1");
    set_color(BLUE);
    printf("]");
    set_color(RED);
    printf(" Vizualizare Cos Cumparaturi\n");
    set_color(BLUE);
    printf("[");
    set_color(GREEN);
    printf("2");
    set_color(BLUE);
    printf("]");
    set_color(RED);
    printf(" Modificare cantitate produs\n");
    set_color(BLUE);
    printf("[");
    set_color(GREEN);
    printf("3");
    set_color(BLUE);
    printf("]");
    set_color(RED);
    printf(" Adauga produs in Cos Cumparaturi\n");
    set_color(BLUE);
    printf("[");
    set_color(GREEN);
    printf("4");
    set_color(BLUE);
    printf("]");
    set_color(RED);
    printf(" Stergere produs Cos Cumparaturi\n");
    set_color(BLUE);
    printf("[");
    set_color(GREEN);
    printf("5");
    set_color(BLUE);
    printf("]");
    set_color(RED);
    printf(" Goleste Cos Cumparaturi\n");
    set_color(BLUE);
    printf("[");
    set_color(GREEN);
    printf("6");
    set_color(BLUE);
    printf("]");
    set_color(RED);
    printf(" Plaseaza comanda\n");
    set_color(BLUE);
    printf("[");
    set_color(GREEN);
    printf("7");
    set_color(BLUE);
    printf("]");
    set_color(RED);
    printf(" Inapoi\n");
    set_color(YELLOW);
    printf("\nIntroduceti optiunea dorita si apasati ENTER: ");
    set_color(GREEN);
    while (optiune_selectata < 1 || optiune_selectata > 7)
    {
        cin >> optiune_selectata;
        if (optiune_selectata == 1)
        {
            AFISARE_COS_CUMPARATURI();
            set_color(YELLOW);
            printf("\n\n\n\t\t\tApasati orice tasta pentru a reveni la 'COS CUMPARATURI'");
            set_color(GREEN);
            getch();
            COS_CUMPARATURI();
        }
        else if (optiune_selectata == 2)
        {
            MODIFICARE_CANTITATE();
        }
        else if (optiune_selectata == 3)
        {
            SELECTARE_PRODUS();
        }
        else if (optiune_selectata == 4)
        {
            STERGERE_PRODUS_COS_CUMPARATURI();
        }
        else if (optiune_selectata == 5)
        {
            GOLIRE_COS_CUMPARATURI();
        }
        else if (optiune_selectata == 6)
        {
            PLASARE_COMANDA();
            MODIFICARE_STOC_FISIER();
            GOLIRE_COS_CUMPARATURI();
        }
        else if (optiune_selectata == 7)
        {
            MENIU_PRINCIPAL();
        }
        else
            MENIU_PRINCIPAL();
    }
}
void CONFIRMARE_ADAUGARE_PRODUS_COS(int optiune_selectata, int cantitate_selectata)
{
    system("cls");
    set_color(WHITE);
    printf("\n---------------------------------------------------------------------------------------------------------\n");
    set_color(LIGHT_BLUE);
    printf("                                               PRODUSE MAGAZIN                                              \n");
    set_color(WHITE);
    printf("---------------------------------------------------------------------------------------------------------\n\n");
    cos.add(produseStoc[optiune_selectata - 1], cantitate_selectata);
    produseStoc[optiune_selectata - 1].set_stoc(cantitate_selectata);
    set_color(GREEN);
    cout <<"\n\t\t\tAti adaugat ";
    set_color(RED);
    cout <<cantitate_selectata;
    set_color(RED);
    cout <<" buc";
    set_color(GREEN);
    cout << " din produsul \"";
    set_color(RED);
    cout <<produseStoc[optiune_selectata - 1].get_nume();
    set_color(GREEN);
    cout <<"\" in Cosul de cumparaturi!" ;
    set_color(YELLOW);
    printf("\n\n\n\t\t\tApasati orice tasta pentru a reveni la 'MENIU PRINCIPAL'");
    getch();
    PRODUSE_MAGAZIN();
}
void SELECTARE_PRODUS()
{
    int optiune_selectata = 0, cantitate_selectata = 0;
    system("cls");
    set_color(WHITE);
    printf("\n---------------------------------------------------------------------------------------------------------\n");
    set_color(LIGHT_BLUE);
    printf("                                               PRODUSE MAGAZIN                                              \n");
    set_color(WHITE);
    printf("---------------------------------------------------------------------------------------------------------\n\n");
    for(auto item: produseStoc)
        cout << item;
    set_color(YELLOW);
    printf("\nIntroduceti optiunea dorita si apasati ENTER: ");
    set_color(GREEN);
    cin >> optiune_selectata;
    while(optiune_selectata <= 0 || optiune_selectata > produseStoc.size())
    {
        SELECTARE_PRODUS();
        cin >> optiune_selectata;
    }
    set_color(YELLOW);
    printf("\nIntroduceti cantitatea dorita si apasati ENTER: ");
    set_color(GREEN);
    cin >> cantitate_selectata;
    while(cantitate_selectata < 0 || cantitate_selectata > produseStoc[optiune_selectata-1].get_cantitate())
    {
        SELECTARE_PRODUS();
        cin >> optiune_selectata;
    }

    CONFIRMARE_ADAUGARE_PRODUS_COS(optiune_selectata, cantitate_selectata);
}
void PRODUSE_MAGAZIN()
{
    system("cls");
    int optiune_selectata = 0, key_pressed = 0;
    set_color(WHITE);
    printf("\n-----------------------------------------------------------------------------------------------------\n");
    set_color(LIGHT_BLUE);
    printf("                                             PRODUSE MAGAZIN                                            \n");
    set_color(WHITE);
    printf("-----------------------------------------------------------------------------------------------------\n\n");
    for(auto item: produseStoc)
        cout << item;
    set_color(BLUE);
    printf("[");
    set_color(GREEN);
    printf("1");
    set_color(BLUE);
    printf("]");
    set_color(RED);
    printf(" Adaugare produs in cos\n");
    set_color(BLUE);
    printf("[");
    set_color(GREEN);
    printf("2");
    set_color(BLUE);
    printf("]");
    set_color(RED);
    printf(" Inapoi la ");
    set_color(GREEN);
    printf("'MENIU PRINCIPAL'\n");
    set_color(YELLOW);
    printf("\nIntroduceti optiunea dorita si apasati ENTER: ");
    set_color(GREEN);
    while (optiune_selectata != 1 || optiune_selectata != 2)
    {
        cin>>optiune_selectata;
        if (optiune_selectata == 1)
        {
            SELECTARE_PRODUS();
        }
        else if(optiune_selectata == 2)
        {
            MENIU_PRINCIPAL();
        }
        else
            PRODUSE_MAGAZIN();
    }
}
void MENIU_PRINCIPAL()
{
    system("cls");
    int optiune_selectata = 0;
    set_color(WHITE);
    printf("\n------------------------------------------------------------------------------------------------------\n");
    set_color(LIGHT_BLUE);
    printf("                                            MENIU PRINCIPAL                                          \n");
    set_color(WHITE);
    printf("------------------------------------------------------------------------------------------------------\n\n");
    set_color(BLUE);
    printf("[");
    set_color(GREEN);
    printf("1");
    set_color(BLUE);
    printf("]");
    set_color(RED);
    printf(" Produse Magazin\n");
    set_color(BLUE);
    printf("[");
    set_color(GREEN);
    printf("2");
    set_color(BLUE);
    printf("]");
    set_color(RED);
    printf(" Cos Cumparaturi\n");
    set_color(YELLOW);
    printf("\nIntroduceti optiunea dorita si apasati ENTER: ");
    set_color(GREEN);
    while (optiune_selectata != 1 || optiune_selectata != 2)
    {
        cin >> optiune_selectata;
        if (optiune_selectata == 1)
        {
            PRODUSE_MAGAZIN();
        }
        else if (optiune_selectata == 2)
        {
            COS_CUMPARATURI();
        }
        else
        {
            MENIU_PRINCIPAL();
        }
    }

}

int main()
{
    read_stoc();
    read_comenzi();
    MENIU_PRINCIPAL();

    return 0;
}
