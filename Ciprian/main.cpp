#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <conio.h>
#include <ctime>
#include "Data.h"
#include "Produs.h"
#include "Comanda.h"

using namespace std;

vector<Produs*> produseStoc;
vector<Comanda> comenzi;
int option;

void main_menu();
void read_stoc();
void read_comenzi();
void vezi_produse();
void produs_menu(int);
void vizualizare_stoc_menu();
void adaugare_produs();
void store_content();
void modif_date();
void modif_cantitate(int);
void modif_pret(int);
void produse_expirate();
void sterge_produse_expirate();
void vezi_comenzi();

int main() {

    read_stoc();
    read_comenzi();
    main_menu();
    return 0;
}

void vezi_comenzi(){
    for(auto item : comenzi)
        cout<<item;
    system("pause");
    system("cls");
    main_menu();
}

void modify_id(vector<Produs*>::iterator i){
    for(i; i!= produseStoc.end();i++)
        (*i)->modif_id();
}

void sterge_produse_expirate(){
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    vector<Produs*>::iterator it;
    Data *d;
    for(it = produseStoc.begin();it != produseStoc.end();it++){
            if(*it == nullptr) continue;

        d = (*it)->get_data();
        if( d == nullptr)
            break;
        if(d->get_an() < (now->tm_year + 1900)){
                Produs *p = *it;
            modify_id(it);
            produseStoc.erase(it);
            p->modif_next_id();
            delete p;
            it--;
        }
        else if(d->get_luna() < (now->tm_mon + 1)){
                Produs *p = *it;
                modify_id(it);
            produseStoc.erase(it);
            p->modif_next_id();
            delete p;
            it--;
        }
                else if(d->get_zi() < (now->tm_mday)){
                    Produs *p = *it;
                    modify_id(it);
            produseStoc.erase(it);
            p->modif_next_id();
            delete p;
            it--;
                }
    }
    system("cls");
    cout<<"Produsele expirate au fost sterse\n\n";
    system("pause");
    system("cls");
    main_menu();
    store_content();
}

void produse_expirate(){
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    int k=0;
    Data *d;
    for( auto item : produseStoc){
        d = item->get_data();
        if(d->get_an() < (now->tm_year + 1900))
            {cout<<*item; k=1;}
        else if(d->get_luna() < (now->tm_mon + 1))
                {cout<<*item; k=1;}
                else if(d->get_zi() < (now->tm_mday))
                {cout<<*item; k=1;}
    }
    if(!k)
        cout<<" Nu exista produse expirate\n\n";
    cout<<"[1] Sterge produse expirate\n";
    cout<<"[2] Meniu principal\n";
    cout<<"Introdu optiunea: ";
    cin>>option;
    system("cls");
    switch(option){
    case 1:
        sterge_produse_expirate();
        break;
    case 2:
        main_menu();
        break;
    default:
        cout<<option<<" nu e o optiune valabila\n\n";
        produse_expirate();
    }
}

void modif_pret(int key){
    printf("\n---------------------------------------------------------------------------------------------------------\n");
    printf("                                             Modificare pret                                              \n");
    printf("---------------------------------------------------------------------------------------------------------\n\n");
    for(auto item : produseStoc)
        if(item->getID() == key){
            cout<<*item;
            break;
        }
    double cantit;
    cout<<"Introdu noul pret: ";
    cin>>cantit;
    for(auto item : produseStoc)
        if(item->getID() == key){
            item->set_pret(cantit);
            break;
        }
    system("cls");
    cout<<"Pretul a fost mofificat\n";
    for(auto item : produseStoc)
        if(item->getID() == key){
            cout<<*item;
            break;
        }
    system("pause");
    system("cls");
    store_content();
    produs_menu(key);
}

void modif_cantitate(int key){
    printf("\n---------------------------------------------------------------------------------------------------------\n");
    printf("                                           Modificare cantitate                                              \n");
    printf("---------------------------------------------------------------------------------------------------------\n\n");
    for(auto item : produseStoc)
        if(item->getID() == key){
            cout<<*item;
            break;
        }
    int cantit;
    cout<<"Introdu cantitatea ce va fi adaugata: ";
    cin>>cantit;
    for(auto item : produseStoc)
        if(item->getID() == key){
            *item += cantit;
            break;
        }
    system("cls");
    cout<<"Cantitatea a fost mofificata\n";
    for(auto item : produseStoc)
        if(item->getID() == key){
            cout<<*item;
            break;
        }
    system("pause");
    system("cls");
    store_content();
    produs_menu(key);
}

