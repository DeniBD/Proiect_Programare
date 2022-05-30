#ifndef PRODUS_H
#define PRODUS_H

#include <string>
#include <vector>
#include "Data.h"

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
    friend bool operator <(const Produs & x, const Produs & y);
    friend ostream &operator<<(ostream &os, Produs &x);
    string get_nume();
    double get_pret();
    string get_cod_bare();
    int get_cantitate();
    Data* get_data();

};

#endif // PRODUS_H
