let file_name = "input.txt";;

let dive1 () =
	let file = open_in file_name in
	let rec _dive1 file depth horiz =
		try
			let elts = String.split_on_char ' ' (input_line file) in
			match elts with
			| direc::number::[] -> begin 
				match direc, int_of_string number with
				| "forward", x -> _dive1 file ( depth ) (horiz+x)
				| "down"   , x -> _dive1 file (depth+x) ( horiz )
				| "up"     , x -> _dive1 file (depth-x) ( horiz )
				| _ -> print_endline "FAIL" ; failwith "WTF"
				end
			| _ -> print_endline "FAIL" ; failwith "WTF"
		with e ->
			close_in_noerr file;
			depth * horiz
	in
	_dive1 file 0 0
;;

let dive2 () =
	let file = open_in file_name in
	let rec _dive1 file depth horiz aim =
		try
			let elts = String.split_on_char ' ' (input_line file) in
			match elts with
			| direc::number::[] -> begin 
				match direc, int_of_string number with
				| "forward", x -> _dive1 file (depth+x*aim) (horiz+x) aim
				| "down"   , x -> _dive1 file depth horiz (aim+x)
				| "up"     , x -> _dive1 file depth horiz (aim-x)
				| _ -> print_endline "FAIL" ; failwith "WTF"
				end
			| _ -> print_endline "FAIL" ; failwith "WTF"
		with e ->
			close_in_noerr file;
			depth * horiz
	in
	_dive1 file 0 0 0
;;

let main =
	dive1 () |> Printf.printf "Résultat pb1 : %i\n";
	dive2 () |> Printf.printf "Résultat pb2 : %i\n"
;;
