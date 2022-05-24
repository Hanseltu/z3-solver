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
    z3::expr Z3HandleBin(ExprPtr r, ExprPtr l);
    z3::expr Z3HandleTri(ExprPtr r, ExprPtr m, ExprPtr l);
    z3::expr Z3HandleUry(ExprPtr ury_expr);

    z3::expr Z3HandleAdd(ExprPtr r, ExprPtr l); // 7
    z3::expr Z3HandleSub(ExprPtr r, ExprPtr l);
    z3::expr Z3HandleMul(ExprPtr r, ExprPtr l);
    z3::expr Z3HandleUDiv(ExprPtr r, ExprPtr l);

    z3::expr Z3HandleSDiv(ExprPtr r, ExprPtr l); // 11
    z3::expr Z3HandleURem(); // not defined?
    z3::expr Z3HandleSRem(ExprPtr srem_expr);
    z3::expr Z3HandleNeg(ExprPtr neg_expr);
    z3::expr Z3HandleNot(ExprPtr not_expr);
    z3::expr Z3HandleAnd(ExprPtr r, ExprPtr l);
    z3::expr Z3HandleOr(ExprPtr r, ExprPtr l);
    z3::expr Z3HandleXor(ExprPtr r, ExprPtr l);
    z3::expr Z3HandleShl(ExprPtr r, ExprPtr l);
    z3::expr Z3HandleLShr(ExprPtr r, ExprPtr l);

    z3::expr Z3HandleAShr(ExprPtr r, ExprPtr l); // 21
    z3::expr Z3HandleEqual(ExprPtr equal_expr);
    z3::expr Z3HandleDistinct(ExprPtr dist_expr);
    z3::expr Z3HandleUlt(ExprPtr ult_expr);
    z3::expr Z3HandleUle(ExprPtr ule_expr);
    z3::expr Z3HandleUgt(ExprPtr ugt_expr);
    z3::expr Z3HandleUge(ExprPtr uge_expr);
    z3::expr Z3HandleSlt(ExprPtr slt_expr);
    z3::expr Z3HandleSle(ExprPtr sle_expr);
    z3::expr Z3HandleSgt(ExprPtr sgt_expr);

    z3::expr Z3HandleSge(ExprPtr sge_expr); // 31
    z3::expr Z3HandleLor(ExprPtr lor_expr);
    z3::expr Z3HandleLAnd(ExprPtr land_expr);
    z3::expr Z3HandleLNot(ExprPtr lnot_expr);
    z3::expr Z3HandleSignExt(ExprPtr signext_expr);
    z3::expr Z3HandleZeroEXT(ExprPtr zero_expr);
    z3::expr Z3HandleShrd(ExprPtr r, ExprPtr m, ExprPtr l);
    z3::expr Z3HandleSign(ExprPtr sign_expr);
    z3::expr Z3HandleNoSign(ExprPtr nosign_expr);
    z3::expr Z3HandleOverflow(ExprPtr overflow_expr);

    z3::expr Z3HandleNoOverflow(ExprPtr nooverflow_expr); // 41
    z3::expr Z3HandleCombine(ExprPtr r, ExprPtr l);  // ?lsize? rsize?
    z3::expr Z3HandleExtract(ExprPtr r, ExprPtr l, int size); // need to return size as well

};
} // end of namespace

#endif  // end of _Z3HANDLER_H__


/* 1. Some expressions are not defined ? e.g., Const? Bin? Tri? Ury?
 * 2. How to define Combine? Tri? Overflow ? Shr ...
 * 3. Some expression are missing? e.g., URem?
 *
*/
