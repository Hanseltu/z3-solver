#ifndef _EXPR_H__
#define _EXPR_H__

#include <memory>
#include <stdio.h>

#define EXPR_UNDEFINED   -1

#define EXPR_Add		 7
#define EXPR_Sub		 8
#define EXPR_Mul		 9
#define EXPR_UDiv		 10
#define EXPR_SDiv		 11
#define EXPR_URem		 12
#define EXPR_SRem		 13
#define EXPR_Neg         14
#define EXPR_Not		 15
#define EXPR_And		 16
#define EXPR_Or		     17
#define EXPR_Xor		 18
#define EXPR_Shl		 19
#define EXPR_LShr		 20
#define EXPR_AShr		 21
#define EXPR_Equal		 22
#define EXPR_Distinct    23
#define EXPR_Ult		 24
#define EXPR_Ule		 25
#define EXPR_Ugt		 26
#define EXPR_Uge		 27
#define EXPR_Slt		 28
#define EXPR_Sle		 29
#define EXPR_Sgt		 30
#define EXPR_Sge		 31
#define EXPR_LOr		 32
#define EXPR_LAnd		 33
#define EXPR_LNot		 34

#define EXPR_SignEXT     35
#define EXPR_ZeroEXT     36
#define EXPR_Shrd        37

#define EXPR_Sign           38
#define EXPR_NoSign         39
#define EXPR_Overflow           40
#define EXPR_NoOverflow         41

#define EXPR_Combine        42
#define EXPR_Extract        43

struct SYMemObject {
        std::string name;  // name of object
        unsigned long long addr;        // memory address
        unsigned long long size;        // size in bytes
        // KVExprPtr expr;    // point to a KVExprPtr
        //SYMemObject() : expr(nullptr) {}
    };

namespace EXPR {

class Expr {
    protected:

    public:
        int exprID ;
        int size;
        int offset;

        Expr(int sz, int off=0) {
            this->size = sz, this->offset = off; this->exprID = -1 ;
        }
        Expr() {
            this->size = 4, this->offset = 0; this->exprID = -1 ;
        }
        ~Expr() {} ;
        bool Excute(int &size, long &val) {
            size = this->size ;
            val = 0 ;
            return true ;
        }

        virtual void print(void) {};
        //virtual void print(void) = 0;
};

typedef std::shared_ptr<Expr> ExprPtr;

// User defined expression, usually be a user delcared symbolic object.
class UDefExpr : public Expr {
   protected:
    void *O;

   public:
    UDefExpr(void *obj) :Expr() {
        O = obj;
        //SYMemObject *objj = (SYMemObject*)O;
        //printf("%s\n", objj->name.c_str());
    }
    UDefExpr(void *obj, int sz, int off) : Expr(sz, off) {
        O = obj;
    }

    void print ();
};

class ConstExpr : public Expr {
   protected:
    uint64_t V;

   public:
    ConstExpr(uint64_t value) {
        V = value;
    }

    void print () ;
};

class BinExpr : public Expr {
   protected:
    ExprPtr R, L;

    BinExpr(ExprPtr r, ExprPtr l) : R(r), L(l) {}
    BinExpr(ExprPtr r, ExprPtr l, int sz, int off) : Expr(sz, off), R(r), L(l) {}

