; 
(set-info :status unknown)
(declare-fun niceval () (_ BitVec 32))
(assert
 (and (and true (not (bvugt (bvsub niceval (_ bv2 32)) (_ bv0 32)))) (not (= (bvsub niceval (_ bv2 32)) (_ bv0 32)))))
(check-sat)

