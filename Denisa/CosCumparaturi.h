#pragma once
#include "Produs.h"
#include <vector>
#include <map>

class CosCumparaturi
{
    double pret_total;
    map <Produs, int> fr;
public:
    CosCumparaturi();
    CosCumparaturi(const CosCumparaturi&);
    void del (Produs& p, int cantitate);
    void add(Produs& p, int cantitate);
    void delete_produs(Produs &p);
    ~CosCumparaturi() {}
    friend ostream &operator<<(ostream &os, const CosCumparaturi &x);
    double get_pret_total() const;
    void set_pret_total();
    void delete_cos();
    map<Produs, int> get_map() const;
};

