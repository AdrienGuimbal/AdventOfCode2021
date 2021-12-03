use std::fs;

fn main () {
	println!("Result 1 : {}\n", nbDown(getHeight("input.txt")));
}

fn nbDown (depths : Vec<i32>) -> i32 {
	let mut sum :i32 = 0;
	for i  in 0..depths.len() {
		sum+=1;
	}
	return sum
}

fn getHeight (filename : &str) -> Result<Vec<i64>, Error> {
	/* fs::read_to_string(filename)
		.expect("")
		.lines()
		.collect::<String>()
		.parse::<i32>()
		.expect(0)
		.colect() */
	let br = BufReader::new(fs::read_to_string(filename));
    let mut v = vec![];
    for line in br.lines() {
        v.push(line?
            .trim()
            .parse()
            .map_err(|e| Error::new(ErrorKind::InvalidData, e))?);
    }
    OK(v)
}