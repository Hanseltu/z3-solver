## Testing before merging (check whether z3 library can work in the target machine alone)

```
$git clone git@github.com:Hanseltu/z3-solver.git
$cd z3-solver
z3-solver#./compile.sh
z3-solver#./z3-test
```
If everything is ok, the execution will print the messages as follows:
```
ret_udef : niceval
ret_const : #x00000001
ret_add : (bvadd #x00000001 #x00000001)
+++ Original Expression: Sge(Add(1,1))
+++ Original Expression: 
LNot(Ugt(Sub(2,Extract(Combine(0,niceval), 0, 4))))
ret_extract length : (_ BitVec 32)
+++ Original Expression: 
Equal(And(Extract(Combine(0,niceval), 0, 4),Extract(Combine(0,niceval), 0, 4)))
solver: (declare-fun niceval () (_ BitVec 64))
(assert (let ((a!1 (bvugt (bvsub #x00000002
                         ((_ extract 31 0) (concat #x00000000 niceval)))
                  #x00000000))
      (a!2 (= (bvand ((_ extract 31 0) (concat #x00000000 niceval))
                     ((_ extract 31 0) (concat #x00000000 niceval)))
              #x00000000)))
  (and true (not (not a!1)) a!2)))
sat
symbol : niceval   value : 0
checking sat/unsat before concritization: sat
checking sat/unsat after concritization: unsat
result of concritize : 0

```

## Start merging

### Step 1: deal with `Expr.h`

* Replace the original `Expr.h` with the one in the `z3-solver` folder
* Comment the definition of `SYMemObject` (Lines 52-58) in the new `Expr.h`

### Step 2: add the z3 library and include files into the whole project (check the compilation command in `compile.sh` for more detail)

```
g++ -g test-merge.cc Expr.cpp Z3Handler.cpp z3/libz3.so -I ./z3/include -o z3-test
```

### Step 3 : add the following head file in the file which may invoke the solver

```
#include "Expr.h"
#include "Z3Handler.h"
#include <map>

using namespace z3;
using namespace EXPR;
using namespace Z3HANDLER;
```

### Step 4 : invoke `z3-solver` and return a `map` for the further using (add the code, for example, in Lines 76-87, in `test-merge.cc` in target place)

* The constraint `constraints_test` can be replaced with our own
```
Z3Handler *z3_handler_test = new Z3Handler();
std::map<std::string, unsigned long long> ret_result;
ret_result = z3_handler_test->Z3SolveOne(constraints_test); // now the [symbolic name, concrete value] map will be returned
for (auto it = ret_result.begin(); it != ret_result.end(); it ++){
    std::cout << "symbol : " << it->first << "   value : " << it->second << std::endl;
}

// testing concritize function
int value = 1;
bool ret_con = z3_handler_test->Z3SolveConcritize(obj, value, constraints_test);
std::cout << "result of concritize : " << ret_con << std::endl;
```


