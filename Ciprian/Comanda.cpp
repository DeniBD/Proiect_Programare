#include "Comanda.h"
#include <iostream>

using namespace std;

Comanda::Comanda() {
    this->data_plasare = nullptr;
}

Comanda::Comanda(Data *d, vector<string> codBare, vector<int> nrProduse) {
    if (d != nullptr)
        this->data_plasare = d;
    this->nrProduse = nrProduse;
    this->codBare = codBare;
}

Comanda::Comanda(const Comanda &c){
    this->codBare = c.codBare;
    this->nrProduse = c.nrProduse;
    this->data_plasare = c.data_plasare;
}

Comanda::~Comanda() {
    /*if (this->data_plasare != nullptr)
        delete this->data_plasare;*/
}

ostream &operator<<(ostream &os, Comanda &x) {
    os << "Data plasare comanda: " << *x.data_plasare;
    os << "\t\tCod de bare produs " << "\t" << "Cantitate produs " << endl;
    int k = 1;
    for (auto i = 0; i < x.codBare.size(); i++) {
        os << "Produs " << k++ << "\t\t" << x.codBare[i] << "\t\t\t" << x.nrProduse[i] << endl;
    }
    os<<endl;
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
