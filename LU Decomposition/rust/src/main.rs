use ndarray::prelude::*;
use rayon::prelude::*;
use ndarray::Zip;
use std::io::{BufRead, BufReader, BufWriter, Error, Write};
use std::fs::File;
use ndarray::Array2;
use std::time::{Duration, Instant};

fn main() {
    let args: Vec<String> = std::env::args().collect();

    if args.len() < 4 {
        println!("Too few arguments!");
        return
    }

    let n:usize = args[1].parse().unwrap();
    let num_threads:usize = args[3].parse().unwrap();

    println!("size: {n}, num_threads:{num_threads}");
    let mut L = Array2::<f64>::zeros((n, n));
    let mut U = Array2::<f64>::zeros((n, n));
    let mut A = Array2::<f64>::zeros((n, n));

    // Read matrix from file

    let reader = BufReader::new(File::open("./lu_input.txt").expect("Cannot open file.txt"));

    let mut i =0;
    let mut j = 0;
    for line in reader.lines() {
        j=0;
        for word in line.unwrap().split_whitespace() {
            A[[i,j]] = word.parse().unwrap();
            // println!("word '{}'", word);
            j+=1;
        }
        i+=1;
    }

    let start = Instant::now();
    LU_factorization(n, &mut A, &mut L, &mut U, num_threads);
    let duration = start.elapsed();

    println!("Time elapsed in sequential is: {:?}", duration);

    rayon::ThreadPoolBuilder::new().num_threads(num_threads).build_global().unwrap();

    let start = Instant::now();
    LU_factorization_parallel(n, &mut A, &mut L, &mut U, num_threads);

    let duration = start.elapsed();

    println!("Time elapsed in parallel is: {:?}", duration);

}


fn LU_factorization(n: usize, A: &mut Array2<f64>, L: &mut Array2<f64>, U: &mut Array2<f64>, num_threads: usize){
    let i: usize =0;
    let j:usize =0;
    let k:usize = 0;

    let mut iter_all:Vec<(usize, usize)> = Vec::new();
    for j in 0..n {
        for i in 0..n{
            iter_all.push((i, j));
        }
    }

    let cols: Vec<(usize,usize, f64)> = iter_all.into_iter().map(|(i, j)| {
        let val = if i == j { 1.0 } else { 0.0 };

        (i,  j, val)
    }).collect();

    for (i,j, val) in cols {
        L[[i,j]] = val;
        U[[i,j]] = 0.0;
    }

    for k in 0..n {
        U[[k,k]] = A[[k,k]];

        let cols: Vec<(usize, f64)> = (k+1..n).into_iter().map(|i| {

            let sub = A[[i,k]]/U[[k,k]];

            (i, sub)
        }).collect();

        for (i, sub) in cols {
            L[[i,k]] = sub;
            U[[k,i]] = A[[k,i]];
        }

        let mut iter_all:Vec<(usize, usize)> = Vec::new();
        for j in k + 1..n {
            for i in k+1..n{
                iter_all.push((i, j));
            }
        }

        let cols: Vec<(usize,usize, f64)> = iter_all.into_iter().map(|(i, j)| {
            let sum = L[[i,k]] * U[[k,j]];

            (i,  j, A[[i, j]] - sum)
        }).collect();

        for (i,j, ai) in cols {
            A[[i,j]] = ai;
        }
    }
}

fn LU_factorization_parallel(n: usize, A: &mut Array2<f64>, L: &mut Array2<f64>, U: &mut Array2<f64>, num_threads: usize) {
    let mut i: usize =0;
    let mut j:usize =0;
    let mut k:usize = 0;

    let mut iter_all:Vec<(usize, usize)> = Vec::new();
    for j in 0..n {
        for i in 0..n{
            iter_all.push((i, j));
        }
    }

    let cols: Vec<(usize,usize, f64)> = iter_all.into_par_iter().map(|(i, j)| {
        let val = if i == j { 1.0 } else { 0.0 };

        (i,  j, val)
    }).collect();

    for (i,j, val) in cols {
        L[[i,j]] = val;
        U[[i,j]] = 0.0;
    }

    for k in 0..n {
        U[[k,k]] = A[[k,k]];

        let cols: Vec<(usize, f64)> = (k+1..n).into_par_iter().map(|i| {

            let sub = A[[i,k]]/U[[k,k]];

            (i, sub)
        }).collect();

        for (i, sub) in cols {
            L[[i,k]] = sub;
            U[[k,i]] = A[[k,i]];
        }

        let mut iter_all:Vec<(usize, usize)> = Vec::new();
        for j in k + 1..n {
            for i in k+1..n{
                iter_all.push((i, j));
            }
        }

        let cols: Vec<(usize,usize, f64)> = iter_all.into_par_iter().map(|(i, j)| {
            let sum = L[[i,k]] * U[[k,j]];

            (i,  j, A[[i, j]] - sum)
        }).collect();

        for (i,j, ai) in cols {
            A[[i,j]] = ai;
        }
    }
}
