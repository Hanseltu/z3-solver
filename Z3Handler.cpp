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
        case Expr::Kind::UNDEFINED:{ // -1
            //std::cout << "Handling " << kind << std::endl;
            return Z3HandleUND(ptr);
        }
        case Expr::Kind::Const:{ // 3
            return Z3HandleConst(ptr);
        }
        case Expr::Kind::Bin:{
            ;
        }
        case Expr::Kind::Tri:{
            ;
        }
        case Expr::Kind::Ury:{
            ;
        }
        case Expr::Kind::Add: { // 7
            AddExpr * expr_r = static_cast<AddExpr*>(ptr.get());
            ExprPtr R = expr_r->getExprPtrR();
            ExprPtr L = expr_r->getExprPtrL();
            return Z3HandleAdd(R, L);
        }
        case Expr::Kind::Sub:{
            ;
        }
        case Expr::Kind::Mul:{
            ;
        }
        case Expr::Kind::UDiv:{
            ;
        }
        case Expr::Kind::SDiv:{ // 11
            ;
        }
        case Expr::Kind::URem:{
            ;
        }
        case Expr::Kind::SRem:{
            ;
        }
        case Expr::Kind::Neg:{
            ;
        }
        case Expr::Kind::Not:{
            ;
        }
        case Expr::Kind::And:{
            ;
        }
        case Expr::Kind::Or:{
            ;
        }
        case Expr::Kind::Xor:{
            ;
        }
        case Expr::Kind::Shl:{
            ;
        }
        case Expr::Kind::LShr:{
            ;
        }
        case Expr::Kind::AShr:{ // 21
            ;
        }
        case Expr::Kind::Equal:{
            ;
        }
        case Expr::Kind::Distinct:{
            ;
        }
        case Expr::Kind::Ult:{
            ;
        }
        case Expr::Kind::Ule:{
            ;
        }
        case Expr::Kind::Ugt:{
            ;
        }
        case Expr::Kind::Uge:{
            ;
        }
        case Expr::Kind::Slt:{
            ;
        }
        case Expr::Kind::Sle:{
            ;
        }
        case Expr::Kind::Sgt:{
            ;
        }
        case Expr::Kind::Sge:{ // 31
            return Z3HandleSge(ptr);
        }
        case Expr::Kind::Lor:{
            ;
        }
        case Expr::Kind::LAnd:{
            ;
        }
        case Expr::Kind::LNot:{
            ;
        }
        case Expr::Kind::SignEXT:{
            ;
        }
        case Expr::Kind::ZeroEXT:{
            ;
        }
        case Expr::Kind::Shrd:{
            ;
        }
        case Expr::Kind::Sign:{
            ;
        }
        case Expr::Kind::NoSign:{
            ;
        }
        case Expr::Kind::Overflow:{
            ;
        }
        case Expr::Kind::NoOverflow:{ // 41
            ;
        }
        case Expr::Kind::Combine:{
            ;
        }
        case Expr::Kind::Extract:{
            ;
        }
        default:{
            printf("\033[47;31m Z3 Handlering ERROR : Unsupported type of EXPR? \033[0m\n");
            throw ptr;
        }
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

z3::expr Z3Handler::Z3HandleBin(ExprPtr r, ExprPtr l){ // not sure how to write z3 expr
    return context_.bv_val(100, 64);
}

z3::expr Z3Handler::Z3HandleTri(ExprPtr r, ExprPtr m, ExprPtr l){ // not sure how to write z3 expr
    return context_.bv_val(100, 64);
}

z3::expr Z3Handler::Z3HandleUry(ExprPtr ptr){ // not sure how to write z3 expr
    expr x = context_.bv_const("x", 100);
    return x;
}

z3::expr Z3Handler::Z3HandleAdd(ExprPtr r, ExprPtr l){ // 7
    //context c;
    expr ret = Z3HandlingExprPtr(r) + Z3HandlingExprPtr(l);
    //TODO need to handle signed/unsigned ?
    return ret;
}

z3::expr Z3Handler::Z3HandleSub(ExprPtr r, ExprPtr l){
    expr ret = Z3HandlingExprPtr(l) - Z3HandlingExprPtr(r);
    return ret;
}

z3::expr Z3Handler::Z3HandleMul(ExprPtr r, ExprPtr l){
    expr ret = Z3HandlingExprPtr(l) * Z3HandlingExprPtr(r);
    return ret;
}

z3::expr Z3Handler::Z3HandleUDiv(ExprPtr r, ExprPtr l){
    expr ret = z3::udiv(Z3HandlingExprPtr(l), Z3HandlingExprPtr(r));
    return ret;
}

z3::expr Z3Handler::Z3HandleSDiv(ExprPtr r, ExprPtr l){ // 11
    expr ret = Z3HandlingExprPtr(l) / Z3HandlingExprPtr(r) ;
    return ret;
}

