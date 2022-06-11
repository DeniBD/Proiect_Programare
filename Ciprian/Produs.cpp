//
// Created by Daniel on 29-May-22.
//

#include "Produs.h"
#include <string>
#include <iostream>

using namespace std;

int Produs::next_id = 1;

ostream &operator<<(ostream &os, Produs &x) {
    os <<"["<<x.getID()<<"] \tNume produs: " << x.nume << endl << "\tPret produs: " << x.pret <<" lei"<< endl <<"\tCantitate: "<<x.cantitate<<endl<< "\tData expirare: " << *x.expData << endl;
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
    this->id = x.id;
    return *this;
}
bool operator <(const Produs &x, const Produs &y) {

}
Produs::Produs() {
    this->cantitate = 0;
    this->nume = "";
    this->codBare = "";
    this->expData = nullptr;
    this->pret = 0;
    this->id = next_id++;
}

Produs::Produs(const Produs &p){
    this->nume = p.nume;
    this->codBare = p.codBare;
    this->cantitate = p.cantitate;
    this->pret = p.pret;
    this->expData = p.expData;
    this->id = p.id;
}

Produs::~Produs() {
    if(this->expData != nullptr)
        delete this->expData;

}

Produs& Produs::operator +=(const int c){
    this->cantitate += c;
    return *this;
}



string Produs::get_nume() {
    return nume;
}

double Produs::get_pret() {
    return pret;
}

string Produs::get_cod_bare(){
    return this->codBare;
}

int Produs::get_cantitate(){
    return this->cantitate;
}

Data* Produs::get_data(){
    if(this->expData != nullptr)
        return this->expData;
    else
        return nullptr;
}

void Produs::set_pret(double p){
    this->pret = p;
}
