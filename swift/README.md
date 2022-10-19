# Calculating prime numbers in Swift

My first attempt was rather slow and would work only for up to 3659 and then crash with a stack overflow. Up to 1000 it finds the 169 prime numbers in 0.78 seconds:

``` swift
import UIKit

let lastNumber = 1000
var count = 2
var prime = true
var startTime = NSDate()

print("We calcuate the prime numbers until", lastNumber, "\n")
print("\n2", terminator:" ") // check divisors until 1 smaller than number
for number in 3 ... lastNumber {
    prime = true
    for divisor in 2 ... number - 1 { // exclude number as divisor
        let quotient = Double(Double(number) / Double(divisor))
        let rest = quotient - Double(Int(quotient))
        if rest == 0 {
            prime = false
            break
        }
    }
    if prime {
        print(number, terminator:" ")
        count += 1
    }
}

var stopTime = NSDate()
var interval = stopTime.timeIntervalSince(startTime as Date)
print("\n\nThis calculation took", interval,"seconds.")
print("I found", count, "prime numbers.")
```
## Progress - 123x speed increase!

Over a cycle of 8 iterations the code progressed as following, starting with the time for prime numbers to 10,000:

- v1 crashes with stack overflow because divisor gets too large
- v2 1.29 seconds - divisor only until squareroot of number
- v3 0.71 seconds - move to SwiftUI, removed remaining calculation step
- v4 0.63 seconds - only odd numbers from 5 on
- v5 0.62 seconds - start with 11 and divider 3 (no even numbers)
- v6 0.34 seconds - only odd dividers from 3 on
- v7 0.06 seconds - using modulus % operator

Being so fast we check the time until 100,000 (9592) and 1,000,000 (78,498)

- v7 0.67 sec - 1,000,000 crashes with 78 GBytes of RAM utilization
- v8 0.59 sec - not printing the result, and 7.19 seconds for 1,000,000

``` swift
import SwiftUI

let lastNumber = 1000000
var count = 4 // start from 11, know 2, 3, 5, 7
var prime = true
var startTime = NSDate()

print("We calcuate the prime numbers until", lastNumber, "\n")
print("\n2 3 5 7", terminator:" ") // because upper limit divisor
for number in stride(from: 11, through: lastNumber, by: 2) {
    prime = true
    for divisor in stride(from: 3, through: Int(Double(number).squareRoot()), by: 2) { 
        if number % divisor == 0 {
            prime = false
            break
        }
    }
    if prime {
//        print(number, terminator:" ")
        count += 1
    }
}

var stopTime = NSDate()
var interval = stopTime.timeIntervalSince(startTime as Date)
print("\n\nThis calculation took", interval,"seconds.")
print("I found", count, "prime numbers.")

```