z3::expr Z3Handler::Z3HandleURem(){ // not defined in Expr.h
    expr x = context_.bv_val(100, 64);
}

z3::expr Z3Handler::Z3HandleSRem(ExprPtr r, ExprPtr l){
    expr ret = z3::srem(Z3HandlingExprPtr(l), Z3HandlingExprPtr(r));
    return ret;
}

z3::expr Z3Handler::Z3HandleNeg(ExprPtr ptr){
    expr x = Z3HandlingExprPtr(ptr);
    expr ret = (- x);
    return ret;
}

z3::expr Z3Handler::Z3HandleNot(ExprPtr ptr){
    NotExpr *not_expr = static_cast<NotExpr*>(ptr.get());
    if (not_expr == NULL){
        printf("\033[47;31m Z3 Handlering ERROR : NotExpr \033[0m\n");
        throw not_expr;
    }
    expr x = Z3HandlingExprPtr(not_expr->getExprPtr());
    expr ret = (~ x);
    return ret;
}

z3::expr Z3Handler::Z3HandleAnd(ExprPtr r, ExprPtr l){
    expr ret = Z3HandlingExprPtr(l) & Z3HandlingExprPtr(r);
    return ret;
}

z3::expr Z3Handler::Z3HandleOr(ExprPtr r, ExprPtr l){
    expr ret = Z3HandlingExprPtr(l) | Z3HandlingExprPtr(r);
    return ret;
}

z3::expr Z3Handler::Z3HandleXor(ExprPtr r, ExprPtr l){
    expr ret = Z3HandlingExprPtr(l) ^ Z3HandlingExprPtr(r);
    return ret;
}

z3::expr Z3Handler::Z3HandleShl(ExprPtr r, ExprPtr l){
    expr ret = z3::shl(Z3HandlingExprPtr(l), Z3HandlingExprPtr(r));
    return ret;
}

z3::expr Z3Handler::Z3HandleLShr(ExprPtr r, ExprPtr l){
    expr ret = z3::lshr(Z3HandlingExprPtr(l), Z3HandlingExprPtr(r));
    return ret;
}

z3::expr Z3Handler::Z3HandleAShr(ExprPtr r, ExprPtr l){ // 21
    expr ret = z3::ashr(Z3HandlingExprPtr(l), Z3HandlingExprPtr(r));
    return ret;
}

z3::expr Z3Handler::Z3HandleEqual(ExprPtr ptr){ //  Should have two sub-expressions?
    return context_.bv_val(100, 64);
}

z3::expr Z3Handler::Z3HandleDistinct(ExprPtr ptr){ // Should have two sub-expressions?
    return context_.bv_val(100, 64);
}


// for Ult, Ule, Ugt, Uge, Slt, Sle, Sge, Sge, are they only compare with 0? rather than two sub-expressions?
// If this is the case, is it 0 always in the right side? e.g., x >0 not 0 > x?
z3::expr Z3Handler::Z3HandleUlt(ExprPtr ptr){
    UltExpr *ult_expr = static_cast<UltExpr*>(ptr.get());
    if (ult_expr == NULL){
        printf("\033[47;31m Z3 Handlering ERROR : UltExpr \033[0m\n");
        throw ult_expr;
    }
    expr x = Z3HandlingExprPtr(ult_expr->getExprPtr());
    expr ret = z3::ult(x, 0);
    return ret;
}

z3::expr Z3Handler::Z3HandleUle(ExprPtr ptr){
    UleExpr *ule_expr = static_cast<UleExpr*>(ptr.get());
    if (ule_expr == NULL){
        printf("\033[47;31m Z3 Handlering ERROR : UleExpr \033[0m\n");
        throw ule_expr;
    }
    expr x = Z3HandlingExprPtr(ule_expr->getExprPtr());
    expr ret = z3::ule(x, 0);
    return ret;
}

z3::expr Z3Handler::Z3HandleUgt(ExprPtr ptr){
    UgtExpr *ugt_expr = static_cast<UgtExpr*>(ptr.get());
    if (ugt_expr == NULL){
        printf("\033[47;31m Z3 Handlering ERROR : UleExpr \033[0m\n");
        throw ugt_expr;
    }
    expr x = Z3HandlingExprPtr(ugt_expr->getExprPtr());
    expr ret = z3::ugt(x, 0);
    return ret;
}

z3::expr Z3Handler::Z3HandleUge(ExprPtr ptr){
    UgeExpr *uge_expr = static_cast<UgeExpr*>(ptr.get());
    if (uge_expr == NULL){
        printf("\033[47;31m Z3 Handlering ERROR : UleExpr \033[0m\n");
        throw uge_expr;
    }
    expr x = Z3HandlingExprPtr(uge_expr->getExprPtr());
    expr ret = z3::uge(x, 0);
    return ret;
}