void produs_menu(int key){
    printf("\n---------------------------------------------------------------------------------------------------------\n");
    printf("                                               Modificare date                                              \n");
    printf("---------------------------------------------------------------------------------------------------------\n\n");
    for( auto item : produseStoc)
        if(item->getID() == key)
            cout<<*item;
    cout<<"[1] Modificare cantitate\n";
    cout<<"[2] Modificare pret\n";
    cout<<"[3] Meniu principal\n";
    cout<<"Introdu optiunea: ";
    cin>>option;
    system("cls");
    switch(option){
    case 1:
        modif_cantitate(key);
        break;
    case 2:
        modif_pret(key);
        break;
    case 3:
        main_menu();
        break;
    default:
        cout<<option<<" nu e o optiune valabila\n\n";
        produs_menu(key);
    }
}

void modif_date(){
    printf("\n---------------------------------------------------------------------------------------------------------\n");
    printf("                                               Modificare date                                              \n");
    printf("---------------------------------------------------------------------------------------------------------\n\n");
    vezi_produse();
    cout<<"Alege un produs: ";
    int prod;
    cin>>prod;
    if(prod > produseStoc.size()){
        system("cls");
        cout<<prod<<" nu e o optiune valabila\n\n";
        modif_date();
    }
    else{
        system("cls");
        produs_menu(prod);
    }
}

void store_content(){
    ofstream g("stoc.txt");
    for(auto item: produseStoc){
        g<<item->get_cod_bare()<<" "<<item->get_nume()<<" "<<item->get_cantitate()<<" "<<item->get_pret()<<" ";
        g<<item->get_data()->get_zi()<<"."<<item->get_data()->get_luna()<<"."<<item->get_data()->get_an()<<"\n";
    }
    g.close();
}

void adaugare_produs(){
    system("cls");
    printf("\n---------------------------------------------------------------------------------------------------------\n");
    printf("                                               ADAUGARE PRODUS                                              \n");
    printf("---------------------------------------------------------------------------------------------------------\n\n");
    string cod_bare,nume,data;
    int cantitate;
    double pret;
    cout<<"Cod de bare produs: ";
    cin>>cod_bare;cout<<endl;
    cout<<"Nume : ";
    cin>>nume;cout<<endl;
    cout<<"Cantitate: ";
    cin>>cantitate;cout<<endl;
    cout<<"Pret: ";
    cin>>pret;cout<<endl;
    cout<<"Data expirare: ";
    cin>>data;cout<<endl;
    Data *d = new Data(data);
    Produs *produs;
    produs = new Produs(nume, cod_bare, cantitate, pret, d);
    produseStoc.push_back(produs);
    system("cls");
    cout<<"\nProdusul a fost adaugat\n\n";
    system("pause");
    system("cls");
    store_content();
    vizualizare_stoc_menu();
}

void vizualizare_stoc_menu(){
    printf("\n---------------------------------------------------------------------------------------------------------\n");
    printf("                                               PRODUSE STOC                                              \n");
    printf("---------------------------------------------------------------------------------------------------------\n\n");
    vezi_produse();
    cout<<"[1] Modifica date produs\n";
    cout<<"[2] Vizualizare produse expirate\n";
    cout<<"[3] Adaugare produs nou\n";
    cout<<"[4] Inapoi\n";
    cout<<"Introdu optiunea: \n";
    cin>>option;
    system("cls");
    switch(option){
    case 1:
        modif_date();
        break;
    case 2:
        produse_expirate();
        break;
    case 3:
        adaugare_produs();
        break;
    case 4:
        main_menu();
        break;
    default:
        cout<<option<<" nu e o optiune valabila\n\n";
        vizualizare_stoc_menu();
    }
}

void main_menu(){
    printf("\n---------------------------------------------------------------------------------------------------------\n");
    printf("                                               MENIU PRINCIPAL                                              \n");
    printf("---------------------------------------------------------------------------------------------------------\n\n");
    cout<<"[1] Vizualizare stoc\n";
    cout<<"[2] Vizualizare istoric comenzi\n";
    cout<<"[3] Opreste aplicatia\n";
    cout<<"Introdu optiunea: ";
    cin>>option;
    system("cls");
    switch (option) {
        case 1:
            vizualizare_stoc_menu();
            break;
        case 2:
            vezi_comenzi();
            break;
        case 3:
            return; //se intoarce in main
        default:
            cout<<option<<" nu e o optiune disponibila\n";
            main_menu();
            break;
    }
}

void vezi_produse(){
    for(auto item: produseStoc)
        cout << *item;
}
void read_stoc() {
    ifstream fin("stoc.txt");
    int nr, cantitate;
    string content, nume, data, codBare;
    vector<string> items;
    double pret;
    string delim = " ";
    while (getline(fin, content)) {
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
        //cout<<"Cantitate="<<cantitate<<endl;
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
        Produs *produs;
        produs = new Produs(nume, codBare, cantitate, pret, d);
        produseStoc.push_back(produs);
    }
    fin.close();
}
void read_comenzi() {
    ifstream fin("comenzi.txt");
    int cantitate, nr;
    string data, content, codBare;
    string delim = " ";
    while (getline(fin, content)) {
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
        for (int i = 1; i <= nr; i++) {
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
        comenzi.push_back(c);
    }
    fin.close();
}
