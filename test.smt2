; 
(set-info :status unknown)
(declare-fun niceval () (_ BitVec 32))
(assert
 (let (($x15 (and true (bvugt (bvsub ((_ extract 31 0) (concat (_ bv0 32) niceval)) (_ bv2 32)) (_ bv0 32)))))
 (and $x15 (and (distinct (bvsub ((_ extract 31 0) (concat (_ bv0 32) niceval)) (_ bv1 32)) (_ bv0 32)) true))))
(assert
 (= niceval (_ bv0 32)))
(check-sat)

