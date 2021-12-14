(* module Set_String = Set.Make(String);;

module Cave = struct 
	type t = string * Set_String.t
	let compare (a,_) (b,_) =
		String.compare a b
	;;
end

module Cave_Set = Set.Make(Cave);; *)



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

let input =
	let parse = get_lines "input/day2.txt" |> List.map 
		(fun str -> Scanf.sscanf str "%s-%s" 
			(fun s1 s2 -> s1, s2)
		)
	in
	let rec _fill_list inp acc =
		match inp with
		| [] -> acc
		| (c1, c2)::t -> _fill_list t (if List.mem h acc then else)
	in
;;

(* Problem 1 *)
let () = Printf.printf "Resultat pb1 : %d\n" @@ 0;;
let () = Printf.printf "Resultat pb2 : %d\n" @@ 0;;
