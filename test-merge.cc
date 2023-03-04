#include "Z3Handler.h"
#include "z3++.h"
using namespace z3;
using namespace EXPR;

static __attribute__ ((noinline)) unsigned long long rdtsc(void){
    unsigned hi, lo;
    asm volatile ("rdtsc" : "=a"(lo), "=d"(hi));
    return ((unsigned long long) lo | ((unsigned long long) hi << 32));
}

void test(){
    // create a symbolic object
    VMState::SYMemObject *obj = new VMState::SYMemObject;
    VMState::SYMemObject *obj1 = new VMState::SYMemObject;
    obj1->size = 4;
    obj->has_seed = 1;
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
    ExprPtr const_expr = std::make_shared<ConstExpr>(0xffffffffffff1ffe);
    expr ret_const = z3_handler->Z3HandleConst(const_expr);
    std::cout << "ret_const : " << ret_const << std::endl;
    //testing Add
    ExprPtr add_expr = std::make_shared<AddExpr>(udef_expr, const_expr);
    expr ret_add =  z3_handler->Z3HandleAdd(const_expr, const_expr);
    std::cout << "ret_add : " << ret_add << std::endl;
    //expr con = ret_udef == ret_add;

    // testing LNot(Ugt(Sub(0x2, Extract(Combine(0x, which_rdi), 0, 4)))
    ExprPtr const_expr1 = std::make_shared<ConstExpr>(0x0);
    ExprPtr const_expr2 = std::make_shared<ConstExpr>(0x2);
    ExprPtr const_expr3 = std::make_shared<ConstExpr>(0x10);
    CombineExpr *combine = new CombineExpr(const_expr1, udef_expr, 0, 0);
    ExprPtr combine_expr = std::make_shared<CombineExpr>(udef_expr, const_expr1, 0, 0);
    ExprPtr extract_expr = std::make_shared<ExtractExpr>(udef_expr, 0, 4);
    ExprPtr signext_expr = std::make_shared<SignExtExpr>(extract_expr);
    //ExprPtr sub_expr = std::make_shared<SubExpr>(const_expr1, extract_expr);
    ExprPtr sub_expr = std::make_shared<SubExpr>(const_expr1, signext_expr);
    ExprPtr equal_expr_test = std::make_shared<EqualExpr>(sub_expr);
    ExprPtr sub_expr1 = std::make_shared<SubExpr>(const_expr3, extract_expr);
    //ExprPtr sub_expr = std::make_shared<SubExpr>(extract_expr, const_expr1);
    ExprPtr ugt_expr = std::make_shared<UgtExpr>(extract_expr, const_expr2);
    //ExprPtr ugt_expr = std::make_shared<UgtExpr>(const_expr2, extract_expr);
    ExprPtr lnot_expr = std::make_shared<LNotExpr>(ugt_expr);
    LNotExpr *lnot = static_cast<LNotExpr*>(lnot_expr.get());
    UgtExpr *ugt = static_cast<UgtExpr*>(ugt_expr.get());
    std::cout << "+++ Original Expression: \n" ;
    //equal_expr_test->print();
    //sub_expr->print();
    //lnot->print();
    //ugt->print();
    std::cout << "\n";

    // test SignExpr/NoSignExpr
    /*
    ExprPtr const_expr00 = std::make_shared<ConstExpr>(0xfffffffffffffffe);
    const_expr00->size = 8;
    ExprPtr const_expr11 = std::make_shared<ConstExpr>(0x2);
    const_expr11->size = 8;
    ExprPtr sign_expr = std::make_shared<SignExpr>(const_expr00);
    expr sign_expr_z3 = z3_handler->Z3HandleSign(sign_expr);
    std:: cout << "sign_expr : " << sign_expr_z3 << std::endl;
    */


    // testing CombineMulti
    /*
    ExprPtr const_expr00 = std::make_shared<ConstExpr>(0x1);
    const_expr00->size = 8;
    ExprPtr const_expr11 = std::make_shared<ConstExpr>(0x1);
    const_expr11->size = 4;
    ExprPtr const_expr22 = std::make_shared<ConstExpr>(0x1);
    const_expr22->size = 1;
    ExprPtr const_expr33 = std::make_shared<ConstExpr>(0x1);
    const_expr33->size = 1;
    ExprPtr const_expr44 = std::make_shared<ConstExpr>(0x1);
    const_expr44->size = 1;
    ExprPtr const_expr55 = std::make_shared<ConstExpr>(0x1);
    const_expr55->size = 1;
    std::vector<ExprPtr> e;
    e.push_back(const_expr11);
    e.push_back(const_expr22);
    e.push_back(const_expr33);
    e.push_back(const_expr44);
    e.push_back(const_expr55);
    std::vector<int> o;
    o.push_back(4);
    o.push_back(2);
    o.push_back(2);
    ExprPtr multicombine_expr = std::make_shared<CombineMultiExpr>(e, o, o);
    multicombine_expr->print();
    ExprPtr ult_expr = std::make_shared<UltExpr>(multicombine_expr, const_expr00);
    expr multicombine_expr_z3 = z3_handler->Z3HandleCombineMulti(e);
    expr const_expr00_z3 = z3_handler->Z3HandleConst(const_expr00);
    expr test_expr = multicombine_expr_z3 - const_expr00_z3;
    std::cout << "test_expr:" << test_expr << std::endl;
    */
    /*
    expr ret_combine = z3_handler->Z3HandleCombine(udef_expr, const_expr1);
    expr ret_extract = z3_handler->Z3HandleExtract(extract_expr);
    //std::cout << "ret_extract length : " << ret_extract.get_sort() << std::endl;
    expr ret_sub = z3_handler->Z3HandleSub(extract_expr, const_expr2);
    //expr ret_solver = z3_handler->Z3HandlingExprPtr(lnot_expr);
    //testing Sge
    ExprPtr sge_expr = std::make_shared<SgeExpr>(extract_expr, const_expr);
    SgeExpr * sge = static_cast<SgeExpr*>(sge_expr.get());
    //std::cout << "+++ Original Expression: " ;
    //sge->print();
    std::cout << "\n";
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
    std::cout << "starting testing --- \n";
    */
    //lnot2->print();
    //std::cout << "\n";
    // Merging from here; assuming we have got the constraints (defined in std::set<KVExprPtr>), 'constraints_test' in this code
    //

    // testing 2022.11.21
    // Sign(And(sym, sym)) and NoSign(And(sym, sym))
    // Sign(And(count_rsi,count_rsi)) testtest: /home/neo/smu/kernel-se/z3/include/z3++.h:1652: z3::expr z3::operator&&(const z3::expr&, const z3::expr&): Assertion `a.is_bool() && b.is_bool()' failed.
    /*
    ExprPtr and_expr_test = std::make_shared<AndExpr>(udef_expr, udef_expr);
    ExprPtr sign_expr_test = std::make_shared<SignExpr>(and_expr_test);
    SignExpr *sign_test = static_cast<SignExpr*>(sign_expr_test.get());

    ExprPtr nosign_expr_test = std::make_shared<NoSignExpr>(and_expr_test);
    SignExpr *nosign_test = static_cast<SignExpr*>(nosign_expr_test.get());
    sign_test->print();
    nosign_test->print();
    */

    /*
    // testing 2022.11.21
    // Ult(Add(Add(CombineMulti(Extract(gid_rdi, 0, 4), 0x0, 0xc9, 0xff, 0xff, ),Mul(0x1,0x1)),0xffffffffffffffff),0x0) terminate called after throwing an instance of 'z3::exception' what():  Argument #x01 at position 1 does not match declaration (declare-fun bvmul ((_ BitVec 64) (_ BitVec 64)) (_ BitVec 64))
    ExprPtr mul_expr = std::make_shared<MulExpr>(const_expr3, const_expr3);
    MulExpr *mul_test = static_cast<MulExpr*>(mul_expr.get());
    ExprPtr extract_expr_test = std::make_shared<ExtractExpr>(udef_expr, 0, 4);
    ExprPtr const_expr_test1 = std::make_shared<ConstExpr>(0x0);
    ExprPtr const_expr_test2 = std::make_shared<ConstExpr>(0xc9);
    ExprPtr const_expr_test3 = std::make_shared<ConstExpr>(0xff);
    ExprPtr const_expr_test4 = std::make_shared<ConstExpr>(0xff);
    ExprPtr const_expr_test5 = std::make_shared<ConstExpr>(0xffffffffffffffff);
    ExprPtr multicombine_expr_test = std::make_shared<CombineMultiExpr>(extract_expr_test, const_expr1, const_expr2, const_expr3, const_expr_test4, const_expr_test4);
    ExprPtr add_expr_test1 = std::make_shared<AddExpr>(multicombine_expr_test, mul_test);
    ExprPtr add_expr_test2 = std::make_shared<AddExpr>(add_expr_test1, const_expr_test5);
    ExprPtr ult_expr_test = std::make_shared<UltExpr>(add_expr_test2, const_expr_test1);
    UltExpr *ult_test = static_cast<UltExpr*>(ult_expr_test.get());
    //mul_test->print();
    ult_test->print();
    */

    // testing 2022.11.21 # TODO no work
    //Distinct(And(Extract(flags_rdx, 0, 4),0xf8)) terminate called after throwing an instance of 'z3::exception' what():  ast is not an expression
    /*
    ExprPtr extract_expr_test = std::make_shared<ExtractExpr>(udef_expr, 0, 4);
    ExprPtr const_expr_test = std::make_shared<ConstExpr>(0xf8);
    ExprPtr and_expr_test = std::make_shared<AndExpr>(extract_expr_test, const_expr_test);
    ExprPtr dist_expr_test = std::make_shared<DistinctExpr>(and_expr_test);
    DistinctExpr *dist_test = static_cast<DistinctExpr*>(dist_expr_test.get());
    dist_test->print();
    */

    /*
    // testing 2022.11.29 TODO not passed
    // Equal(Sub(CombineMulti(And(Extract(prot_rsi, 0, 4),0x5), Extract(prot_rsi, 4, 8), ),0x1))terminate called after throwing an instance of 'z3::exception' what():  ast is not an expression std::set<KVExprPtr> constraints_test;
    ExprPtr extract_expr_test = std::make_shared<ExtractExpr>(udef_expr, 0, 4);
    ExtractExpr *extract_test1 = static_cast<ExtractExpr*>(extract_expr_test.get());
    extract_test1->print();
    std::cout << "\n";
    */

    /*
    ExprPtr const_expr_test = std::make_shared<ConstExpr>(0x5);
    const_expr_test->size = 4;
    ExprPtr and_expr_test1 = std::make_shared<AndExpr>(extract_expr_test, const_expr_test);
    //ExprPtr dist_expr_test = std::make_shared<DistinctExpr>(and_expr_test);
    //DistinctExpr *dist_test = static_cast<DistinctExpr*>(dist_expr_test.get());
    //dist_test->print();
    AndExpr *and_test = static_cast<AndExpr*>(and_expr_test1.get());
    and_test->print();
    std::cout << "\n";
    expr and_expr_z3 = z3_handler->Z3HandleAnd(and_expr_test1, const_expr_test);
    std::cout << "and_expr_z3 : " << and_expr_z3 << std::endl;

    ExprPtr extract_expr_test2 = std::make_shared<ExtractExpr>(udef_expr, 4, 8);
    ExtractExpr *extract_test2 = static_cast<ExtractExpr*>(extract_expr_test2.get());
    extract_test2->print();
    std::cout << "\n";

    std::vector<ExprPtr> e;
    std::vector<int> s;
    std::vector<int> o;
    e.push_back(and_expr_test1);
    e.push_back(extract_expr_test2);
    s.push_back(4);
    s.push_back(4);
    o.push_back(0);
    o.push_back(4);
    ExprPtr multicombine_expr = std::make_shared<CombineMultiExpr>(e, o, s);
    CombineMultiExpr *combine_expr_test = static_cast<CombineMultiExpr*>(multicombine_expr.get());
    combine_expr_test->print();


    ExprPtr const_expr_test1 = std::make_shared<ConstExpr>(0x1);
    const_expr_test1->size = 4;
    ExprPtr sub_expr_test = std::make_shared<SubExpr>(multicombine_expr, const_expr_test1);
    sub_expr_test->print();
    */


    // testing 2022.12.13
    // Distinct(And(ZeroEXT(Extract(mode_rdx, 0, 2)),0x8000000)) ast is not an expression
    // @TODO done in 2023.3.3: fix this by change the way to combine experssions
    ExprPtr extract_expr_test = std::make_shared<ExtractExpr>(udef_expr, 0, 1);
    ExprPtr zeroext_expr_test = std::make_shared<ZeroExtExpr>(extract_expr_test, 4, 0);
    ExprPtr const_expr_test = std::make_shared<ConstExpr>(0xe0);
    const_expr_test->size = 4;
    ExprPtr and_expr_test = std::make_shared<AndExpr>(zeroext_expr_test, const_expr_test);
    ExprPtr dist_expr_test = std::make_shared<DistinctExpr>(and_expr_test);
    DistinctExpr *dist_test = static_cast<DistinctExpr*>(dist_expr_test.get());
    dist_test->print();
    std::cout << "\n";



    std::set<KVExprPtr> constraints_test;
    //constraints_test.insert(sub_expr_test);
    //constraints_test.insert(add_expr);
    //constraints_test.insert(dist_expr_test);
    constraints_test.insert(and_expr_test);
    //constraints_test.insert(sign_expr_test);
    //constraints_test.insert(nosign_expr_test);
    //constraints_test.insert(lnot_expr1);
    //constraints_test.insert(lnot_expr2);

    //constraints_test.insert(ugt_expr);
    //constraints_test.insert(lnot_expr);
    //constraints_test.insert(equal_expr_test);

    // testing Z3SolveOne
    Z3HANDLER::Z3Handler *z3_handler_test = new Z3HANDLER::Z3Handler();
    /*
    std::map<std::string, unsigned long long> ret_result;
    unsigned long long time_start_solve = rdtsc();
    ret_result = z3_handler_test->Z3SolveOne(constraints_test); // now the [symbolic name, concrete value] map will be returned
    unsigned long long time_end_solve = rdtsc();
    for (auto it = ret_result.begin(); it != ret_result.end(); it ++){
        std::cout << "symbol : " << it->first << std::endl;
        printf("value : %llu(dec) %x(hex) \n", it->second, (unsigned int) it->second);
    }
    */

    // testing concritize function
    // 'obj' is a symbolic object defined with SYMemObject*, 'value' is the concrete value; 'constraints_test' is a set of constraints
    std::vector<VMState::SYMemObject*> symobjts;
    //obj->i32 = 1;
    //symobjts.push_back(obj);
    obj->i32 = 20;
    symobjts.push_back(obj);
    //symobjts.push_back(obj1);
    //symobjts.push_back(obj); // testing a symbolic object which is not in the constraints
    //values.push_back(1000);
    //unsigned long long time_start_concritize = rdtsc();
    bool ret_bool = z3_handler_test->Z3SolveConcritize(symobjts, constraints_test);
    int64_t ret_con = z3_handler_test->Z3SolveConcritizeToConstant(symobjts, constraints_test);
    std::cout << "result of concritize (to bool): " << ret_bool << std::endl;
    std::cout << "result of concritize (to a constant) : " << ret_con << std::endl;
    //unsigned long long time_end_concritize = rdtsc();
    //std::cout << "Time for Z3SolveOne : " << time_end_solve - time_start_solve << std::endl;
    //std::cout << "Time for Z3SolveConcritize : " << time_end_concritize - time_start_concritize << std::endl;
}
void eval_example1() {
    std::cout << "eval example 1\n";
    context c;
    expr x = c.int_const("x");
    expr y = c.int_const("y");
    solver s1(c);

    s1.add(x > 5);
    s1.add(x == 100);

    unsigned long long start1 = rdtsc();
    std::cout << s1.check() << "\n";
    unsigned long long end1 = rdtsc();
    std::cout << "Time for normal Z3 (solver.check()) : " << end1 - start1  << std::endl;

    solver s2(c);
    unsigned long long start2 = rdtsc();
    //s2.add(100>5);
    y = x > 5 && x == 100;
    //y.simplify();
    s2.add(y);
    s2.check();
    //model m = s2.get_model();
    //s2.get_model().eval(y);
    unsigned long long end2 = rdtsc();
    std::cout << "Time for normal Z3 (check): " << end2 - start2  << std::endl;


    /*
    model m = s.get_model();
    std::cout << "Model:\n" << m << "\n";
    std::cout << "x+y = " << m.eval(x+y) << "\n";
    */
    /*
    expr xx = c.bv_const("xx", 32);
    expr yy = c.bv_const("yy", 32);
    expr const_test1 = c.bv_val(1, 32);
    expr const_test2 = c.bv_val(1, 32);
    expr sym_and_const = xx & const_test1;
    expr const_and_const = const_test1 & const_test2;
    expr sym_and_sym = xx & yy;
    std::cout << "const_and_const : " << const_and_const << std::endl;
    std::cout << "sym_and_sym : " << sym_and_sym << std::endl;
    std::cout << "sym_and_const : " << sym_and_const << std::endl;
    std::cout << "length of sym_and_const : "  << std::endl;
    expr comb = z3::concat(sym_and_const, const_test2);
    expr subtest = yy - const_test1;
    std::cout << "comb : " << comb << std::endl;
    std::cout << "subtest : " << subtest << std::endl;
    */

    expr zz = c.bv_const("zz", 32);
    expr aa = zz.extract(15, 0);
    expr const_test1 = c.bv_val(0x8000000, 32);
    expr zeroext = z3::zext(aa, 16);
    std::cout << "zeroext : " << zeroext << std::endl;
    expr and_test = zeroext & const_test1;
    // expr dist = and_test != 0;
    std::cout << "and_test : " << and_test << std::endl;

}


void substitute_example() {
    std::cout << "substitute example\n";
    context c;
    expr x(c);
    x = c.int_const("x");
    expr f(c);
    //f = (x == 2) || (x == 1);
    f = (x > 5);
    std::cout << f << std::endl;
    std::cout << f.is_true() << std::endl;

    expr two(c), three(c);
    two   = c.int_const("x");
    three = c.int_val(10);
    Z3_ast from[] = { two };
    Z3_ast to[]   = { three };
    expr new_f(c);
    unsigned long long start = rdtsc();
    new_f = to_expr(c, Z3_substitute(c, f, 1, from, to));
    unsigned long long end = rdtsc();
    std::cout << new_f << std::endl;
    std::cout << new_f.simplify().is_true() << std::endl;
    std::cout << "Time for normal Z3 (in substitute): " << end - start  << std::endl;

}


int main(){
    test();
    //unsigned long long start = rdtsc();
   //  eval_example1();
    //substitute_example();
    //unsigned long long end = rdtsc();
    //std::cout << "Time for normal Z3 : " << end - start  << std::endl;

    //std::cout << "/////////////////" << std::endl;
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