   public:
    void print () ;
};

class AddExpr : public BinExpr {
   public:
    AddExpr(ExprPtr r, ExprPtr l) : BinExpr(r, l) {exprID = EXPR_Add;}
    AddExpr(ExprPtr r, ExprPtr l, int sz, int off) : BinExpr(r, l, sz, off) {exprID = EXPR_Add;}
};

class SubExpr : public BinExpr {
   public:
    SubExpr(ExprPtr r, ExprPtr l) : BinExpr(r, l) {exprID = EXPR_Sub;}
    SubExpr(ExprPtr r, ExprPtr l, int sz, int off) : BinExpr(r, l, sz, off) {exprID = EXPR_Sub;}
};

class MulExpr : public BinExpr {
   public:
   // sz is source size.
    MulExpr(ExprPtr r, ExprPtr l) : BinExpr(r, l) {exprID = EXPR_Mul;}
    MulExpr(ExprPtr r, ExprPtr l, int sz, int off) : BinExpr(r, l, sz, off) {exprID = EXPR_Mul;}
};

class DivExpr : public BinExpr {
   public:
    DivExpr(ExprPtr r, ExprPtr l) : BinExpr(r, l) {exprID = EXPR_UDiv;}
    DivExpr(ExprPtr r, ExprPtr l, int sz, int off) : BinExpr(r, l, sz, off) {exprID = EXPR_UDiv;}
};

class AndExpr : public BinExpr {
   public:
    AndExpr(ExprPtr r, ExprPtr l) : BinExpr(r, l) {exprID = EXPR_And;}
    AndExpr(ExprPtr r, ExprPtr l, int sz, int off) : BinExpr(r, l, sz, off) {exprID = EXPR_And;}
};

class OrExpr : public BinExpr {
   public:
    OrExpr(ExprPtr r, ExprPtr l) : BinExpr(r, l) {exprID = EXPR_Or;}
    OrExpr(ExprPtr r, ExprPtr l, int sz, int off) : BinExpr(r, l, sz, off) {exprID = EXPR_Or;}
};

class XorExpr : public BinExpr {
   public:
    XorExpr(ExprPtr r, ExprPtr l) : BinExpr(r, l) {exprID = EXPR_Xor;}
    XorExpr(ExprPtr r, ExprPtr l, int sz, int off) : BinExpr(r, l, sz, off) {exprID = EXPR_Xor;}
};

class Shl_SalExpr : public BinExpr {
   public:
    Shl_SalExpr(ExprPtr r, ExprPtr l) : BinExpr(r, l) {exprID = EXPR_Shl;}
    Shl_SalExpr(ExprPtr r, ExprPtr l, int sz, int off) : BinExpr(r, l, sz, off) {exprID = EXPR_Shl;}
};
class ShrExpr : public BinExpr {
   public:
    ShrExpr(ExprPtr r, ExprPtr l) : BinExpr(r, l) {exprID = EXPR_LShr;}
    ShrExpr(ExprPtr r, ExprPtr l, int sz, int off) : BinExpr(r, l, sz, off) {exprID = EXPR_LShr;}
};

class SarExpr : public BinExpr {
   public:
    SarExpr(ExprPtr r, ExprPtr l) : BinExpr(r, l) {exprID = EXPR_AShr;}
    SarExpr(ExprPtr r, ExprPtr l, int sz, int off) : BinExpr(r, l, sz, off) {exprID = EXPR_AShr;}
};

class iDivExpr : public BinExpr {
   public:
    // r : Dividend, l : Divisor
    iDivExpr(ExprPtr r, ExprPtr l) : BinExpr(r, l) {exprID = EXPR_SDiv;}
    iDivExpr(ExprPtr r, ExprPtr l, int sz, int off) : BinExpr(r, l, sz, off) {exprID = EXPR_SDiv;}
};

class iRemExpr : public BinExpr {
   public:
    iRemExpr(ExprPtr r, ExprPtr l) : BinExpr(r, l) {exprID = EXPR_SRem;}
    iRemExpr(ExprPtr r, ExprPtr l, int sz, int off) : BinExpr(r, l, sz, off) {exprID = EXPR_SRem;}
};

class UryExpr : public Expr {
   protected:
    ExprPtr E;
    UryExpr(ExprPtr e) : E(e) {}
    UryExpr(ExprPtr e, int sz, int off) : Expr(sz, off), E(e) {}

