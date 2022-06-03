; 
(set-info :status unknown)
(declare-fun niceval () (_ BitVec 64))
(assert
 (let (($x16 (and true (not (bvugt (bvsub ((_ extract 31 0) (concat (_ bv1 32) niceval)) (_ bv2 32)) (_ bv0 32))))))
 (and $x16 (not (= (bvsub ((_ extract 31 0) (concat (_ bv1 32) niceval)) (_ bv2 32)) (_ bv0 32))))))
(check-sat)

