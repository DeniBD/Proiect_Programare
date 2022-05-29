//
// Created by Denisa on 28-May-22.
//

#include "CosCumparaturi.h"
#include <iostream>
#include<map>
using namespace std;
CosCumparaturi::CosCumparaturi() {
    pret_total = 0;
}

CosCumparaturi::CosCumparaturi(vector <Produs> p) {
    this->produse = p;
    /*for (int i = 0; i < produse.size(); i++){
            pret_total += produse[i].get_pret;
        if (fr.find(produse[i]) == fr.end()) {

                fr[produse[i]] = 1;
            }

            // Else update the frequency
            else {
                fr[produse[i]]++;
            }
    }
    */
}

CosCumparaturi::~CosCumparaturi() {

}

double CosCumparaturi::get_pret() {
    return pret_total;
}

ostream &operator<<(ostream &os, CosCumparaturi &x) {
    int k = 1;
    for (auto i = 0; i < x.produse.size(); i++) {
        os << "Produs " << k++ << "\t" << x.produse[i].get_nume() << "\t\t" << x.produse[i].get_pret() <<"lei\t"<<x.fr[x.produse[i]]<<endl;
    }
    os<<endl;
    return os;
}
