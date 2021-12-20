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

(* let input = get_lines "input/day2.txt" |> List.map 
	(fun str -> Scanf.sscanf str "%ix%ix%i" 
		(fun l w h -> l, w, h)
	)
;; *)

let error_score line =
	let len = String.length line in
	let rec _error_code i prev =
		if i = len then 0 else
		match line.[i], List.hd prev with
		| '(', _ | '[', _ | '{', _ | '<', _ -> _error_code (i+1) (line.[i]:: prev)
		| ')', '(' | ']', '[' | '}', '{' | '>', '<' -> _error_code (i+1) (List.tl prev)
		| s, _ -> match s with
			| ')' -> 3
			| ']' -> 57
			| '}' -> 1197
			| '>' -> 25137
			| _ -> failwith "WTF"
	in
	_error_code 0 [' ']
;;

let rec pb1 lst = 
	match lst with
	| [] -> 0
	| h::t -> (error_score h) + (pb1 t)
;;

let corec_score line =
	let len = String.length line in
	let rec get_score to_close score =
		match to_close with
		| [' '] -> score
		| '('::t -> get_score t (1 + 5*score)
		| '['::t -> get_score t (2 + 5*score)
		| '{'::t -> get_score t (3 + 5*score)
		| '<'::t -> get_score t (4 + 5*score)
		| _ -> failwith "WTF"
	in
	let rec _correc_score i prev =
		if i = len then get_score prev 0 else
		match line.[i], List.hd prev with
		| '(', _  | '[',  _ | '{',  _ | '<', _  -> _correc_score (i+1) (line.[i]:: prev)
		| ')','(' | ']','[' | '}','{' | '>','<' -> _correc_score (i+1) (List.tl prev)
		| _ -> failwith "wtf"
	in
	_correc_score 0 [' ']
;;

let rec incomplete lst =
	match lst with
	| [] -> []
	| h::t -> if error_score h = 0 then h::(incomplete t)
			  else incomplete t
;;

let pb2 lst =
	let rec _pb2 lst scores =
		match lst with
		| [] -> List.nth (List.sort Int.compare scores) ((List.length scores) / 2)
		| h::t -> _pb2 t ((corec_score h)::scores)
	in
	_pb2 (incomplete lst) [] 
;;

(* Problem 1 *)
let () = Printf.printf "Resultat pb1 : %d\n" @@ pb1 (get_lines "input.txt");;
let () = Printf.printf "Resultat pb2 : %d\n" @@ pb2 (get_lines "input.txt");;
