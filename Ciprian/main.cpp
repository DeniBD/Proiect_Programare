#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <conio.h>
//#include<cstring>
#include "Data.h"
#include "Produs.h"
#include "Comanda.h"

using namespace std;

vector<Produs> produseStoc;
vector<Comanda> comenzi;
//map<Produs,int> M;
int option;

void main_menu();
void read_stoc();
void read_comenzi();
void vezi_produse();
void vizualizare_stoc_menu();
void adaugare_produs();
void store_content();

int main() {
    read_stoc();
    read_comenzi();
    main_menu();
    int k;
    cin>>k;
    return 0;
}

void store_content(){
    ofstream g("stoc.txt");
    for(auto item: produseStoc){
        g<<item.get_cod_bare()<<" "<<item.get_nume()<<" "<<item.get_cantitate()<<" "<<item.get_pret()<<" ";
        g<<item.get_data()->get_zi()<<"."<<item.get_data()->get_luna()<<"."<<item.get_data()->get_an()<<"\n";
    }

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
    Produs produs(nume, cod_bare, cantitate, pret, d);
        // cout << produs;
        produseStoc.push_back(produs);
    ///pune o confirmare
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
    cout<<"[3] Reumplere stoc\n";
    cout<<"[4] Adaugare produs nou\n";
    cout<<"[5] Inapoi\n";
    cout<<"Introdu optiunea: \n";
    cin>>option;
    switch(option){
    case 1:
        //modif_date();
        break;
    case 2:

        break;
    case 3:

        break;
    case 4:
        adaugare_produs();
        break;
    case 5:

        break;
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
            //
            break;
        case 3:
            //
            return; //modifica (se intoarce in main)
        default:
            cout<<option<<" nu e o optiune disponibila\n";
            main_menu();
            break;
    }
}

void vezi_produse(){
    for(auto item: produseStoc)
        cout << item;
}
void read_stoc() {
    ifstream fin("stoc.txt");
    int nr, cantitate;
    string content, nume, data, codBare;
    vector<string> items;
    double pret;
    string delim = " ";
    while (getline(fin, content)) {
        //cout<<content<<endl;
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
        //cout << *d;
        Produs produs(nume, codBare, cantitate, pret, d);
        // cout << produs;
        produseStoc.push_back(produs);
    }
    fin.close();
}
void read_comenzi() {
    ifstream fin("comenzi.txt");
    int cantitate, nr;
    string data, content, codBare;
    string delim = " ";
    //cout<<"Da"<<endl;;
    while (getline(fin, content)) {
            //cout<<content<<endl;
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
        // cout << c;
        comenzi.push_back(c);
    }
    //cin>>nr;
    fin.close();
}