   public:
    virtual void print () ;

};

class NegExpr : public UryExpr {
   public:
    NegExpr(ExprPtr e) : UryExpr(e) {exprID = EXPR_Neg;}
    NegExpr(ExprPtr e, int sz, int off) : UryExpr(e, sz, off) {exprID = EXPR_Neg;}
};

class NotExpr : public UryExpr {
   public:
    NotExpr(ExprPtr e) : UryExpr(e) {exprID = EXPR_Not;}
    NotExpr(ExprPtr e, int sz, int off) : UryExpr(e, sz, off) {exprID = EXPR_Not;}
};

class LNotExpr : public UryExpr {
   public:
    LNotExpr(ExprPtr e) : UryExpr(e) {exprID = EXPR_LNot;}
    LNotExpr(ExprPtr e, int sz, int off) : UryExpr(e, sz, off) {exprID = EXPR_LNot;}
};

class SignExtExpr : public UryExpr {
   public:
    SignExtExpr(ExprPtr e) : UryExpr(e) {exprID = EXPR_SignEXT;}
    SignExtExpr(ExprPtr e, int sz, int off) : UryExpr(e, sz, off) {exprID = EXPR_SignEXT;}
};

class ZeroExtExpr : public UryExpr {
   public:
    ZeroExtExpr(ExprPtr e) : UryExpr(e) {exprID = EXPR_ZeroEXT;}
    ZeroExtExpr(ExprPtr e, int sz, int off) : UryExpr(e, sz, off) {exprID = EXPR_ZeroEXT;}
};

class EqualExpr : public UryExpr {
    public:
        EqualExpr(ExprPtr e) : UryExpr(e) {exprID = EXPR_Equal;}
        EqualExpr(ExprPtr e, int sz, int off) : UryExpr(e, sz, off) {exprID = EXPR_Equal;}
};

class DistinctExpr : public UryExpr {
    public:
        DistinctExpr(ExprPtr e) : UryExpr(e) {exprID = EXPR_Distinct;}
        DistinctExpr(ExprPtr e, int sz, int off) : UryExpr(e, sz, off) {exprID = EXPR_Distinct;}
};

class UltExpr : public UryExpr {
    public:
        UltExpr(ExprPtr e) : UryExpr(e) {exprID = EXPR_Ult;}
        UltExpr(ExprPtr e, int sz, int off) : UryExpr(e, sz, off) {exprID = EXPR_Ult;}
};

class UleExpr : public UryExpr {
    public:
        UleExpr(ExprPtr e) : UryExpr(e) {exprID = EXPR_Ule;}
        UleExpr(ExprPtr e, int sz, int off) : UryExpr(e, sz, off) {exprID = EXPR_Ule;}
};

class UgtExpr : public UryExpr {
    public:
        UgtExpr(ExprPtr e) : UryExpr(e) {exprID = EXPR_Ugt;}
        UgtExpr(ExprPtr e, int sz, int off) : UryExpr(e, sz, off) {exprID = EXPR_Ugt;}
};

class UgeExpr : public UryExpr {
    public:
        UgeExpr(ExprPtr e) : UryExpr(e) {exprID = EXPR_Uge;}
        UgeExpr(ExprPtr e, int sz, int off) : UryExpr(e, sz, off) {exprID = EXPR_Uge;}
};

class SltExpr : public UryExpr {
    public:
        SltExpr(ExprPtr e) : UryExpr(e) {exprID = EXPR_Slt;}
        SltExpr(ExprPtr e, int sz, int off) : UryExpr(e, sz, off) {exprID = EXPR_Slt;}
};

class SleExpr : public UryExpr {
    public:
        SleExpr(ExprPtr e) : UryExpr(e) {exprID = EXPR_Sle;}
        SleExpr(ExprPtr e, int sz, int off) : UryExpr(e, sz, off) {exprID = EXPR_Sle;}
};

class SgtExpr : public UryExpr {
    public:
        SgtExpr(ExprPtr e) : UryExpr(e) {exprID = EXPR_Sgt;}
        SgtExpr(ExprPtr e, int sz, int off) : UryExpr(e, sz, off) {exprID = EXPR_Sgt;}
} ;

class SgeExpr : public UryExpr {
    public:
        SgeExpr(ExprPtr e) : UryExpr(e) {exprID = EXPR_Sge;}
        SgeExpr(ExprPtr e, int sz, int off) : UryExpr(e, sz, off) {exprID = EXPR_Sge;}
} ;

class SignExpr : public UryExpr {
    public:
        SignExpr(ExprPtr e) : UryExpr(e) {exprID = EXPR_Sign;}
        SignExpr(ExprPtr e, int sz, int off) : UryExpr(e, sz, off) {exprID = EXPR_Sign;}
} ;

class NoSignExpr : public UryExpr {
    public:
        NoSignExpr(ExprPtr e) : UryExpr(e) {exprID = EXPR_NoSign;}
        NoSignExpr(ExprPtr e, int sz, int off) : UryExpr(e, sz, off) {exprID = EXPR_NoSign;}
} ;
class OverflowExpr : public UryExpr {
    public:
        OverflowExpr(ExprPtr e) : UryExpr(e) {exprID = EXPR_Overflow;}
        OverflowExpr(ExprPtr e, int sz, int off) : UryExpr(e, sz, off) {exprID = EXPR_Overflow;}
} ;
class NoOverflowExpr : public UryExpr {
    public:
        NoOverflowExpr(ExprPtr e) : UryExpr(e) {exprID = EXPR_NoOverflow;}
        NoOverflowExpr(ExprPtr e, int sz, int off) : UryExpr(e, sz, off) {exprID = EXPR_NoOverflow;}
} ;

class TriExpr : public Expr {
   protected:
    ExprPtr R, M, L;

    TriExpr(ExprPtr r, ExprPtr m, ExprPtr l) : R(r), M(m), L(l) {}
    TriExpr(ExprPtr r, ExprPtr m, ExprPtr l, int sz, int off) : Expr(sz, off), R(r), M(m), L(l) {}

    void print () ;
};

class ShrdExpr :public TriExpr {
    public:
    ShrdExpr(ExprPtr r, ExprPtr m, ExprPtr l) :TriExpr(r, m, l) {exprID = EXPR_Shrd;}
    ShrdExpr(ExprPtr r, ExprPtr m, ExprPtr l, int sz, int off) : TriExpr(r, m, l, sz, off) {exprID = EXPR_Shrd;}
};

class CombineExpr :public BinExpr {
    public:
    int rsz, lsz ;
    // r is high bytes, l is low bytes.
    CombineExpr(ExprPtr r, ExprPtr l, int rsize, int lsize) :BinExpr(r, l) {exprID = EXPR_Combine;rsz=rsize; lsz=lsize;}
    CombineExpr(ExprPtr r, ExprPtr l, int rsize, int lsize, int sz, int off) : BinExpr(r, l, sz, off) {exprID = EXPR_Combine;rsz=rsize; lsz=lsize;}
};
class ExtractExpr : public UryExpr {
    public:
        int s, e;
        ExtractExpr(ExprPtr expr, int start, int end) : UryExpr(expr) {exprID = EXPR_Extract;s=start; e=end;}
        ExtractExpr(ExprPtr expr, int start, int end, int sz, int off) : UryExpr(expr, sz, off) {exprID = EXPR_Extract;s=start; e=end;}

        virtual void print () ;
} ;

};  // namespace EXPR

#endif  // _EXPR_H__
