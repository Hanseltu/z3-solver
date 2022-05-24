#ifndef _Z3HANDLER_H__
#define _Z3HANDLER_H__


/* @THX class for transfer constraint
 *
 *
*/


#include"z3++.h"
#include "Expr.h"

extern z3::context g_z3_context;
using namespace EXPR;
// using namespace z3;
namespace Z3HANDLER {
class Z3Handler{
protected:
    z3::context& context_;
public:
    //z3::expr x = c.int_val(0);

    Z3Handler();
    virtual ~Z3Handler();

    z3::expr Z3HandlingExprPtr(ExprPtr ptr);

    // handle different expressions
    z3::expr Z3HandleUND(ExprPtr undef_expr);

    z3::expr Z3HandleConst(ExprPtr const_expr); // 3
    z3::expr Z3HandleBin();
    z3::expr Z3HandleTri();
    z3::expr Z3HandleUry();

    z3::expr Z3HandleAdd(ExprPtr r, ExprPtr l); // 7
    z3::expr Z3HandleSub();
    z3::expr Z3HandleMul();
    z3::expr Z3HandleUDiv();

    z3::expr Z3HandleSDiv(); // 11
    z3::expr Z3HandleURem();
    z3::expr Z3HandleSRem();
    z3::expr Z3HandleNeg();
    z3::expr Z3HandleNot();
    z3::expr Z3HandleAnd();
    z3::expr Z3HandleOr();
    z3::expr Z3HandleXor();
    z3::expr Z3HandleShl();
    z3::expr Z3HandleLShr();

    z3::expr Z3HandleAShr(); // 21
    z3::expr Z3HandleEqual();
    z3::expr Z3HandleDistinct();
    z3::expr Z3HandleUlt();
    z3::expr Z3HandleUle();
    z3::expr Z3HandleUgt();
    z3::expr Z3HandleUge();
    z3::expr Z3HandleSlt();
    z3::expr Z3HandleSle();
    z3::expr Z3HandleSgt();

    z3::expr Z3HandleSge(ExprPtr ptr); // 31
    z3::expr Z3HandleLor();
    z3::expr Z3HandleLAnd();
    z3::expr Z3HandleLNot();
    z3::expr Z3HandleSignExt();
    z3::expr Z3HandleZeroEXT();
    z3::expr Z3HandleShrd();
    z3::expr Z3HandleSign();
    z3::expr Z3HandleNoSign();
    z3::expr Z3HandleOverflow();

    z3::expr Z3HandleNoOverflow(); // 41
    z3::expr Z3HandleCombine();
    z3::expr Z3HandleExtract();

};
} // end of namespace

#endif  // end of _Z3HANDLER_H__
