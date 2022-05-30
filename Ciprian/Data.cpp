#include "Data.h"

#include <iostream>

using namespace std;

Data::Data() {
    this->zi = 0;
    this->luna = 0;
    this->an = 0;
}

Data::Data(int z, int l, int a) {
    this->zi = z;
    this->luna = l;
    this->an = a;
}

Data::Data(const Data &d) {
    this->zi = d.zi;
    this->luna = d.luna;
    this->an = d.an;
}

Data::Data(string info) {

    size_t pos = 0;
    string delim = ".";
    //zi
    pos = info.find(delim);
    this->zi = stoi(info.substr(0, pos));
    info = info.substr(pos + delim.length());
    //luna
    pos = info.find(delim);
    this->luna = stoi(info.substr(0, pos));
    info = info.substr(pos + delim.length());
    //an
    pos = info.find(delim);
    this->an = stoi(info.substr(0, pos));
    info = info.substr(pos + delim.length());
}

/*Data::~Data()
{

}*/
int Data::get_zi(){
    return this->zi;
}

int Data::get_luna(){
    return this->luna;
}

int Data::get_an(){
    return this->an;
}

ostream &operator<<(ostream &os, Data &x) {
    cout << x.zi << "." << x.luna << "." << x.an << endl;
    return os;
}
