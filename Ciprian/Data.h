#ifndef DATA_H
#define DATA_H

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
    int get_zi();
    int get_luna();
    int get_an();

    //~Data();

    friend ostream &operator<<(ostream &os, Data &x);
};


#endif // DATA_H
