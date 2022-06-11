; 
(set-info :status unknown)
(declare-fun niceval () (_ BitVec 32))
(assert
 (let ((?x9 (concat niceval (_ bv0 32))))
 (let ((?x10 ((_ extract 63 32) ?x9)))
 (let (($x13 (bvugt ?x10 (_ bv2 32))))
 (and true $x13)))))
(assert
 (= niceval (_ bv200 32)))
(assert
 (= niceval (_ bv200 32)))
(check-sat)


