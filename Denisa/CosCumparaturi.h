//
// Created by Denisa on 28-May-22.
//

#ifndef PROIECT_PROGRAMARE_COSCUMPARATURI_H
#define PROIECT_PROGRAMARE_COSCUMPARATURI_H

#include "Produs.h"
#include <vector>
class CosCumparaturi{
    vector<Produs> produse;
    double pret_total;
    //vector<int> numar_produse;
public:
    CosCumparaturi();
    CosCumparaturi(vector<Produs>);
    CosCumparaturi(const CosCumparaturi&);
    ~CosCumparaturi();
    friend ostream &operator<<(ostream &os, CosCumparaturi &x);
    double get_pret();
};



#endif //PROIECT_PROGRAMARE_COSCUMPARATURI_H
