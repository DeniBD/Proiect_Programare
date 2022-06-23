//
// Created by Denisa on 28-May-22.
//

#include "Produs.h"
#include "Data.h"
#include <vector>
#include <string>
using namespace std;


class Comanda {
    vector<string> codBare;
    vector<int> nrProduse;
    Data *data_plasare;
public:
    Comanda();
    Comanda(Data *data, vector<string> c, vector<int> nrProduse);
    ~Comanda();
    Comanda &operator=(const Comanda &);
    friend ostream &operator<<(ostream &os, Comanda &x);
};


