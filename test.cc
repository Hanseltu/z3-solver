#include<vector>
#include"z3++.h"

#include "Expr.h"


#include <map>

using namespace z3;
using namespace EXPR;

void demorgan() {
    std::cout << "de-Morgan example\n";

    context c;

    expr x = c.bool_const("x");
    expr y = c.bool_const("y");
    expr conjecture = (!(x && y)) == (!x || !y);

    solver s(c);
    // adding the negation of the conjecture as a constraint.
    s.add(!conjecture);
    std::cout << "s: "  << s << "\n";
    std::cout << "stm_lib2: " << s.to_smt2() << "\n";
    switch (s.check()) {
    case unsat:   std::cout << "de-Morgan is valid\n"; break;
    case sat:     std::cout << "de-Morgan is not valid\n"; break;
    case unknown: std::cout << "unknown\n"; break;
    }
}


void find_model_example1() {
    std::cout << "find_model_example1\n";
    context c;
    expr x = c.int_const("x");
    expr y = c.int_const("y");
    solver s(c);

    s.add(x >= 1);
    s.add(y < x + 3);
    std::cout << s.check() << "\n";

    model m = s.get_model();
    std::cout << m << "\n";
    // traversing the model
    for (unsigned i = 0; i < m.size(); i++) {
        func_decl v = m[i];
        // this problem contains only constants
        assert(v.arity() == 0);
        std::cout << v.name() << " = " << m.get_const_interp(v) << "\n";
    }
    // we can evaluate expressions in the model.
    std::cout << "x + y + 1 = " << m.eval(x + y + 1) << "\n";
}


//brief Simple function that tries to prove the given conjecture using the following steps:
// 1- create a solver
// 2- assert the negation of the conjecture
// 3- checks if the result is unsat.
void prove(expr conjecture) {
    context & c = conjecture.ctx();
    solver s(c);
    s.add(!conjecture);
    std::cout << "conjecture:\n" << conjecture << "\n";
    if (s.check() == unsat) {
        std::cout << "proved" << "\n";
    }
    else {
        std::cout << "failed to prove" << "\n";
        std::cout << "counterexample:\n" << s.get_model() << "\n";
    }
}


//brief Simple bit-vector example. This example disproves that x - 10 <= 0 IFF x <= 10 for (32-bit) machine integers
void bitvector_example1() {
    std::cout << "bitvector example 1\n";
    context c;
    expr x = c.bv_const("x", 32);

    // using signed <=
    prove((x - 10 <= 0) == (x <= 10));

    // using unsigned <=
    prove(ule(x - 10, 0) == ule(x, 10));

    expr y = c.bv_const("y", 32);
    prove(implies(concat(x, y) == concat(y, x), x == y));
}


//brief Find x and y such that: x ^ y - 103 == x * y
void bitvector_example2() {
    std::cout << "bitvector example 2\n";
    context c;
    expr x = c.bv_const("x", 32);
    expr y = c.bv_const("y", 32);
    solver s(c);
    // In C++, the operator == has higher precedence than ^.
    s.add((x ^ y) - 103 == x * y);
    std::cout << s << "\n";
    std::cout << s.check() << "\n";
    std::cout << s.get_model() << "\n";
}


void bitvector_example(){
    context c;
    expr x = c.bv_const("x", 64);
    solver s(c);
    s.add(x == 100);
    std::cout << "s : " << s << std::endl;
    std::cout << "stm_lib2: " << s.to_smt2() << std::endl;
    std::cout << "sat? : " << s.check() << std::endl;
    std::cout << "model： " << s.get_model() << std::endl;
}

std::map<std::string, unsigned long long> ret_map; //TODO is the unsigned long long ok here?

std::map<std::string, unsigned long long> se_solver(ExprPtr expr){
    // 1. get symbolic variable name
    // 2. traverse the experssion, and build expr recongnized in z3
    std::map<std::string, unsigned long long> ret;

    // first round traverse to find the symbolic variables
    std::vector<std::string> sym_names;


    // second round to build the z3 expr
    //

    // get results from solver


    return ret;

}


int main(){
    //demorgan();
    //find_model_example1();
    //bitvector_example1();
    //bitvector_example2();
    //bitvector_example();
    SYMemObject *obj = new SYMemObject;
    obj->name = "niceval";
    UDefExpr sym = new UDefExpr(obj);
    //Expr *exprptr = new Expr(8, 0);
    ExprPtr sptr = std::make_shared<UDefExpr>(obj);
    ExtractExpr *ext = new ExtractExpr(sptr, 0, 4);
    //ext->print();
    ExprPtr cons = std::make_shared<ConstExpr>(0x13);
    ExprPtr extptr = std::make_shared<ExtractExpr>(sptr, 0, 4);
    SubExpr *subexpr = new SubExpr(extptr, cons);
    //subexpr->print();
    SgeExpr *sge = new SgeExpr(std::make_shared<SubExpr>(extptr, cons));
    std::cout << "### The constraints to be passed into solver : " << std::endl;
    sge->print();
    std::cout << "\nKind Sge : " << sge->getKind() << std::endl;
    std::cout << "\n\n";

    // using solver
    std::cout << "### solver information : " << std::endl;
    context c;
    expr x = c.bv_const("niceval", 64);
    x = x + 1;
    x.extract(4, 0);
    solver s(c);
    s.add(x - 19 >= 0);
    std::cout << "s : " << s << std::endl;
    std::cout << "stm_lib2: " << s.to_smt2() << std::endl;
    std::cout << "sat? : " << s.check() << std::endl;
    model m = s.get_model();
    std::cout << m << "\n";
    // traversing the model
    std::cout << "### solver results: " << "\n";
    for (unsigned i = 0; i < m.size(); i++) {
        func_decl v = m[i];
        // this problem contains only constants
        assert(v.arity() == 0);
        std::cout << v.name() << " = " << m.get_const_interp(v) << "\n";
    }
    return 0;
}
