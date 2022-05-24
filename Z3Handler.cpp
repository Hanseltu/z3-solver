#include "Z3Handler.h"

#include <limits.h>
#include <stdlib.h>


// print color setting
#define COLOR_NONE "\033[0m"
#define RED "\033[1;31;40m"


void perror(char *const msg);
void perror(char *const msg){ //TODO
    printf("\033[47;31m Z3 Handlering ERROR : %s \033[0m", msg);
    printf("\n");
}

using namespace z3;
using namespace Z3HANDLER;
Z3Handler::Z3Handler(): context_(g_z3_context){}

Z3Handler::~Z3Handler(){}

z3::expr Z3Handler::Z3HandlingExprPtr(ExprPtr ptr){
    int kind = ptr->getKind();

    switch (kind){
        case Expr::Kind::UNDEFINED:
            //std::cout << "Handling " << kind << std::endl;
            return Z3HandleUND(ptr);
        case Expr::Kind::Const:
            return Z3HandleConst(ptr);
        case Expr::Kind::Sge:
            return Z3HandleSge(ptr);
        default:
            printf("\033[47;31m Z3 Handlering ERROR : Unsuported type of EXPR? \033[0m\n");
            throw ptr;
    }
}


z3::expr Z3Handler::Z3HandleUND(ExprPtr udef_expr_ptr){
    UDefExpr * udef_expr = static_cast<UDefExpr*>(udef_expr_ptr.get());
    if (udef_expr == NULL){
        printf("\033[47;31m Z3 Handlering ERROR : UDefExpr \033[0m\n");
        throw udef_expr;
    }
    SYMemObject *obj = udef_expr->getObject();
    std::string sym_name = obj->name;
    unsigned long long size = obj->size;
    expr x = context_.bv_const(sym_name.c_str(), size*8);
    return x;
}

z3::expr Z3Handler::Z3HandleConst(ExprPtr const_expr_ptr){ // 3
    ConstExpr *const_expr = static_cast<ConstExpr*>(const_expr_ptr.get());
    if (const_expr == NULL){
        printf("\033[47;31m Z3 Handlering ERROR : UDefExpr \033[0m\n");
        throw const_expr;
    }
    uint64_t value = const_expr->getValue();
    //std::cout << "value in ConstExpr : " << value << std::endl;
    expr x = context_.bv_val(value, 64);
    return x;
}

z3::expr Z3Handler::Z3HandleBin(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleTri(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleUry(){
    expr x = context_.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleAdd(ExprPtr r, ExprPtr l){ // 7
    //context c;
    expr ret = Z3HandlingExprPtr(r) + Z3HandlingExprPtr(l);
    //TODO need to handle signed/unsigned
    return ret;
}

z3::expr Z3Handler::Z3HandleSub(){
    static context c;
    static expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleMul(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleUDiv(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleSDiv(){ // 11
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleURem(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleSRem(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleNeg(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleNot(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleAnd(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleOr(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleXor(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleShl(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleLShr(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleAShr(){ // 21

    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleEqual(){

    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleDistinct(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleUlt(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleUle(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleUgt(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleUge(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleSlt(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleSle(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleSgt(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleSge(ExprPtr sge_expr_ptr){ // 31
    SgeExpr *sge_expr = static_cast<SgeExpr*>(sge_expr_ptr.get());
    if (sge_expr == NULL){
        printf("\033[47;31m Z3 Handlering ERROR : SgeExpr \033[0m\n");
        throw sge_expr;
    }
    expr x = Z3HandlingExprPtr(sge_expr->getExprPtr());
    expr ret = x >= 0;
    return ret;
}

z3::expr Z3Handler::Z3HandleLor(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleLAnd(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleLNot(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleSignExt(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleZeroEXT(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleShrd(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleSign(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleNoSign(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleOverflow(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleNoOverflow(){ // 41
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleCombine(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleExtract(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}
