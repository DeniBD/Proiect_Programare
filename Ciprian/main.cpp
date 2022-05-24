#include <iostream>
#include <cstring>
#include <fstream>
#include "Produs.h"

using namespace std;

Produs **produseStoc;
int nrProduseStoc = -1;
int option;

void read_content();
void main_menu();
void vizualizare_stoc();
void modificare_cantitate(int);
void alege_produs();
void alege_produs_menu(int);
void vizualizare_stoc_menu();

int main() {
    read_content();
    main_menu();

    /// sa nu se inchida consola
    int a;
    cin>>a;
    return 0;
}

void vizualizare_stoc_menu(){
    vizualizare_stoc();
    cout<<"1. Modifica date produs\n";
    cout<<"2. Vizualizare produse expirate\n";
    cout<<"3. Reumplere stoc\n";
    cout<<"4. Adaugare produs nou\n";
    cout<<"5. Inapoi\n";
}

void alege_produs_menu(int k){
    produseStoc[k]->afisare();
    cout<<"1. Modificare cantitate\n";
    cout<<"2. Modificare pret\n";
    cout<<"3. Inapoi\n";
    cout<<"Introdu optiunea: ";
    cin>>option;
    system("cls");
    switch(option){
        case 1:
            modificare_cantitate(k);
            break;
        case 2:
            //
            break;
        case 3:
            //
            break;
        default:
            cout<<option<<" nu e o optiune disponibila\n";
            alege_produs_menu(k);
            break;
    }
}

void alege_produs(){
    vizualizare_stoc();
    cout<<"Alege un produs: ";
    cin>>option;
    system("cls");
    if(option > 0 && option < nrProduseStoc){
        ///e in option-1!
        alege_produs_menu(option - 1);
    }
    else{
        cout<<option<<" nu e o optiune disponibila\n";
        alege_produs();
    }
}

void modificare_cantitate(int k){
    produseStoc[k]->afisare();
    cout<<"Introduceti cantitatea adaugata: \n";
    int c;
    cin>>c;
    produseStoc[k]->modif_cantitate(c);
    cout<<"\nCantitatea a fost modificata\n\n";
    alege_produs();
}

void vizualizare_stoc(){
    for(int i=0;i<=nrProduseStoc;i++) {
        cout<<i+1<<". ";
        produseStoc[i]->afisare();
    }
}

void main_menu(){
    cout<<"////// MENIU PRINCIPAL //////"<<endl;
    cout<<"1. Vizualizare stoc\n";
    cout<<"2. Vizualizare istoric comenzi\n";
    cout<<"3. Opreste aplicatia\n";
    cout<<"Introdu optiunea: ";
    cin>>option;
    system("cls");
    switch (option) {
        case 1:
            vizualizare_stoc();
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

void read_content(){
    ifstream f("E:\\Facultate\\Sem2\\PP\\Proiect C++\\clproject\\stoc.txt");
    int nr,cantitate;
    char content[50],nume[30],codBare[30],data[10];
    double pret;
    f>>nr;
    produseStoc = new Produs*[nr];
    f.ignore();
    while(f.getline(content,50)){
        char *token;
        token = strtok(content," ");
        strcpy(codBare,token);
        token = strtok(NULL," ");
        strcpy(nume,token);
        token = strtok(NULL," ");
        cantitate = stoi(token);
        token = strtok(NULL," ");
        pret = stod(token);
        token = strtok(NULL," ");
        strcpy(data,token);
        Data *d;
        d = new Data(data);
        produseStoc[++nrProduseStoc] = new Produs(nume,codBare,cantitate,pret,d);
    }
    f.close();
}