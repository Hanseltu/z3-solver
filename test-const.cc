#include "z3++.h"
using namespace z3;

int main(){
    context c;
    expr zz = c.bv_const("zz", 16);
    expr const_test1 = c.bv_val(0x8000000, 32);
    expr zeroext = zext(zz, 32);
    std::cout << "zeroext : " << zeroext << std::endl;
    //expr and_test = zeroext & const_test1; // not work
    expr and_test = zeroext & 0x8000000; // works well
    std::cout << "and_test : " << and_test<< std::endl;
    return 0;
}
