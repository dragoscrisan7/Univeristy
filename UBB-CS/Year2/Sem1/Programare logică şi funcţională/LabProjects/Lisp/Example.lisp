(defun rmocc(l elem)
	(cond
		((null l) nil)
		((and (atom (car l)) (equal (car l) elem)) (rmocc (cdr l) elem))
		((atom (car l)) (cons (car l) (rmocc (cdr l) elem)))
		(t (cons (rmocc (car l) elem) (rmocc (cdr l) elem)))
	)
)
