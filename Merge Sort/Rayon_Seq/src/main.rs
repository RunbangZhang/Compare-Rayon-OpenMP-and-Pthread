use std::time::Instant;
use rand::Rng;
use std::cmp::min;

pub fn merge_sort<T: PartialOrd + Copy>(input: &mut [T]) {
    if input.len() < 2 {return;}
    
    let len = input.len();
    let mid = len / 2;
    merge_sort(&mut input[..mid]);
    merge_sort(&mut input[mid..]);

    let mut tmp = Vec::with_capacity(len);
    let mut i = 0;
    let mut j = mid;

    while i < mid && j < len {
        if input[i] < input[j] {
            tmp.push(input[i]);
            i += 1;
        } else {
            tmp.push(input[j]);
            j += 1;
        }
    }
    if i < mid {
        tmp.extend_from_slice(&input[i..mid]);
    } else if j < len {
        tmp.extend_from_slice(&input[j..len]);
    }

    input.copy_from_slice(&tmp[..]);
}

fn generate_random_array(size: usize) -> [i32; 1000000] { // change the problem size
    let mut rng = rand::thread_rng();
    let mut arr = [0; 1000000]; // change the problem size
    for i in 0..size {
        arr[i] = rng.gen_range(0..10000); 
    }
    arr
}

fn main() {
    let mut nums = generate_random_array(1000000); // change the problem size

    let start_time = Instant::now();

    merge_sort(&mut nums);

    let end_time = Instant::now();
    let duration = end_time - start_time;

    println!("Time: {:?}", duration);
}