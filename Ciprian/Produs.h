//
// Created by Daniel on 18-May-22.
//

#ifndef CLPROJECT_PRODUS_H
#define CLPROJECT_PRODUS_H

class Data;

class Produs {
    char *nume;
    char *codBare;
    int cantitate;
    double pret;
    Data *expData;
public:
    Produs();
    Produs(char*,char*,int,double,Data*);
    Produs(const Produs&);
    ~Produs();
    void afisare();
    void modif_cantitate(int);
};

class Data{
    int zi;
    int luna;
    int an;
public:
    Data();
    Data(int,int,int);
    Data(char*);
    Data(const Data&);
    void afisare();
};

class Comanda{
    Produs **produse;
    Data *dataPlasare;
    double pret;
    int nrProduse;
public:
    Comanda();
    Comanda(Produs**,Data*,double,int);
    Comanda(const Comanda&);
    ~Comanda();
};

class CosCumparaturi{
    Produs **produse;
    double pret;
    int nrProduse;
public:
    CosCumparaturi();
    CosCumparaturi(Produs**,double,int);
    CosCumparaturi(const CosCumparaturi&);
    ~CosCumparaturi();
};
#endif //CLPROJECT_PRODUS_H
