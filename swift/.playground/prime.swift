let lastNumber = 1000

print("We calcuate the prime numbers until", terminator: " ")
print(lastNumber)

print("2 3 5 7 11", terminator:" ")

for number in 13 ... lastNumber {
    let upperBound = Int(Double(number).squareRoot())
    var isPrime = 1
    for divisor in 2 ... upperBound {
        let quotient = Double(Double(number) / Double(divisor))
        let rest = quotient - Double(Int(quotient))
        //print(number, divisor, rest)
        if rest == 0 {
            isPrime = 0
            break
        }
    }
    if isPrime == 1 {
        print(number, terminator:" ")
    }
}
