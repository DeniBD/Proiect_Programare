//
// Created by Daniel on 18-May-22.
//

#include "Produs.h"
#include <cstring>
#include <iostream>

using namespace std;
///Produs

Produs::Produs() {
    this->nume = nullptr;
    this->codBare = nullptr;
    this->cantitate = 0;
    this->pret = 0;
    this->expData = nullptr;
}

Produs::Produs(char *n,char *cb,int cant,double pr,Data *d){
    this->nume = new char[strlen(n)+1];
    strcpy(this->nume,n);
    this->codBare = new char[strlen(cb)+1];
    strcpy(this->codBare,cb);
    this->cantitate = cant;
    this->pret = pr;
    //this->expData = new Data;
    this->expData = d;
}

Produs::Produs(const Produs &p) {
    if(this->nume)
        delete []this->nume;
    this->nume = new char[strlen(p.nume)+1];
    strcpy(this->nume,p.nume);
    if(this->codBare)
        delete []this->nume;
    this->nume = new char[strlen(p.codBare)+1];
    strcpy(this->codBare,p.codBare);
    this->cantitate = p.cantitate;
    this->pret = p.pret;
    if(this->expData)
        delete this->expData;
    //this->expData = new Data;
    this->expData = p.expData;
}

Produs::~Produs() {
    if(this->nume)
        delete []this->nume;
    if(this->codBare)
        delete []this->codBare;
    if(this->expData)
        delete []this->expData;
}

void Produs::afisare() {
    cout<<"Produs: ";
    if(this->nume)
        cout<<this->nume<<endl;
    else
        cout<<"Fara nume"<<endl;
    cout<<"Cantitate: "<<this->cantitate<<endl;
    cout<<"Pret: "<<this->pret<<endl;
    cout<<"Data expirare: ";
    if(this->expData)
        this->expData->afisare();
    cout<<endl;
}

void Produs::modif_cantitate(int c) {
    this->cantitate += c;
}
///Data

Data::Data() {
    this->zi = 0;
    this->luna = 0;
    this->an = 0;
}

Data::Data(int z,int l,int a){
    this->zi = z;
    this->luna = l;
    this->an = a;
}

Data::Data(const Data &d) {
    this->zi = d.zi;
    this->luna = d.luna;
    this->an = d.an;
}

Data::Data(char *info) {
    char *aux;
    int z,l,a;
    aux = strtok(info,".");
    z = stoi(aux);
    aux = strtok(NULL,".");
    l = stoi(aux);
    aux = strtok(NULL,".");
    a = stoi(aux);
    this->zi = z;
    this->luna = l;
    this->an = a;
}

void Data::afisare() {
    cout<<this->zi<<"."<<this->luna<<"."<<this->an<<endl;
}

///Comanda

Comanda::Comanda() {
    this->produse = nullptr;
    this->dataPlasare = nullptr;
    this->pret = 0;
    this->nrProduse = -1;
}

Comanda::Comanda(Produs **p, Data *d, double pr, int np) {
    this->produse = new Produs*[np];
    this->produse = p;
    this->dataPlasare = new Data;
    this->dataPlasare = d;
    this->pret = pr;
    this->nrProduse = np;
}

Comanda::Comanda(const Comanda &c) {
    if(this->produse)
        delete []this->produse;
    this->produse = new Produs*[c.nrProduse];
    this->produse = c.produse;
    if(this->dataPlasare)
        delete dataPlasare;
    this->dataPlasare = new Data;
    this->dataPlasare = c.dataPlasare;
    this->nrProduse = c.nrProduse;
}

Comanda::~Comanda() {
    if(this->produse)
        delete []this->produse;
    if(this->dataPlasare)
        delete this->dataPlasare;
}

///CosCumparaturi

CosCumparaturi::CosCumparaturi() {
    this->produse = nullptr;
    this->pret = 0;
    this->nrProduse = -1;
}

CosCumparaturi::CosCumparaturi(Produs **p, double pr, int n) {
    this->produse = new Produs*[n];
    this->pret = pr;
    this->nrProduse = n;
}

CosCumparaturi::CosCumparaturi(const CosCumparaturi &c) {
    if(this->produse)
        delete []this->produse;
    this->produse = new Produs*[c.nrProduse];
    this->produse = c.produse;
    this->pret = c.pret;
    this->nrProduse = c.nrProduse;
}

CosCumparaturi::~CosCumparaturi() {
    if(this->produse)
        delete []this->produse;
}