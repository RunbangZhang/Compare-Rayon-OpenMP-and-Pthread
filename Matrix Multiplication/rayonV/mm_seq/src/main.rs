use rand::Rng;
use std::env;
use std::time::Instant;

fn main() {
    let args: Vec<String> = env::args().collect();
    let n: usize = args[1].trim().parse().expect("Invalid Size!");

    let mut rng = rand::thread_rng();

    let mut a: Vec<Vec<i32>> = vec![vec![0; n]; n];
    let mut b: Vec<Vec<i32>> = vec![vec![0; n]; n];
    let mut c: Vec<Vec<i32>> = vec![vec![0; n]; n];

    for i in 0..n {
        for j in 0..n {
            a[i][j] = rng.gen_range(1..101);
            b[i][j] = rng.gen_range(1..101);
        }
    }
    
    let start_time = Instant::now();

    c.iter_mut().enumerate().for_each(|(i, row)| {
        for j in 0..n {
            let mut sum = 0;
            for k in 0..n {
                sum += a[i][k] * b[k][j];
            }
            row[j] = sum;
        }
    });

    let duration = start_time.elapsed();

    println!("Program Time:  {:?}", duration);
}

