// Calculating primes to {last} in Rust v3.0.2023

use std::time::{Instant};

fn is_prime(number: i32) -> i32 {
    let mut prime = 1;
    for divider in (3..((number as f32).sqrt() as i32) + 1).step_by(2)
    {
        if number % divider == 0
        {
            prime = 0;
            break;
        }
    }
    return prime;
}

// This is the main function.
fn main() {
    let last  = 100000000;
    let mut found = 4;   // we already know 2, 3, 5, 7
    // let primes = [2, 3, 5, 7];
    println!("Calculating prime numbers until {last} in Rust v3.0.2023");
    let start = Instant::now();
    for number in (11..last).step_by(2)
    {
        found += is_prime(number);
    }
    let duration = start.elapsed();
    println!("Found {found} prime numbers.");
    println!("This took {:?} seconds.", duration);    
}
