#pragma once
#include "Produs.h"
#include <vector>
#include <map>

class CosCumparaturi{
    vector<Produs> produse;
    double pret_total;
    map <Produs, int> fr;
public:
    CosCumparaturi();
    CosCumparaturi(vector<Produs> p);
    CosCumparaturi(const CosCumparaturi&);
    ~CosCumparaturi();
    friend ostream &operator<<(ostream &os, CosCumparaturi &x);
    double get_pret();
};

