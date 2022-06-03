#include <iostream>
#include "Expr.h"
//#include "ExecCtrl.h"

//#include "VMState.h"

using namespace EXPR;
static char exprName[][16] = {"","","","","","","",
                            "Add" ,
                            "Sub" ,
                            "Mul" ,
                            "UDiv" ,
                            "SDiv" ,
                            "URem" ,
                            "SRem" ,
                            "Neg" ,
                            "Not" ,
                            "And" ,
                            "Or	" ,
                            "Xor" ,
                            "Shl" ,
                            "LShr" ,
                            "AShr" ,
                            "Equal" ,
                            "Distinct" ,
                            "Ult" ,
                            "Ule" ,
                            "Ugt" ,
                            "Uge" ,
                            "Slt" ,
                            "Sle" ,
                            "Sgt" ,
                            "Sge" ,
                            "LOr" ,
                            "LAnd" ,
                            "LNot" ,
                            "SignEXT",
                            "ZeroEXT",
                            "Shrd",
                            "Sign",
                            "NoSign",
                            "Overflow",
                            "NoOverflow",
                            "Combine",
                            "Extract"
                            };


void UDefExpr::print () {
    //VMState::SYMemObject *obj = (VMState::SYMemObject *) O;
    SYMemObject *obj = (SYMemObject *) O;
    if(obj != NULL )
        std::cout << obj->name ;
    else
        std::cout << "OBJ" ;
}

void ConstExpr::print () {
    std::cout << V;
}

void BinExpr::print () {
    std::cout<<exprName[exprID]<<"(";
    R->print();
    std::cout<<",";
    L->print();
    std::cout<<")";
}

void UryExpr::print () {
    std::cout<<exprName[exprID]<<"(";
    E->print();
    std::cout<<")";
}

void TriExpr::print () {
    std::cout<<exprName[exprID]<<"(";
    L->print();
    std::cout<<",";
    M->print();
    std::cout<<",";
    R->print();
    std::cout<<")";
}

void ExtractExpr::print () {
    std::cout<<exprName[exprID]<<"(";
    E->print();
    std::cout << ", " << s << ", " << e ;
    std::cout<<")";
}
/*
KVExprPtr CreateExprByID(int id, KVExprPtr R, KVExprPtr M, KVExprPtr L, int size = 4, int offset = 0) {

    KVExprPtr exprptr = NULL;
    switch (id) {
        case EXPR_Add		 :
        case EXPR_Sub		 :
        case EXPR_Mul		 :
        case EXPR_UDiv		 :
        case EXPR_SDiv		 :
        case EXPR_URem		 :
        case EXPR_SRem		 :
        case EXPR_Neg        :
        case EXPR_Not		 :
        case EXPR_And		 :
        case EXPR_Or		 :
        case EXPR_Xor		 :
        case EXPR_Shl		 :
        case EXPR_LShr		 :
        case EXPR_AShr		 :
            asm ("int3") ;
            break ;

        case EXPR_Equal		 :
            exprptr.reset(new EqualExpr(R, size, offset)) ;
            break ;

        case EXPR_Distinct   :
            exprptr.reset(new DistinctExpr(R, size, offset)) ;
            break ;

        case EXPR_Ult		 :
            exprptr.reset(new UltExpr(R, size, offset)) ;
            break ;

        case EXPR_Ule		 :
            exprptr.reset(new UleExpr(R, size, offset)) ;
            break ;

        case EXPR_Ugt		 :
            exprptr.reset(new UgtExpr(R, size, offset)) ;
            break ;

        case EXPR_Uge		 :
            exprptr.reset(new UgeExpr(R, size, offset)) ;
            break ;

        case EXPR_Slt		 :
            exprptr.reset(new SltExpr(R, size, offset)) ;
            break ;

        case EXPR_Sle		 :
            exprptr.reset(new SleExpr(R, size, offset)) ;
            break ;

        case EXPR_Sgt		 :
            exprptr.reset(new SgtExpr(R, size, offset)) ;
            break ;

        case EXPR_Sge		 :
            exprptr.reset(new SgeExpr(R, size, offset)) ;
            break ;

        case EXPR_LOr		 :
        case EXPR_LAnd		 :
        case EXPR_LNot		 :
        case EXPR_SignEXT    :
        case EXPR_ZeroEXT    :
        case EXPR_Shrd       :
            asm ("int3") ;
            break ;
        default :
            break ;
    }
    return exprptr ;
}
*/
