#include "Produs.h"
#include "CosCumparaturi.h"
#include <string>
#include <iostream>

using namespace std;

int Produs::next_id = 1;
ostream &operator<<(ostream &os, Produs &x)
{
    os <<"["<< x.getID() <<"] \tNume produs: "<< x.nume << endl << "\tPret produs: "<< x.pret<<" lei"<< endl << "\tData expirare: "<< *x.expData <<endl<<"\tNr. Produse pe stoc:"<< x.cantitate <<endl<<endl;
    return os;
}

Produs::Produs(string nume, string codBare, int cantitate, double pret, Data *expData)
{
    id = next_id++;
    this->nume = nume;
    this->codBare = codBare;
    this->cantitate = cantitate;
    this->pret = pret;
    if(expData != nullptr)
        this->expData = expData;
}
Produs& Produs::operator=(const Produs & x)
{
    if(&x == this) return *this;
    if(this->expData != nullptr)
        delete this->expData;
    if(x.expData != nullptr)
    {
        this->expData = new Data;
        this->expData = x.expData;
    }
    this->pret = x.pret;
    this->cantitate = x.cantitate;
    this->nume = x.nume;
    this->codBare = x.codBare;

    return *this;
}
bool Produs:: operator<(const Produs &ob) const
{
    return  codBare < ob.codBare;
}
/*
bool Produs:: operator()(const Produs &lhs, const Produs &rhs) const
    {
        if (lhs.codBare == rhs.codBare)
            return lhs.codBare < rhs.codBare;
    }
*/
Produs::~Produs()
{
    if(this->expData != nullptr)
        delete this->expData;
}

string Produs::get_nume() const
{
    return nume;
}

double Produs::get_pret() const
{
    return pret;
}

string Produs::get_cod_bare() const
{
    return this->codBare;
}
void Produs::set_stoc(int x)
{
    this->cantitate -= x;
}
void Produs::set_stoc_modificare_cantitate(int x, int fr)
{
    if(x > fr)
        this->cantitate -= abs(x - fr);
    else
        this->cantitate += abs(x - fr);

}
int Produs::get_cantitate() const
{
    return this->cantitate;
}

Data* Produs::get_data() const
{
    return this->expData;
}
