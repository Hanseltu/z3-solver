#ifndef _Z3HANDLER_H__
#define _Z3HANDLER_H__


/* @THX class for transfer constraint
 *
 *
*/


#include"z3++.h"
#include "Expr.h"

using namespace z3;
class Z3Handler{
public:
    Z3Handler(){}
    virtual ~Z3Handler(){}

    // handle different expressions
    z3::expr Z3HandleAdd();



};


#endif  // end of _Z3HANDLER_H__
