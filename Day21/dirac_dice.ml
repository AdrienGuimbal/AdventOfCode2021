let ($$+$$) (x1, y1) (x2, y2) = (x1 + x2, y1 + y2);;
let ($*$$) s (x, y) = (s * x, s * y);;

let rec corr_pos pos =
	((pos - 1) mod 10 ) + 1
and quantum_winner pos1 score1 pos2 score2 player =
	if score1 >= 21 then (
		if score2 >= 21 then print_endline "qsmlkdfqqqqqqqq";
		(1, 0)
	) else if score2 >= 21 then (
		(0, 1)
	) else (
		if player = 1 then (
			      (let npos = corr_pos (pos1 + 3) in 1 $*$$ (quantum_winner (npos) (score1+npos) pos2 score2 2 ) )
			$$+$$ (let npos = corr_pos (pos1 + 4) in 3 $*$$ (quantum_winner (npos) (score1+npos) pos2 score2 2 ) )
			$$+$$ (let npos = corr_pos (pos1 + 5) in 6 $*$$ (quantum_winner (npos) (score1+npos) pos2 score2 2 ) )
			$$+$$ (let npos = corr_pos (pos1 + 6) in 7 $*$$ (quantum_winner (npos) (score1+npos) pos2 score2 2 ) )
			$$+$$ (let npos = corr_pos (pos1 + 7) in 6 $*$$ (quantum_winner (npos) (score1+npos) pos2 score2 2 ) )
			$$+$$ (let npos = corr_pos (pos1 + 8) in 3 $*$$ (quantum_winner (npos) (score1+npos) pos2 score2 2 ) )
			$$+$$ (let npos = corr_pos (pos1 + 9) in 1 $*$$ (quantum_winner (npos) (score1+npos) pos2 score2 2 ) )
		) else (
			      (let npos = corr_pos (pos2 + 3) in 1 $*$$ (quantum_winner pos1 score1 (npos) (score2+npos) 1 ) )
			$$+$$ (let npos = corr_pos (pos2 + 4) in 3 $*$$ (quantum_winner pos1 score1 (npos) (score2+npos) 1 ) )
			$$+$$ (let npos = corr_pos (pos2 + 5) in 6 $*$$ (quantum_winner pos1 score1 (npos) (score2+npos) 1 ) )
			$$+$$ (let npos = corr_pos (pos2 + 6) in 7 $*$$ (quantum_winner pos1 score1 (npos) (score2+npos) 1 ) )
			$$+$$ (let npos = corr_pos (pos2 + 7) in 6 $*$$ (quantum_winner pos1 score1 (npos) (score2+npos) 1 ) )
			$$+$$ (let npos = corr_pos (pos2 + 8) in 3 $*$$ (quantum_winner pos1 score1 (npos) (score2+npos) 1 ) )
			$$+$$ (let npos = corr_pos (pos2 + 9) in 1 $*$$ (quantum_winner pos1 score1 (npos) (score2+npos) 1 ) )
		)
	)
;;

let p1win, p2win = (quantum_winner 6 0 8 0 1);;
let () = Printf.printf "Player1 %i wins ; Player2 %i wins\n" p1win p2win;;
let () = Printf.printf "Résultat pb2 : %i\n" (max p1win p2win);;