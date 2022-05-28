//
// Created by Denisa on 28-May-22.
//

#ifndef PROIECT_PROGRAMARE_PRODUS_H
#define PROIECT_PROGRAMARE_PRODUS_H


#include <string>
#include <vector>
#include "Data.h"

#pragma once

using namespace std;

class Produs {
    string nume;
    string codBare;
    int cantitate;
    double pret;
    Data *expData;
    int id;
    static int next_id;
public:
    Produs();
    int getID() { return id; }
    Produs(string nume, string codBare, int cantitate, double pret, Data *expData);
    ~Produs();
    Produs &operator=(const Produs &);
    friend ostream &operator<<(ostream &os, Produs &x);
    string get_nume();
    double get_pret();

};



#endif //PROIECT_PROGRAMARE_PRODUS_H
