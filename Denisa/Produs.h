#ifndef PROIECT_PROGRAMARE_PRODUS_H
#define PROIECT_PROGRAMARE_PRODUS_H

#include <string>
#include <vector>
#include "Data.h"

using namespace std;

class Produs
{
    string nume;
    string codBare;
    int cantitate;
    double pret;
    Data *expData;
    int id;
    static int next_id;
public:
    Produs() {}
    int getID()
    {
        return id;
    }
    Produs(string nume, string codBare, int cantitate, double pret, Data *expData);
    ~Produs();
    Produs &operator=(const Produs &);
    bool operator()(const Produs &lhs, const Produs &rhs) const;
    bool operator<(const Produs &ob) const;
    friend ostream &operator<<(ostream &os, Produs &x);
    string get_nume() const;
    double get_pret() const;
    string get_cod_bare() const;
    int get_cantitate()const;
    void set_stoc(int x);
    void set_stoc_modificare_cantitate(int x, int fr);
    Data* get_data() const;
    friend void set_color(int color_code);

};



#endif //PROIECT_PROGRAMARE_PRODUS_H
