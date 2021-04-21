#include "NumberWithUnits.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <ostream>

namespace ariel{
    
    NumberWithUnits::NumberWithUnits(double num, string unit){
        number = num;
        this-> unit = unit;
    }

    // static void NumberWithUnits::read_units(ifstream& units_file){
    // }
    
    NumberWithUnits NumberWithUnits::operator +(const NumberWithUnits num){return *this;}
    //posetive
    NumberWithUnits NumberWithUnits::operator +() {
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator +=(const NumberWithUnits num){ return *this;}
    NumberWithUnits NumberWithUnits::operator -(const NumberWithUnits num){return *this;}
//negative
    NumberWithUnits NumberWithUnits::operator -(){
        NumberWithUnits neg = *this;
        neg.number *= (-1);
        return neg;
    }
    NumberWithUnits NumberWithUnits::operator -=(const NumberWithUnits num){return *this;}

    bool NumberWithUnits::operator ==(const NumberWithUnits num){return false;}
    bool NumberWithUnits::operator >=(const NumberWithUnits num){return false;}
    bool NumberWithUnits::operator >(const NumberWithUnits num){return 0;}
    bool NumberWithUnits::operator <(const NumberWithUnits num){return 0;}
    bool NumberWithUnits::operator <=(const NumberWithUnits num){return false;}
    bool NumberWithUnits::operator !=(const NumberWithUnits num){return false;}

// ++num
    NumberWithUnits NumberWithUnits::operator ++(){
        this->number++;
        return *this;
    }  
// num++
    NumberWithUnits NumberWithUnits::operator ++(int){
        NumberWithUnits old = *this;
        this->number++;
        return old;
    } 
    NumberWithUnits NumberWithUnits::operator --(){
        this->number--;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator --(int){
        NumberWithUnits old = *this;
        this->number--;
        return old;
        }

    NumberWithUnits NumberWithUnits::operator *(const double num){
        this->number *=num;
        return *this;
        }

    ostream& operator <<(ostream& os, NumberWithUnits num){
        os << num.number<<'['<< num.unit << ']';
        return os;
    }
   
    
    istream& operator >>(istream& in, NumberWithUnits& num){
        string str,unit;
        char c;
        int number;
       /*
        string s;
        ostringstream os;
        os << in.rdbuf();
        s = os.str();
        */
        // cout << s << endl;
        // in2 >> origin;
       

        // cout << origin <<endl;
        if( !(in >> number))throw invalid_argument("invalid argument: \n\"" "  dosnt start with a number!");
        if( !(in >> c)||(c!='[')) throw invalid_argument("invalid argument:\n\""  "\" after the number should have a '['" );
        
        // vv need to check if str in the list and if is not empty.
        if( !(in >> str)) throw invalid_argument("invalid argument");
        if(str.at(str.length()-1)==']'){
            unit = str.substr(0, str.length()-1);
        }else{
            unit = str;
            if(!(in >> c)||(c!=']')) throw invalid_argument("invalid argument:\n\"" "\" after the unit should have a ']'" );
        }

        if(in >> str) throw invalid_argument("overmuch arguments: after the ']' should be not argument! but -> "+str);
        num.number = number;
        num.unit = unit;
  
/*

        if(in.good()){ cout << "good" << endl;}
        cout<<num.number<<endl;
       
        cout << in.str()<<endl;
        in >> c;
        cout<<c<<endl;
        
        cout << in.str()<<endl;

        in >> str;
        cout<<str<<endl;
        in >> str;
        cout <<str <<endl;

        size_t i = 0;

        while(i<str.length() && str.at(i)!='[')
        {
            if(str.at(i)>='0' && str.at(i) <= '9'){
                number += str.at(i);
            }else{
                if(str.at(i)!=' ')  throw std::invalid_argument(("invalid argument: "+str));
            }
            i++;
        }
        while(i<str.length() && str.at(i)!=']'){
            //if(str.at(i) != ' '){
                unit += str.at(i);
           // }
            i++;
        }
        cout << str << endl;
        while(i < str.length()) { if(str.at(i)!=' ') throw std::invalid_argument(("to many argument: "+str)); }
        
        stringstream s(number);
        s >> num.number;

        num.unit = unit+"";
        */
        return in;
    }
    
    NumberWithUnits operator *(double num1, NumberWithUnits num2){
        return num2.operator*(num1);
    }
}