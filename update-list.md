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
