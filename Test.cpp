#include "doctest.h"
#include <istream>

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "NumberWithUnits.hpp"
using namespace ariel;


TEST_CASE("try"){
ifstream units_file{"units.txt"};
NumberWithUnits::read_units(units_file);

    NumberWithUnits a{2, "km"}; 
    CHECK((a.operator==(a)));
    CHECK(!(a*3).operator==(a));
}


TEST_CASE("equals length"){
    NumberWithUnits a{2, "km"}; 
    NumberWithUnits b{20, "m"}; 
    CHECK((a == NumberWithUnits{2, "km"}));
    CHECK((a == NumberWithUnits{2000, "m"}));
    CHECK((a == NumberWithUnits{200000, "cm"}));

    CHECK((a != NumberWithUnits{1000, "m"}));
    CHECK((a != NumberWithUnits{200, "km"}));
    CHECK((a != NumberWithUnits{20, "cm"}));
    
    CHECK(( (a+b) == NumberWithUnits{2020, "m"}));
    CHECK(((a+b) == NumberWithUnits{2.02, "km"}));
} 

TEST_CASE("equals weight"){
    NumberWithUnits a{2, "kg"}; 
    NumberWithUnits b{20, "g"}; 
    CHECK((a == NumberWithUnits{2, "kg"}));
    CHECK((a == NumberWithUnits{2000, "g"}));
    CHECK((a*100 == NumberWithUnits{200000, "g"}));
    CHECK((100*a == NumberWithUnits{200000, "g"}));

    CHECK((a != NumberWithUnits{1000, "g"}));
    CHECK((a != NumberWithUnits{200, "kg"}));
    CHECK((a != NumberWithUnits{20, "ton"}));
    
    CHECK(( (a+b) == NumberWithUnits{2020, "g"}));
    CHECK(((a+b) == NumberWithUnits{2.02, "kg"}));
} 
TEST_CASE("comperetions"){
    NumberWithUnits a{2, "km"}; 
    NumberWithUnits b{20, "m"}; 
    // NumberWithUnits ton{1, "ton"}; 

    CHECK((a>b));
    CHECK((a>=b));
    CHECK((b<a));
    CHECK((b<a));
    CHECK(((b+NumberWithUnits{1,"km"}) <= a));
}

TEST_CASE("input"){
    
    stringstream iss {"700 [kg]"};
    NumberWithUnits a{2,""};
    CHECK_NOTHROW (iss >> a);
    CHECK((a == NumberWithUnits{700,"kg"} ));

    stringstream is2 {"sds700 [kg]"};
    CHECK_THROWS(is2 >> a); 
    
    stringstream is3 {"700 kg]"};
    CHECK_THROWS(is3 >> a); 

    stringstream is4{"700 [kg"} ;
    CHECK_THROWS(is4 >> a); 

    stringstream is5{"700 []"} ;
    CHECK_THROWS(is5 >> a); 
    // cout << iss.str();


/*
    cout << iss.str() <<endl;
    iss<<"str()";
    cout << iss.str() << " 1"<<endl;

    iss.str("3 [g]");
    NumberWithUnits e{4,"gf"};
    iss >> e;
    cout << iss.str() << e << " 2" <<endl;
    stringstream().swap(iss);
    iss<<"swap";
    cout << iss.str() << " 3" <<endl;
*/

}
