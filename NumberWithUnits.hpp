#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

using namespace std;
// Map static ezer(Map& map1,Map& map2);
// void static func_for_fill_the_deep_map( map<string,double>& main_map, Map& map1, string word);
typedef map<string,map<string,double>> Map;


namespace ariel{

class NumberWithUnits{
    private:
    double number;
    string unit;


    public:
    NumberWithUnits(double num, string unit2); // : number(num),unit(unit2){}
  //  ~NumberWithUnits(){}
    static void read_units(ifstream& units_file);
    
    NumberWithUnits operator +(const NumberWithUnits num);
    NumberWithUnits operator +(); //posetive
    NumberWithUnits operator +=(const NumberWithUnits num);
    NumberWithUnits operator -(const NumberWithUnits num);
    NumberWithUnits operator -(); //negative 
    NumberWithUnits operator -=(const NumberWithUnits num);

    // bool operator ==(const NumberWithUnits num);
    // bool operator >=(const NumberWithUnits num);
    // bool operator >(const NumberWithUnits num);
    // bool operator <(const NumberWithUnits num);
    // bool operator <=(const NumberWithUnits num);
    // bool operator !=(const NumberWithUnits num);

    friend  bool operator ==(const NumberWithUnits num1,const NumberWithUnits num2);
    friend  bool operator !=(const NumberWithUnits num1,const NumberWithUnits num2);
    friend  bool operator >=(const NumberWithUnits num1,const NumberWithUnits num2);
    friend  bool operator <=(const NumberWithUnits num1,const NumberWithUnits num2);
    friend  bool operator <(const NumberWithUnits num1,const NumberWithUnits num2);
    friend  bool operator >(const NumberWithUnits num1,const NumberWithUnits num2);
    
    NumberWithUnits& operator ++();  // ++num
    NumberWithUnits operator ++(int); // num++
    NumberWithUnits& operator --();
    NumberWithUnits operator --(int);

    NumberWithUnits operator *(const double num);

    friend ostream& operator <<(ostream& os, NumberWithUnits num);
    friend istream& operator >>(istream& in, NumberWithUnits& num);
    friend NumberWithUnits operator *(double num1, NumberWithUnits num2);

    friend bool compare(const NumberWithUnits num1,const NumberWithUnits num2,int);
    friend double compare(const NumberWithUnits num1,const NumberWithUnits num2);
    
};
}
