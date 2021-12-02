let file_name = "input.txt";;

let get_heights file =
	let rec _get_heights file acc =
		try
			let line = input_line file in
			_get_heights file @@ (int_of_string line)::acc
		with e ->
			close_in_noerr file; 
			List.rev acc
	in
	_get_heights file []
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
	get_heights file |> elevation |> Printf.printf "Résultat : %i\n"
;;
