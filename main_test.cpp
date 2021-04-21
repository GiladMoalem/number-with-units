//main_test.cpp
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"


int main(){
    doctest::Context context;
    context.addFilter("reporters","console");
    context.run();
    
    return 0;
}