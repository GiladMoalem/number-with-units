#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

namespace ariel{

class NumberWithUnits{
    private:
    double number;
    string unit;

    public:
    NumberWithUnits(double num, string unit2); // : number(num),unit(unit2){}
    ~NumberWithUnits(){}

    static void read_units(ifstream& units_file){}
    
    NumberWithUnits operator +(const NumberWithUnits num);
    NumberWithUnits operator +(); //posetive
    NumberWithUnits operator +=(const NumberWithUnits num);
    NumberWithUnits operator -(const NumberWithUnits num);
    NumberWithUnits operator -(); //negative 
    NumberWithUnits operator -=(const NumberWithUnits num);

    bool operator ==(const NumberWithUnits num);
    bool operator >=(const NumberWithUnits num);
    bool operator >(const NumberWithUnits num);
    bool operator <(const NumberWithUnits num);
    bool operator <=(const NumberWithUnits num);
    bool operator !=(const NumberWithUnits num);

    NumberWithUnits operator ++();  // ++num
    NumberWithUnits operator ++(int); // num++
    NumberWithUnits operator --();
    NumberWithUnits operator --(int);

    NumberWithUnits operator *(const double num);

    friend ostream& operator <<(ostream& os, NumberWithUnits num);
    friend istream& operator >>(istream& in, NumberWithUnits& num);
    friend NumberWithUnits operator *(double num1, NumberWithUnits num2);
};
}