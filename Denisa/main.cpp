#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <conio.h>
#include "Data.h"
#include "Produs.h"
#include "Comanda.h"
#include "CosCumparaturi.h"
vector<Produs> produseStoc;
vector<Comanda> comenzi;
vector<Produs> produse_cos;
vector<int> nr_produse;
CosCumparaturi cos;
void MENIU_PRINCIPAL();
void SELECTARE_PRODUS();
void PRODUSE_MAGAZIN();
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
        cantitate = stoi(content.substr(0, pos));
        content = content.substr(pos + delim.length());
        //pret
        pos = content.find(delim);
        pret = stoi(content.substr(0, pos));
        content = content.substr(pos + delim.length());
        //data
        pos = content.find(delim);
        data = content.substr(0, pos);
        content = content.substr(pos + delim.length());
        Data *d = new Data(data);
        //cout << *d;
        Produs produs(nume, codBare, cantitate, pret, d);
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
        // cout<<c;
        comenzi.push_back(c);
    }
    fin.close();
}
bool cautare_produs_cos(int optiune_selectata){
    for (int i = 0; i < produse_cos.size(); i++)
        if(produse_cos[i].get_nume() == produse_cos[optiune_selectata - 1].get_nume())
            return 0;
    return 1;
}
void AFISARE_COS_CUMPARATURI(){
    system("cls");
    cos = CosCumparaturi(produse_cos);
    printf("\n------------------------------------------------------------------------------------------------------\n");
    printf("                                            COS CUMPARATURI                                          \n");
    printf("------------------------------------------------------------------------------------------------------\n\n");
    cout<<cos;
    cout<<"Pret total Cos Cumparaturi: ";
    cout << cos.get_pret();
}
void COS_CUMPARATURI(){
    system("cls");
    int optiune_selectata = 0;
    printf("\n------------------------------------------------------------------------------------------------------\n");
    printf("                                            COS CUMPARATURI                                          \n");
    printf("------------------------------------------------------------------------------------------------------\n\n");
    printf("[1] Vizualizare Cos Cumparaturi\n");
    printf("[2] Modificare cantitate produs\n");
    printf("[3] Adauga produs in Cos Cumparaturi\n");
    printf("[4] Stergere produs Cos Cumparaturi\n");
    printf("[5] Goleste Cos Cumparaturi\n");
    printf("[6] Plaseaza comanda\n");
    printf("[7] Inapoi\n");
    printf("\nIntroduceti optiunea dorita si apasati ENTER: ");
    while (optiune_selectata < 1 || optiune_selectata > 7) {
        cin >> optiune_selectata;
        if (optiune_selectata == 1) {
            //AFISARE_COS_CUMPARATURI();
        } else if (optiune_selectata == 2) {
            //MODIFICARE_CANTITATE();
        } else if (optiune_selectata == 3) {
            SELECTARE_PRODUS();
        } else if (optiune_selectata == 4) {
            //STERGERE_PRODUS_COS_CUMPARATURI();
        } else if (optiune_selectata == 5) {
            //GOLIRE_COS_CUMPARATURI();
        } else if (optiune_selectata == 6) {
            //PLASARE_COMANDA();
        } else if (optiune_selectata == 7) {
            MENIU_PRINCIPAL();
        } else
            MENIU_PRINCIPAL();
    }
}
void CONFIRMARE_ADAUGARE_PRODUS_COS(int optiune_selectata){
    system("cls");
    printf("\n---------------------------------------------------------------------------------------------------------\n");
    printf("                                               PRODUSE MAGAZIN                                              \n");
    printf("---------------------------------------------------------------------------------------------------------\n\n");
    //produse_cos.push_back(produseStoc[optiune_selectata - 1]);
    //ADAUGARE_PRODUS_COS
    /*if(cautare_produs_cos(optiune_selectata)) {
        produse_cos.push_back(produseStoc[optiune_selectata - 1]);
        nr_produse[optiune_selectata - 1]++;
    }
    else
        nr_produse[optiune_selectata - 1]++;
*/
    cout <<"\n\t\t\t\tAti adaugat "<<produseStoc[optiune_selectata - 1].get_nume()<<" in Cosul de cumparaturi!" ;
    printf("\n\n\n\t\t\tApasati orice tasta pentru a reveni la 'MENIU PRINCIPAL'");
    getch();
    PRODUSE_MAGAZIN();
}
void SELECTARE_PRODUS(){
    system("cls");
    int optiune_selectata = 0;
    system("cls");
    printf("\n---------------------------------------------------------------------------------------------------------\n");
    printf("                                               PRODUSE MAGAZIN                                              \n");
    printf("---------------------------------------------------------------------------------------------------------\n\n");
    for(auto item: produseStoc)
        cout << item;
    printf("\nIntroduceti optiunea dorita si apasati ENTER: ");
    while(optiune_selectata <= 0 || optiune_selectata > produseStoc.size()) {
        cin >> optiune_selectata;
        if(optiune_selectata <=0 || optiune_selectata >produseStoc.size())
            SELECTARE_PRODUS();
        else
            CONFIRMARE_ADAUGARE_PRODUS_COS(optiune_selectata);
    }
}
void PRODUSE_MAGAZIN(){
    system("cls");
    int optiune_selectata = 0, key_pressed = 0;

    printf("\n-----------------------------------------------------------------------------------------------------\n");
    printf("                                             PRODUSE MAGAZIN                                            \n");
    printf("-----------------------------------------------------------------------------------------------------\n\n");
    printf("[1] Adaugare produs in cos\n");
    printf("[2] Inapoi la 'MENIU PRINCIPAL'\n");
    printf("\nIntroduceti optiunea dorita si apasati ENTER: ");

    while (optiune_selectata != 1 || optiune_selectata != 2) {
        cin>>optiune_selectata;
        if (optiune_selectata == 1) {
            SELECTARE_PRODUS();
        }
        else if(optiune_selectata == 2) {
            MENIU_PRINCIPAL();
        }
        else
            PRODUSE_MAGAZIN();
    }
}
void MENIU_PRINCIPAL(){
    system("cls");
    int optiune_selectata = 0, key_pressed = 0;
    printf("\n------------------------------------------------------------------------------------------------------\n");
    printf("                                            MENIU PRINCIPAL                                          \n");
    printf("------------------------------------------------------------------------------------------------------\n\n");
    printf("[1] Produse Magazin\n");
    printf("[2] Cos Cumparaturi\n");
    printf("\nIntroduceti optiunea dorita si apasati ENTER: ");
    while (optiune_selectata != 1 || optiune_selectata != 2) {
        cin >> optiune_selectata;
        if (optiune_selectata == 1) {
            PRODUSE_MAGAZIN();
        } else if (optiune_selectata == 2) {
            COS_CUMPARATURI();
        }
        else
            MENIU_PRINCIPAL();
    }
}


int main() {
    /*
    read_stoc();
    for(auto item: produseStoc)
        cout << item;
    read_comenzi();
    for (int i = 0; i < comenzi.size(); i++)
        cout << comenzi[i];
        */
    read_stoc();
    read_comenzi();
    MENIU_PRINCIPAL();
    return 0;
}
