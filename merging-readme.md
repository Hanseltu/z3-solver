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
symbol : niceval   value : 0
```

## Start merging

### Step 1: deal with `Expr.h`

* Replace the original `Expr.h` with the one in the `z3-solver` folder
* Comment the definition of `SYMemObject` (Lines 52-58) in the new `Expr.h`

### Step 2: add the z3 library and include files into the whole project (check the compilation command in `compile.sh` for more detail)

```
g++ -g test-merge.cc Expr.cpp Z3Handler.cpp z3/libz3.so -I ./z3/include -o z3-test
```

### Step 3 : add the following head file and global variable definition in the file which may invoke the solver

```
#include "Expr.h"
#include "Z3Handler.h"
#include <map>

using namespace z3;
using namespace EXPR;
using namespace Z3HANDLER;

z3::context g_z3_context;
z3::solver g_solver(g_z3_context);
```

### Step 4 : invoke `z3-solver` and return a `map` for the further using (add the code, for example, in Lines 76-87, in `test-merge.cc` in target place)

* The constraint `equal_expr` can be replaced with our own
```
Z3Handler *z3_handler_test = new Z3Handler();
expr ret_solver = z3_handler_test->Z3HandlingExprPtr(equal_expr);
g_solver.add(ret_solver);
if (g_solver.check() == unsat){
    std::cout << "The constraints is unsolveable -:)" << std::endl;
}
model m = g_solver.get_model();
std::map<std::string, unsigned long long> ret_result;
ret_result = z3_handler_test->Z3SolveOne(m); // now the [symbolic name, concrete value] map will be returned
for (auto it = ret_result.begin(); it != ret_result.end(); it ++){
    std::cout << "symbol : " << it->first << "   value : " << it->second << std::endl;
}
```


