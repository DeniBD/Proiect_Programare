//
// Created by Denisa on 28-May-22.
//

#include "Comanda.h"
#include <iostream>

using namespace std;

Comanda::Comanda() {

}

Comanda::Comanda(Data *d, vector<string> codBare, vector<int> nrProduse) {
    if (d != nullptr)
        this->data_plasare = d;
    this->nrProduse = nrProduse;
    this->codBare = codBare;
}

Comanda::~Comanda() {
    if (this->data_plasare != nullptr)
        delete this->data_plasare;
}

ostream &operator<<(ostream &os, Comanda &x) {
    for (auto i = 0; i < x.codBare.size(); i++) {
        os << x.codBare[i] << " " << x.nrProduse[i] << endl;
    }
    return os;
}
Comanda &Comanda::operator=(const Comanda &x) {
    if (this->data_plasare != nullptr)
        delete this->data_plasare;
    if (x.data_plasare != nullptr) {
        this->data_plasare = new Data;
        this->data_plasare = x.data_plasare;
    }
    this->nrProduse = x.nrProduse;
    this->codBare = x.codBare;

}
