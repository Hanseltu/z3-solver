#include<vector>
#include"z3++.h"

#include "Expr.h"
#include "Z3Handler.h"

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
    s.add(x == 100 and x < 1);
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

using namespace Z3HANDLER;


z3::context g_z3_context;
z3::solver g_solver(g_z3_context);


void test(){
    // create a symbolic object
    SYMemObject *obj = new SYMemObject;
    obj->name = "niceval";
    obj->size = 8;
    UDefExpr *sym_expr = new UDefExpr(obj);
    // Z3HandleUND(sym)
    Z3Handler *z3_handler = new Z3Handler();


    // testing UDefExpr
    ExprPtr udef_expr = std::make_shared<UDefExpr>(obj);
    expr ret_udef = z3_handler->Z3HandleUND(udef_expr);
    std::cout << "ret_udef : " << ret_udef << std::endl;

    //testing Const
    ExprPtr const_expr = std::make_shared<ConstExpr>(0x01);
    expr ret_const = z3_handler->Z3HandleConst(const_expr);
    std::cout << "ret_const : " << ret_const << std::endl;

    //testing Add
    /*
    ExprPtr add_expr = std::make_shared<AddExpr>(const_expr, udef_expr);
    expr ret_add =  z3_handler->Z3HandleAdd(const_expr, udef_expr);
    std::cout << "ret_add : " << ret_add << std::endl;
    //expr con = ret_udef == ret_add;

    //testing Sge
    ExprPtr sge_expr = std::make_shared<SgeExpr>(add_expr);
    SgeExpr * sge = static_cast<SgeExpr*>(sge_expr.get());

    std::cout << "+++ Original Expression: " ;
    sge->print();
    std::cout << "\n";
    */
    // testing LNot(Ugt(Sub(0x2, Extract(Combine(0x, which_rdi), 0, 4)))
    ExprPtr const_expr1 = std::make_shared<ConstExpr>(0x0);
    ExprPtr const_expr2 = std::make_shared<ConstExpr>(0x2);
    CombineExpr *combine = new CombineExpr(const_expr1, udef_expr, 0, 0);
    ExprPtr combine_expr = std::make_shared<CombineExpr>(udef_expr, const_expr1, 0, 0);
    ExprPtr extract_expr = std::make_shared<ExtractExpr>(combine_expr, 0, 4);
    ExprPtr sub_expr = std::make_shared<SubExpr>(extract_expr, const_expr2);
    ExprPtr ugt_expr = std::make_shared<UgtExpr>(sub_expr);
    ExprPtr lnot_expr = std::make_shared<LNotExpr>(ugt_expr);
    LNotExpr *lnot = static_cast<LNotExpr*>(lnot_expr.get());
    std::cout << "+++ Original Expression: " ;
    lnot->print();
    std::cout << "\n";
    expr ret_combine = z3_handler->Z3HandleCombine(udef_expr, const_expr1);
    expr ret_extract = z3_handler->Z3HandleExtract(extract_expr);
    std::cout << "ret_extract length : " << ret_extract.get_sort() << std::endl;
    expr ret_sub = z3_handler->Z3HandleSub(extract_expr, const_expr2);
    //expr ret_solver = z3_handler->Z3HandlingExprPtr(lnot_expr);

    // testing Equal(And(Extract(Combine(0x, which_rdi), 0, 4), Extract(Combine(0x0, which_rdi), 0, 4)))
    ExprPtr and_expr = std::make_shared<AndExpr>(extract_expr, extract_expr);
    ExprPtr equal_expr = std::make_shared<EqualExpr>(and_expr);
    EqualExpr *equal = static_cast<EqualExpr*>(equal_expr.get());
    std::cout << "+++ Original Expression: " ;
    equal->print();
    std::cout << "\n";
    expr ret_solver = z3_handler->Z3HandlingExprPtr(equal_expr);
    g_solver.add(ret_solver);
    // testing handlingExprPtr
    //expr ret_expr_ptr = z3_handler->Z3HandlingExprPtr(udef_expr);
    //delete obj;
}

int main(){
    //demorgan();
    //find_model_example1();
    //bitvector_example1();
    //bitvector_example2();
    //bitvector_example();
    test();
    // traversing the model
    std::cout << "g_solver : " << g_solver.check() << g_solver << std::endl;
    model m = g_solver.get_model();
    Z3Handler *z3_handler = new Z3Handler();
    std::map<std::string, unsigned long long> ret;
    ret = z3_handler->Z3SolveOne(m);
    std::cout << "### solver results: " << "\n";
    //std::map<std::string, unsigned long long>::iterator it;
    for (auto it = ret.begin(); it != ret.end(); it ++){
        std::cout << "symbol : " << it->first << "   value : " << it->second << std::endl;
    }
    /*
    for (unsigned i = 0; i < m.size(); i++) {
        func_decl v = m[i];
        // this problem contains only constants
        assert(v.arity() == 0);
        std::cout << v.name() << " = " << m.get_const_interp(v) << "\n";
    }
    */
    /*
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
    */
    return 0;
}
