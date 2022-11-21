#### 20220608


##### change the support of ult, ule, ugt, uge, slt, sle, sgt, sge

##### Three files are required to be modified: please replace the corresponding lines mentioned below

* `Expr.h`
    * Lines 422 - 508 (new definition of those expressions)

* `Z3Handler.h`
    * Lines 67 - 75 (the defintion of the function for handling those expressions)

* `Z3Handler.cpp`
    * Lines 232 - 279 (from `case Expr::Kind::Ult:{ ... }` to `case Expr::Kind::Sge:{ ... }` in the function `Z3Handler::Z3HandlingExprPtr`)
    * Lines 487 - 542 (from the function `Z3Handler::Z3HandleUlt` to the function `Z3Handler::Z3HandleSge`)


#### 20220614

* Remove Lines 53-75 in `Expr.h` and then use it to replace `Expr.h` in your own system

    * Do a testing first to check if replaced `Expr.h` works well


* Replace `Z3Handler.cpp` and `Z3Handler.h`

    * I have added the class definition of `SYMemObject` to `VMState::SYMemObject`, so there will no compiliation errors exist this time


#### 20221004

* Add the one new function definition in Line 38 in `Z3Handler.h`
   * the function `bool Z3ExpressionEvaluator(z3::expr org_expr, z3::expr, z3::expr);`

* Add the function implemented in Lines 74-89 in `Z3Handler.cpp`

* Replace the body of the function `Z3SolveConcritize` implemented in Lines 98-222 in `Z3Handler.cpp`

   *Note that the line number and source file mentioned above are in this repository, you may need to find those files in the `KRover`'s implementation when conducting the merging.*
* https://github.com/Hanseltu/z3-solver/commit/90ca8388d6ff8a528c9c84f047e995f2057129c4


#### 20221022

* Insert one function (`int getSize() {return size;}`) in Line 205 in `Expr.h`
* Modify the size implementation in `Z3Handler::Z3HandleConst` in Lines 474-475 in `Z3Handler.cpp`
* (or check the commit here: https://github.com/Hanseltu/z3-solver/commit/59605d5fbb19ddaf70a68ad29b5a765ebf9b24e3#diff-29840bbe7222209931da38349f5098b73977e4caa744aa48185540693296c636R205 : please ignore other changes as they only for debug purpose)

#### 20221025

* make the changes in two commits in `Expr.h` and `Z3Handler.cpp` below:
   * https://github.com/Hanseltu/z3-solver/commit/9e99ec14a59c73777a9142e9a93860cf62e6110c
   * https://github.com/Hanseltu/z3-solver/commit/22491bded1b94593a062f87c7fcef3fdcc4db360

#### 20221026
* make the changes in the commit in `Expr.h` and `Z3Handler.cpp` below:
   * https://github.com/Hanseltu/z3-solver/commit/92f7cb12e7e4038433c64e0c75feace8d9fafc38


#### 20221121
*  Fix the issue of "Assertion `a.is_bool() && b.is_bool()' failed"
   * replace the implementation of function [`Z3Handler::Z3HandleSign`](https://github.com/Hanseltu/z3-solver/blob/main/Z3Handler.cpp#L713) and [`Z3Handler::Z3HandleNoSign`](https://github.com/Hanseltu/z3-solver/blob/main/Z3Handler.cpp#L727) in `Z3Handler.cpp`
