#include "Z3Handler.h"

using namespace z3;
using namespace Z3HANDLER;

Z3Handler::Z3Handler(): context_(g_z3_context){}

Z3Handler::~Z3Handler(){}


z3::expr Z3HandleUND(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleConst(){ // 3
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleBin(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleTri(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleUry(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleAdd(){ // 7
    //context c;
    expr x = context_.int_val(999);
    return x;
}

z3::expr Z3HandleSub(){
    static context c;
    static expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleMul(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleUDiv(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleSDiv(){ // 11
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleURem(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleSRem(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleNeg(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleNot(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleAnd(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleOr(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleXor(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleShl(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleLShr(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleAShr(){ // 21

    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleEqual(){

    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleDistinct(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleUlt(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleUle(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleUgt(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleUge(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleSlt(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleSle(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleSgt(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleSge(){ // 31
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleLor(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleLAnd(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleLNot(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleSignExt(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleZeroEXT(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleShrd(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleSign(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleNoSign(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleOverflow(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleNoOverflow(){ // 41
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleCombine(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}

z3::expr Z3HandleExtract(){
    context c;
    expr x = c.bv_const("x", 100);
    return x;
}
