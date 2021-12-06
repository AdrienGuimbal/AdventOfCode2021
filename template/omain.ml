let get_lines filename =
	let rec _get_lines file acc =
		try
			let line = input_line file in
			_get_lines file @@ line::acc
		with e ->
			close_in_noerr file;
			List.rev acc
	in
	_get_lines (open_in filename) []
;;

let input = get_lines "input/day2.txt" |> List.map 
	(fun str -> Scanf.sscanf str "%ix%ix%i" 
		(fun l w h -> l, w, h)
	)
;;

(* Problem 1 *)
let () = Printf.printf "Resultat pb1 : %d\n" @@ 0;;
let () = Printf.printf "Resultat pb2 : %d\n" @@ 0;;
