#ifndef PROIECT_PROGRAMARE_DATA_H
#define PROIECT_PROGRAMARE_DATA_H


#include <string>

using namespace std;

class Data {
    int zi;
    int luna;
    int an;
public:
    Data();

    Data(int zi, int luna, int an);

    Data(const Data &);

    Data(string info);

    ~Data();

    friend ostream &operator<<(ostream &os, Data &x);
};


#endif //PROIECT_PROGRAMARE_DATA_H
