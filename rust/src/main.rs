use tokio::time::{Instant};
use std::fs::OpenOptions;
use std::io::Write;

#[tokio::main]
async fn main() {
    let start = Instant::now();

    let array: Vec<_> = (0..1_000_000)
        .map(|i| (i, format!("value_{}", i)))
        .collect();
    let fetch_time = start.elapsed().as_millis();

    // Filtering the array (we need only even ids, and that's the thing ...)
    let start_filter = Instant::now();
    let filtered: Vec<_> = array.into_iter().filter(|(id, _)| id % 2 == 0).collect();
    let filter_time = start_filter.elapsed().as_millis();

    let start_map = Instant::now();
    let mapped: Vec<_> = filtered.into_iter().map(|(_, value)| (value)).collect();
    let map_time = start_map.elapsed().as_millis();

    // Reducing the array (sum the ids)
    let start_reduce = Instant::now();
    let _sum: i64 = mapped.iter().enumerate().map(|(i, _)| i as i64).sum(); // Using i64 here, prevent overflow
    let reduce_time = start_reduce.elapsed().as_millis();

    let output = format!(
        "Rust Benchmark Results:\n\
        Time to fetch: {} ms\n\
        Time to filter: {} ms\n\
        Time to map: {} ms\n\
        Time to reduce: {} ms\n\n",
        fetch_time, filter_time, map_time, reduce_time
    );
    let log_path = "../benchmark.log";
    let mut file = OpenOptions::new().create(true).append(true).open(log_path).unwrap();
    file.write_all(output.as_bytes()).unwrap();

    println!("Rust benchmark results written to benchmark.log");
}