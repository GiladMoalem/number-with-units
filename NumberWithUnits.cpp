#include "NumberWithUnits.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <ostream>
#include <cmath>
#include <list>
typedef map<string,map<string,double>> Map;

namespace ariel{
    static const double EPS = 0.001; 
    static Map compare_map;
void print();

    

static void func_for_fill_the_deep_map( map<string,double>& main_map, Map& map1, string word){
    map<string,double>::iterator itr;
    for (itr = map1[word].begin(); itr != map1[word].end(); itr++)
    {
        if(true||main_map.find(itr->first) == main_map.end() ){//if the neighbor not in the new map
            main_map[itr->first] = (itr->second) * (main_map[word]);
            //main_map["cm"] = map1["m"]["cm"](100) * main_map["m"](1000)
            func_for_fill_the_deep_map(main_map, map1, itr->first);
        }
    }
}/*
static void ezer2(Map& map1,Map& map2){
    Map::iterator itr1;
    map<string,double>::iterator itr2;
    for(itr1 =map1.begin(); itr1!=map1.end(); itr1++){
        map<string,bool> child;
        map<string,bool> father;
        LinkedList<string> wait;

        for(itr2 = itr1->second.begin(); itr2 != itr1->second.end(); itr2++){
            compare_map[itr1->first][itr2->first]= itr2-> second;
            wait.insert((itr2->first));
        }
    }

}*/
static void ezer(Map& map1,Map& map2){
    
    // Map result;
    Map::iterator itr1,start_itr;
    map<string,double>::iterator itr2;
    // map["km"]["km"] = 1.
    for (start_itr = map1.begin(); start_itr != map1.end(); start_itr++){//"kg" <"kg",1>
        compare_map[start_itr ->first][start_itr ->first] =1.0;
    }
    for (start_itr = map2.begin(); start_itr != map2.end(); start_itr++){//"kg" <"kg",1>
        compare_map[start_itr ->first][start_itr ->first] =1.0;
    }
    

    for (itr1 = map1.begin(); itr1 != map1.end(); itr1++){
        for(itr2 = map1[itr1 ->first].begin(); itr2 != map1[itr1 -> first].end(); itr2++ ){//for the deep map
            string word1 = itr1 -> first, word2 = itr2 -> first;
            compare_map[itr1 -> first][itr2 ->first] = itr2 -> second; // "km",(<"m",1000>,<"cm",100000>)
            // gets map, map(map), string key
            // insert to the map the all friends with the string key
            // and does that again recirsivly 
            func_for_fill_the_deep_map(compare_map[itr1 ->first], map1, word2);
            func_for_fill_the_deep_map(compare_map[itr1 ->first], map2, word2);
        }
        // gets map, map(map), string key
        // insert to the map the values mmap
        // and does that recursivly
        func_for_fill_the_deep_map(compare_map[itr1->first], map2, itr1->first);

    }

    for (itr1 = map2.begin(); itr1 != map2.end(); itr1++){
        for(itr2 = map2[itr1 ->first].begin(); itr2 != map2[itr1 -> first].end(); itr2++ ){//for the deep map
            string word1 = itr1 -> first, word2 = itr2 -> first;
            compare_map[itr1 -> first][itr2 ->first] = itr2 -> second; // "km",(<"m",1000>,<"cm",100000>)
            // gets map, map(map), string key
            // insert to the map the all friends with the string key
            // and does that again recirsivly 
            func_for_fill_the_deep_map(compare_map[itr1 ->first], map1, word2);
        }
        // gets map, map(map), string key
        // insert to the map the values mmap
        // and does that recursivly
        func_for_fill_the_deep_map(compare_map[itr1->first], map2, itr1->first);
    }


    
    
}


    NumberWithUnits::NumberWithUnits(double num, string unit){
        if(compare_map.find(unit)==compare_map.end()) throw invalid_argument("the unit is not in the file units");
        number = num;
        this-> unit = unit;
    }

     void NumberWithUnits::read_units(ifstream& units_file){
        // compare_map.clear();
        map <string,map <string,double>> sizes;
        map <string,map <string,double>> sizes_rev;
        
        string word1,word2;
        double n1,n2;
        char c;
        while(units_file >>n1 >> word1>> c >>n2 >> word2){
            sizes[word1][word2] = n2;
            sizes_rev[word2][word1] = 1/n2;
        }
        ezer(sizes,sizes_rev);
print();
cout<<endl<<endl;

     }
    
