use rand::Rng;
use rayon::ThreadPoolBuilder;
use std::time::Instant;

fn parallel_merge_sort<T: Send + Sync + Copy + Ord + Default>(slice: &mut [T]) {
    let len = slice.len();
    if len <= 1 {
        return;
    }

    let mid = slice.len() / 2;

    let (left, right) = slice.split_at_mut(mid);

    rayon::join(|| parallel_merge_sort(left), || parallel_merge_sort(right));

    let mut result = vec![Default::default(); len];
    merge_sorted_arrays(left, right, &mut result);

    slice.copy_from_slice(&result);
}

fn merge_sorted_arrays<T: Copy + Ord + Default>(left: &[T], right: &[T], result: &mut [T]) {
    let mut left_index = 0;
    let mut right_index = 0;

    for i in 0..result.len() {
        if left_index == left.len() {
            result[i] = right[right_index];
            right_index += 1;
        } else if right_index == right.len() {
            result[i] = left[left_index];
            left_index += 1;
        } else if left[left_index] <= right[right_index] {
            result[i] = left[left_index];
            left_index += 1;
        } else {
            result[i] = right[right_index];
            right_index += 1;
        }
    }
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
    let thread_pool = ThreadPoolBuilder::new()
        .num_threads(5) // change the number of threads
        .build()
        .unwrap();

    thread_pool.install(|| {
        parallel_merge_sort(&mut nums);
    });

    let end_time = Instant::now();
    let duration = end_time - start_time;

    println!("Time: {:?}", duration);

}