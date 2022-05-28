//
// Created by Denisa on 28-May-22.
//

#include "Produs.h"
#include <string>
#include <iostream>

using namespace std;
int Produs::next_id = 1;
ostream &operator<<(ostream &os, Produs &x) {
    os <<"["<<x.getID()<<"] \tNume produs: " << x.nume << endl << "\tPret produs: " << x.pret <<" lei"<< endl << "\tData expirare: " << *x.expData << endl;
    return os;
}

Produs::Produs(string nume, string codBare, int cantitate, double pret, Data *expData) {
    id = next_id++;
    this->nume = nume;
    this->codBare = codBare;
    this->cantitate = cantitate;
    this->pret = pret;
    if(expData != nullptr)
        this->expData = expData;
}
Produs& Produs::operator=(const Produs & x) {
    if(this->expData != nullptr)
        delete this->expData;
    if(x.expData != nullptr) {
        this->expData = new Data;
        this->expData = x.expData;
    }
    this->pret = x.pret;
    this->cantitate = x.cantitate;
    this->nume = x.nume;
    this->codBare = x.codBare;

}
Produs::Produs() {
}

Produs::~Produs() {
    if(this->expData != nullptr)
        delete this->expData;
}

string Produs::get_nume() {
    return nume;
}

double Produs::get_pret() {
    return pret;
}
