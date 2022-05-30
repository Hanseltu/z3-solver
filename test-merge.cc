#include "Expr.h"
#include "Z3Handler.h"
#include <map>

using namespace z3;
using namespace EXPR;
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
    ExprPtr add_expr = std::make_shared<AddExpr>(const_expr, const_expr);
    expr ret_add =  z3_handler->Z3HandleAdd(const_expr, const_expr);
    std::cout << "ret_add : " << ret_add << std::endl;
    //expr con = ret_udef == ret_add;

    //testing Sge
    ExprPtr sge_expr = std::make_shared<SgeExpr>(add_expr);
    SgeExpr * sge = static_cast<SgeExpr*>(sge_expr.get());

    std::cout << "+++ Original Expression: " ;
    sge->print();
    std::cout << "\n";

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
    std::cout << "+++ Original Expression: \n" ;
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
    std::cout << "+++ Original Expression: \n" ;
    equal->print();
    std::cout << "\n";

    // Merging from here; assuming we have got an constraint (ExprPtr), 'equal_expr' in this code
    Z3Handler *z3_handler_test = new Z3Handler();
    expr ret_solver = z3_handler_test->Z3HandlingExprPtr(equal_expr);
    g_solver.add(ret_solver);
    if (g_solver.check() == unsat){
        std::cout << "The constraints is unsolveable -:)" << std::endl;
    }
    model m = g_solver.get_model();
    std::map<std::string, unsigned long long> ret_result;
    ret_result = z3_handler_test->Z3SolveOne(m); // now the [symbolic name, concrete value] map will be returned
    for (auto it = ret_result.begin(); it != ret_result.end(); it ++){
        std::cout << "symbol : " << it->first << "   value : " << it->second << std::endl;
    }
}


int main(){
    test();
    return 0;
}