    NumberWithUnits NumberWithUnits::operator +(const NumberWithUnits num){
        if(compare_map[this->unit][num.unit]== 0)throw invalid_argument("the two numbers not comparable");
        NumberWithUnits ans( (number + ( num.number/  compare_map[unit][num.unit] )), unit );
        return ans;
        }
    //posetive
    NumberWithUnits NumberWithUnits::operator +() {
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator +=(const NumberWithUnits num){ 
        if(compare_map[this->unit][num.unit]== 0)throw invalid_argument("the two numbers not comparable");
        number = number +(num.number/compare_map[unit][num.unit]);
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator -(const NumberWithUnits num){
        if(compare_map[this->unit][num.unit]== 0)throw invalid_argument("the two numbers not comparable");
        NumberWithUnits ans( (number - ( num.number/  compare_map[unit][num.unit] )), unit );
        return ans;
        }
//negative
    NumberWithUnits NumberWithUnits::operator -(){
        NumberWithUnits neg = *this;
        neg.number *= (-1);
        return neg;
    }
    NumberWithUnits NumberWithUnits::operator -=(const NumberWithUnits num){
        if(compare_map[this->unit][num.unit]== 0)throw invalid_argument("the two numbers not comparable");
        number = number -(num.number/compare_map[unit][num.unit]);
        return *this;
    }
/*
    bool NumberWithUnits::operator ==(const NumberWithUnits num){
        return number == (num.number / compare_map[unit][num.unit]);
    }
    bool NumberWithUnits::operator >=(const NumberWithUnits num){
        return number >= num.number / compare_map[unit][num.unit];}
    bool NumberWithUnits::operator >(const NumberWithUnits num){
        return number > num.number / compare_map[unit][num.unit];}

    bool NumberWithUnits::operator <(const NumberWithUnits num){
        return number < num.number / compare_map[unit][num.unit];}
    bool NumberWithUnits::operator <=(const NumberWithUnits num){
        return number <= num.number / compare_map[unit][num.unit];}
    bool NumberWithUnits::operator !=(const NumberWithUnits num){
        return number != num.number / compare_map[unit][num.unit];
    }
*/
    bool operator ==(const NumberWithUnits num1,const NumberWithUnits num2){
        if(!compare(num1,num2,0)) throw invalid_argument("this units uncomparable");
        double dist = compare(num1, num2);
        return abs(dist) < EPS;
    }
    bool operator >=(const NumberWithUnits num1,const NumberWithUnits num2){
        return (num1 == num2) || num1.number > (num2.number / compare_map[num1.unit][num2.unit]);
    }
    bool operator >(const NumberWithUnits num1,const NumberWithUnits num2){
        return !(num1==num2) && num1.number > (num2.number / compare_map[num1.unit][num2.unit]);
    }
    bool operator <(const NumberWithUnits num1,const NumberWithUnits num2){
        return !(num1==num2) && num1.number < (num2.number / compare_map[num1.unit][num2.unit]);
    }
    bool operator <=(const NumberWithUnits num1,const NumberWithUnits num2){
        return (num1 == num2) || num1.number <= (num2.number / compare_map[num1.unit][num2.unit]);
    }
    bool operator !=(const NumberWithUnits num1,const NumberWithUnits num2){
        return !(num1 == num2);
    }
    
// ++num
    NumberWithUnits& NumberWithUnits::operator ++(){
        ++(this->number);
        cout<<endl;
        return *this;
    }  
// num++
    NumberWithUnits NumberWithUnits::operator ++(int){
        NumberWithUnits old = *this;
        // this->number++;
        return NumberWithUnits(this->number++,this->unit);
    } 
    NumberWithUnits& NumberWithUnits::operator --(){
        this->number--;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator --(int){
        NumberWithUnits old = *this;
        this->number--;
        return old;
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
        if(compare_map.find(unit)==compare_map.end())throw invalid_argument("shuld be a unit");

        // if(in >> str) throw invalid_argument("overmuch arguments: after the ']' should be not argument! but -> "+str);
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
    
    bool compare(const NumberWithUnits num1,const NumberWithUnits num2,int){
        // cout << num1 << " "<<num2<<" "<< compare_map[num1.unit][num2.unit]<<endl;
        return compare_map[num1.unit][num2.unit] != 0; 
    }
    double compare(const NumberWithUnits num1,const NumberWithUnits num2){
        return (num1.number - (num2.number/compare_map[num1.unit][num2.unit] ));
    }
}