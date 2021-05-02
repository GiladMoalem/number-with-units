#include "NumberWithUnits.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <ostream>
#include <cmath>
#include <stack>
#include <set>
typedef map<string,map<string,double>> Map;

namespace ariel{
    static const double EPS = 0.001; 
    static Map compare_map;
void print();


static double ezer2(string src, string dest){
    set<string> visited;
    compare_map[src][src] = 1;
    if(src==dest) return 1;
    visited.insert(src);

    stack<string> wait;
    wait.push(src);
    string word = src;
    
    while(!wait.empty()){
        word = wait.top();
        wait.pop();
        
        for(auto& n:compare_map[word]){
            if(visited.find(n.first) == visited.end()){
                
                compare_map[src][n.first] = compare_map[src][word] * compare_map[word][n.first];
                compare_map[n.first][src] = 1 / compare_map[src][n.first];
                
                if(n.first == dest)return compare_map[src][n.first];

                wait.push(n.first);
                visited.insert(n.first);
            }
        }
    }
    return -1;
    }



    NumberWithUnits::NumberWithUnits(double num, string unit){
        if(compare_map.find(unit)==compare_map.end()) throw invalid_argument("the unit is not in the file units");
        number = num;
        this-> unit = unit;
    }

     void NumberWithUnits::read_units(ifstream& units_file){
        // compare_map.clear();
        
        
        string word1,word2;
        double n1,n2;
        char c;
        while(units_file >>n1 >> word1>> c >>n2 >> word2){
            compare_map[word1][word1] = 1;
            compare_map[word2][word2] = 1;
            compare_map[word1][word2] = 1/n2;
            compare_map[word2][word1] = n2;
        }
// print();
// cout<<endl<<endl;

     }
    
    NumberWithUnits NumberWithUnits::operator +(const NumberWithUnits num){
        if(ezer2(unit,num.unit)<0)throw invalid_argument("the two numbers not comparable");
        NumberWithUnits ans( (number + ( num.number * compare_map[unit][num.unit] )), unit );
        return ans;
        }
    //posetive
    NumberWithUnits NumberWithUnits::operator +() {
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator +=(const NumberWithUnits num){ 
        if(ezer2(unit,num.unit)<0)throw invalid_argument("the two numbers not comparable");
        number = number +(num.number*compare_map[unit][num.unit]);
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator -(const NumberWithUnits num){
        if(ezer2(unit,num.unit)<0)throw invalid_argument("the two numbers not comparable");
        NumberWithUnits ans( (number - ( num.number * compare_map[unit][num.unit] )), unit );
        return ans;
        }
//negative
    NumberWithUnits NumberWithUnits::operator -(){
        NumberWithUnits neg = *this;
        neg.number *= (-1);
        return neg;
    }
    NumberWithUnits NumberWithUnits::operator -=(const NumberWithUnits num){
        if(ezer2(unit,num.unit)<0) throw invalid_argument("the two numbers not comparable");
        number = number -(num.number*compare_map[unit][num.unit]);
        return *this;
    }

    bool operator ==(const NumberWithUnits num1,const NumberWithUnits num2){
        if( ezer2(num1.unit, num2.unit)<0 ) throw invalid_argument("this units uncomparable");
        double dist = num1.number - num2.number * compare_map[num1.unit][num2.unit];
        return abs(dist) < EPS;
    }
    bool operator >=(const NumberWithUnits num1,const NumberWithUnits num2){
        return num1 > num2 || num1 == num2;
    }
    bool operator >(const NumberWithUnits num1,const NumberWithUnits num2){
        return !(num1==num2) && num1.number > (num2.number * compare_map[num1.unit][num2.unit]);
    }
    bool operator <(const NumberWithUnits num1,const NumberWithUnits num2){
        return !(num1 >= num2);
    }
    bool operator <=(const NumberWithUnits num1,const NumberWithUnits num2){
        return num1 < num2 || num1 == num2;
    }
    bool operator !=(const NumberWithUnits num1,const NumberWithUnits num2){
        return !(num1 == num2);
    }
    
// ++num
    NumberWithUnits& NumberWithUnits::operator ++(){
        ++(this->number);
        return *this;
    }  
// num++
    NumberWithUnits NumberWithUnits::operator ++(int){
        return NumberWithUnits(this->number++,this->unit);
    } 
    NumberWithUnits& NumberWithUnits::operator --(){
        this->number--;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator --(int){
        return NumberWithUnits(this->number--, this->unit);
        }

    NumberWithUnits NumberWithUnits::operator *(const double num){//is that true?
        NumberWithUnits res = *this;
        res.number *= num;
        return res;
        }

    ostream& operator <<(ostream& os, NumberWithUnits num){
        os << num.number<<'['<< num.unit << ']';
        return os;
    }

    
    istream& operator >>(istream& in, NumberWithUnits& num){
        string str,unit;
        char c;
        double number;
       
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
        if(compare_map.find(unit) == compare_map.end()) throw invalid_argument("shuld be a unit");
        // if(in >> str) throw invalid_argument("overmuch arguments: after the ']' should be not argument! but -> "+str);
        num.number = number;
        num.unit = unit;
  
        return in;
    }
    
    NumberWithUnits operator *(double num1, NumberWithUnits num2){
        return num2.operator*(num1);
    }

    // prints
    void print(){
        map <string, map<string,double>>::iterator itr1;
    map <string,double>::iterator deep_itr;
    for (itr1 = compare_map.begin(); itr1 != compare_map.end(); itr1++)
    {
        cout << itr1->first;
        for (deep_itr = compare_map[itr1->first].begin(); deep_itr != compare_map[itr1->first].end(); deep_itr++)
        {
            std::cout << " <" <<deep_itr->first << ','<<deep_itr->second << "> ";
        }
        cout<<endl;
    }
    }

}