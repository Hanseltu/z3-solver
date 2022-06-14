#include "Z3Handler.h"
#include "z3++.h"
using namespace z3;
using namespace EXPR;

void test(){
    // create a symbolic object
    VMState::SYMemObject *obj = new VMState::SYMemObject;
    VMState::SYMemObject *obj1 = new VMState::SYMemObject;
    obj->name = "niceval";
    obj->size = 4;
    UDefExpr *sym_expr = new UDefExpr(obj);
    // Z3HandleUND(sym)
    Z3HANDLER::Z3Handler *z3_handler = new Z3HANDLER::Z3Handler();


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
    ExprPtr sge_expr = std::make_shared<SgeExpr>(add_expr, const_expr);
    SgeExpr * sge = static_cast<SgeExpr*>(sge_expr.get());

    std::cout << "+++ Original Expression: " ;
    //sge->print();
    std::cout << "\n";

    // testing LNot(Ugt(Sub(0x2, Extract(Combine(0x, which_rdi), 0, 4)))
    ExprPtr const_expr1 = std::make_shared<ConstExpr>(0x0);
    ExprPtr const_expr2 = std::make_shared<ConstExpr>(0x2);
    ExprPtr const_expr3 = std::make_shared<ConstExpr>(0x1);
    CombineExpr *combine = new CombineExpr(const_expr1, udef_expr, 0, 0);
    ExprPtr combine_expr = std::make_shared<CombineExpr>(udef_expr, const_expr1, 0, 0);
    ExprPtr extract_expr = std::make_shared<ExtractExpr>(combine_expr, 0, 4);
    ExprPtr sub_expr = std::make_shared<SubExpr>(const_expr2, extract_expr);
    ExprPtr sub_expr1 = std::make_shared<SubExpr>(const_expr3, extract_expr);
    //ExprPtr sub_expr = std::make_shared<SubExpr>(extract_expr, const_expr1);
    ExprPtr ugt_expr = std::make_shared<UgtExpr>(extract_expr, const_expr2);
    //ExprPtr ugt_expr = std::make_shared<UgtExpr>(const_expr2, extract_expr);
    ExprPtr lnot_expr = std::make_shared<LNotExpr>(ugt_expr);
    LNotExpr *lnot = static_cast<LNotExpr*>(lnot_expr.get());
    UgtExpr *ugt = static_cast<UgtExpr*>(ugt_expr.get());
    std::cout << "+++ Original Expression: \n" ;
    //lnot->print();
    ugt->print();
    std::cout << "\n";
    expr ret_combine = z3_handler->Z3HandleCombine(udef_expr, const_expr1);
    expr ret_extract = z3_handler->Z3HandleExtract(extract_expr);
    //std::cout << "ret_extract length : " << ret_extract.get_sort() << std::endl;
    expr ret_sub = z3_handler->Z3HandleSub(extract_expr, const_expr2);
    //expr ret_solver = z3_handler->Z3HandlingExprPtr(lnot_expr);

    // testing Equal(And(Extract(Combine(0x, which_rdi), 0, 4), Extract(Combine(0x0, which_rdi), 0, 4)))
    ExprPtr and_expr = std::make_shared<AndExpr>(extract_expr, extract_expr);
    ExprPtr equal_expr = std::make_shared<EqualExpr>(and_expr);
    ExprPtr equal_expr1 = std::make_shared<EqualExpr>(sub_expr1);
    EqualExpr *equal = static_cast<EqualExpr*>(equal_expr.get());
    //std::cout << "+++ Original Expression: \n" ;
    //equal->print();
    std::cout << "\n";
    //g_solver.reset();
    ExprPtr lnot_expr1 = std::make_shared<LNotExpr>(equal_expr1);
    ExprPtr lnot_expr2 = std::make_shared<LNotExpr>(equal_expr1);
    LNotExpr *lnot1 = static_cast<LNotExpr*>(lnot_expr1.get());
    LNotExpr *lnot2 = static_cast<LNotExpr*>(lnot_expr2.get());
    //lnot1->print();
    std::cout << "\n";
    //lnot2->print();
    //std::cout << "\n";

    // Merging from here; assuming we have got the constraints (defined in std::set<KVExprPtr>), 'constraints_test' in this code
    std::set<KVExprPtr> constraints_test;
    //constraints_test.insert(equal_expr1);
    //constraints_test.insert(lnot_expr1);
    //constraints_test.insert(lnot_expr2);

    constraints_test.insert(ugt_expr);
    //constraints_test.insert(lnot_expr);

    Z3HANDLER::Z3Handler *z3_handler_test = new Z3HANDLER::Z3Handler();
    std::map<std::string, unsigned long long> ret_result;
    ret_result = z3_handler_test->Z3SolveOne(constraints_test); // now the [symbolic name, concrete value] map will be returned
    for (auto it = ret_result.begin(); it != ret_result.end(); it ++){
        std::cout << "symbol : " << it->first << std::endl;
        printf("value : %llu(dec) %x(hex) \n", it->second, (unsigned int) it->second);
    }

    // testing concritize function
    // 'obj' is a symbolic object defined with SYMemObject*, 'value' is the concrete value; 'constraints_test' is a set of constraints
    std::vector<VMState::SYMemObject*> symobjts;
    obj->i32 = 100;
    symobjts.push_back(obj);
    obj->i32 = 200;
    symobjts.push_back(obj);
    //symobjts.push_back(obj); // testing a symbolic object which is not in the constraints
    //values.push_back(1000);
    bool ret_con = z3_handler_test->Z3SolveConcritize(symobjts, constraints_test);
    std::cout << "result of concritize : " << ret_con << std::endl;
}
void eval_example1() {
    std::cout << "eval example 1\n";
    context c;
    expr x = c.int_const("x");
    expr y = c.int_const("y");
    solver s(c);

    /* assert x < y */
    s.add(x < y);
    /* assert x > 2 */
    s.add(x > 2);

    std::cout << s.check() << "\n";

    model m = s.get_model();
    std::cout << "Model:\n" << m << "\n";
    std::cout << "x+y = " << m.eval(x+y) << "\n";
}

int main(){
    test();
    //eval_example1();
    /*
    context c;
    expr x1 = c.bv_const("x", 8);
    expr x2 = c.bv_const("x", 24);
    expr x3 = c.bv_const("x", 32);
    expr x = concat(concat(x1, x2), x3);
    solver s(c);
    expr zz = ugt(x, 2);
    s.add(zz);
    std::cout << "solver : " << s  << s.check() << std::endl;
    std::cout << s.to_smt2() << std::endl;
    std::cout << "checking done ... " << std::endl;
    model m = s.get_model();
    std::cout << m << "\n";
    // traversing the model
    for (unsigned i = 0; i < m.size(); i++) {
        func_decl v = m[i];
        // this problem contains only constants
        assert(v.arity() == 0);
        std::cout << v.name() << " = " << m.get_const_interp(v) << "\n";
    }
    */
    return 0;
}