z3::expr Z3Handler::Z3HandleSlt(ExprPtr ptr){
    SltExpr *slt_expr = static_cast<SltExpr*>(ptr.get());
    if (slt_expr == NULL){
        printf("\033[47;31m Z3 Handlering ERROR : SltExpr \033[0m\n");
        throw slt_expr;
    }
    expr x = Z3HandlingExprPtr(slt_expr->getExprPtr());
    expr ret = (x < 0);
    return ret;
}

z3::expr Z3Handler::Z3HandleSle(ExprPtr ptr){
    SleExpr *sle_expr = static_cast<SleExpr*>(ptr.get());
    if (sle_expr == NULL){
        printf("\033[47;31m Z3 Handlering ERROR : SleExpr \033[0m\n");
        throw sle_expr;
    }
    expr x = Z3HandlingExprPtr(sle_expr->getExprPtr());
    expr ret = (x <= 0);
    return ret;
}

z3::expr Z3Handler::Z3HandleSgt(ExprPtr ptr){
    SgtExpr *sgt_expr = static_cast<SgtExpr*>(ptr.get());
    if (sgt_expr == NULL){
        printf("\033[47;31m Z3 Handlering ERROR : SgtExpr \033[0m\n");
        throw sgt_expr;
    }
    expr x = Z3HandlingExprPtr(sgt_expr->getExprPtr());
    expr ret = (x > 0);
    return ret;
}

z3::expr Z3Handler::Z3HandleSge(ExprPtr sge_expr_ptr){ // 31
    SgeExpr *sge_expr = static_cast<SgeExpr*>(sge_expr_ptr.get());
    if (sge_expr == NULL){
        printf("\033[47;31m Z3 Handlering ERROR : SgeExpr \033[0m\n");
        throw sge_expr;
    }
    expr x = Z3HandlingExprPtr(sge_expr->getExprPtr());
    expr ret = (x >= 0); // TODO need to confirm: compare with zero?
    return ret;
}

z3::expr Z3Handler::Z3HandleLor(ExprPtr ptr){ // not defined in Expr.h
    expr x = context_.bv_val(100, 64);
    return x;
}

z3::expr Z3Handler::Z3HandleLAnd(ExprPtr ptr){ // not defined in Expr.h
    return context_.bv_val(100, 64);
}

z3::expr Z3Handler::Z3HandleLNot(ExprPtr ptr){
    LNotExpr *lnot_expr = static_cast<LNotExpr*>(ptr.get());
    if (lnot_expr == NULL){
        printf("\033[47;31m Z3 Handlering ERROR : LNotExpr \033[0m\n");
        throw lnot_expr;
    }
    expr x = Z3HandlingExprPtr(lnot_expr->getExprPtr());
    expr ret = ! x; // TODO need to confirm: compare with zero?
    return ret;
}

z3::expr Z3Handler::Z3HandleSignExt(ExprPtr ptr){ // not sure how to write z3 expr
    return context_.bv_val(100, 64);
}

z3::expr Z3Handler::Z3HandleZeroEXT(ExprPtr ptr){ // not sure how to write z3 expr
    return context_.bv_val(100, 64);
}

z3::expr Z3Handler::Z3HandleShrd(ExprPtr r, ExprPtr m, ExprPtr l){  // not sure how to write z3 expr
    return context_.bv_val(100, 64);
}

z3::expr Z3Handler::Z3HandleSign(ExprPtr ptr){ // not sure how to write z3 expr
    return context_.bv_val(100, 64);
}

z3::expr Z3Handler::Z3HandleNoSign(ExprPtr ptr){ // not sure how to write z3 expr
    return context_.bv_val(100, 64);
}

z3::expr Z3Handler::Z3HandleOverflow(ExprPtr ptr){ // not sure how to write z3 expr
    return context_.bv_val(100, 64);
}

z3::expr Z3Handler::Z3HandleNoOverflow(ExprPtr ptr){ // 41 // not sure how to write z3 expr
    return context_.bv_val(100, 64);
}

z3::expr Z3Handler::Z3HandleCombine(ExprPtr r, ExprPtr l){ // Is the same as Concat? This version does not consider the lsize and rsize
    expr ret = z3::concat(Z3HandlingExprPtr(l), Z3HandlingExprPtr(r));
    return ret;
}

z3::expr Z3Handler::Z3HandleExtract(ExprPtr ptr, int start, int end){
    ExtractExpr *extract_expr = static_cast<ExtractExpr*>(ptr.get());
    if (extract_expr == NULL){
        printf("\033[47;31m Z3 Handlering ERROR : LNotExpr \033[0m\n");
        throw extract_expr;
    }
    expr x = Z3HandlingExprPtr(extract_expr->getExprPtr());
    int s = extract_expr->getStart();
    int e = extract_expr->getEnd();
    return x.extract(e, s); // looks different with the existing implementation
}
