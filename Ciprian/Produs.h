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
    int getID() { return this->id; }
    Produs(const Produs&);
    Produs(string nume, string codBare, int cantitate, double pret, Data *expData);
    ~Produs();
    Produs &operator=(const Produs &);
    friend bool operator <(const Produs & x, const Produs & y);
    friend ostream &operator<<(ostream &os, Produs &x);
    Produs& operator +=(const int);
    static void modif_next_id(){
        next_id--;
    }
    void modif_id(){
        this->id--;
    }
    string get_nume();
    double get_pret();
    string get_cod_bare();
    int get_cantitate();
    Data* get_data();
    void set_pret(double);
};

#endif // PRODUS_H
