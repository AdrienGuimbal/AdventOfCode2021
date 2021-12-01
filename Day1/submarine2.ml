let file_name = "input1.txt";;

let get_sum_heights file =
	let rec _get_sum_heights file a b acc =
		try
			let line = input_line file in
			let nb   = int_of_string line in
			_get_sum_heights ( file )( b+nb )( nb )( (a+nb)::acc )
		with e ->
			close_in_noerr file; 
			List.rev acc |> List.tl |> List.tl (* removing the first two sum because they are incomplete *)
	in
	_get_sum_heights file 0 0 []
;;

let elevation lst =
	let rec _elevation lst prev acc =
		match lst with
		| []   -> acc
		| h::t -> _elevation t h (acc + if h>prev then 1 else 0)
	in
	_elevation (List.tl lst) (List.hd lst) 0
;;

let main =
	let file = open_in file_name in
	(* let () = List.iter (Printf.printf "%d ") (get_sum_heights file) in *)
	get_sum_heights file |> elevation |> Printf.printf "Résultat : %i\n"
;;
