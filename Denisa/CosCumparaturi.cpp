//
// Created by Denisa on 28-May-22.
//

#include "CosCumparaturi.h"
#include "Produs.h"
#include <iostream>
#include<map>
using namespace std;
CosCumparaturi::CosCumparaturi()
{
    pret_total = 0;
}
void CosCumparaturi::del (Produs& p, int cantitate)
{
    if(cantitate > fr[p])
        this->pret_total += p.get_pret() * abs(fr[p] - cantitate);
    else
        this->pret_total -= p.get_pret() * abs(fr[p] - cantitate);

    this->fr[p] = cantitate;
}

void CosCumparaturi::add (Produs& p, int cantitate)
{
    this->pret_total += p.get_pret() * cantitate;
    if (this->fr.find(p) == this->fr.end())
    {

        this->fr.insert(make_pair(p, cantitate));
    }

    else
    {
        this->fr[p] += cantitate;
    }

}
void CosCumparaturi::set_pret_total()
{
    pret_total = 0;
}

double CosCumparaturi::get_pret_total() const
{
    return pret_total;
}
map <Produs, int> CosCumparaturi:: get_map()const
{
    return fr;
}
void CosCumparaturi ::delete_cos(){
    fr.clear();
}
void CosCumparaturi ::delete_produs(Produs &p){
    fr.erase(p);
}
ostream &operator<<(ostream &os, const CosCumparaturi &x)
{
    int k = 1;
    for(auto &it : x.fr)
        if(it.second != 0)
        {
            os << "[" << k++ << "]\t" << it.first.get_nume() << "\t\t"<< it.first.get_pret() << " lei\t\t" << it.second <<" buc\t\t" << it.first.get_pret()* it.second << " lei"<< endl;
        }
    os<<endl;
    return os;
}
