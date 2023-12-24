// The Swift Programming Language
// https://docs.swift.org/swift-book

let lastNumber = 1000000
var count = 4 // start from 11, know 2, 3, 5, 7
var prime = true
let clock = ContinuousClock()
let result = clock.measure {
    print("We calcuate the prime numbers until", lastNumber, "\n")
    // print("\n2 3 5 7", terminator:" ") // because upper limit divisor
    for number in stride(from: 11, through: lastNumber, by: 2) {
        prime = true
        for divisor in stride(from: 3, through: Int(Double(number).squareRoot()), by: 2) { 
            if number % divisor == 0 {
                prime = false
                break
            }
        }
        if prime {
            count += 1
        }
    }
}
// var stopTime = NSDate()
// var interval = stopTime.timeIntervalSince(startTime as Date)
print("This calculation took", result,"seconds.")
print("I found", count, "prime numbers.")
