//
// Created by Denisa on 28-May-22.
//

#include "CosCumparaturi.h"
#include <iostream>
using namespace std;
CosCumparaturi::CosCumparaturi() {
    pret_total = 0;
}

CosCumparaturi::CosCumparaturi(vector<Produs> v) {
    this->produse = v;
    //this->numar_produse = p;
    for (int i = 0; i < v.size(); i++)
            pret_total += v[i].get_pret();
}

CosCumparaturi::~CosCumparaturi() {

}

double CosCumparaturi::get_pret() {
    return pret_total;
}

ostream &operator<<(ostream &os, CosCumparaturi &x) {
    int k = 1;
    for (auto i = 0; i < x.produse.size(); i++) {
        os << "Produs " << k++ << "\t" << x.produse[i].get_nume() << "\t\t" << x.produse[i].get_pret() <<"lei\t";//<< x.numar_produse[i] <<" buc"<<endl;
    }
    os<<endl;
    return os;
}
