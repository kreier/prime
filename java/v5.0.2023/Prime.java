class divisor {
  public static int[] primes = new int[1000];
  public static int found = 4;
  public static int divisors;
}

class prime {
  public static int is_prime(int number) {
    int flag_prime = 1;
    for(int divider = 3; divider < (int) Math.sqrt(number) + 1; divider = divider + 2) {
      if(number % divider == 0) {
        flag_prime = 0;
        break;
      }
    }
    return flag_prime;
  }

  public static void find_primes(int limit) {
    divisor.primes[0] = 3;
    divisor.primes[1] = 5;
    divisor.primes[2] = 7; 
    divisor.divisors = 3;
    for(int number = 11; number <= limit; number = number + 2) {
      if(is_prime(number) > 0) {
        divisor.found++;
        divisor.primes[divisor.found - 2] =  number;
      }
    }
    divisor.divisors = divisor.found - 1;
  }

  public static int is_prime_fast(int number) {
    int largest_divider = (int)Math.sqrt(number);
    int flag_prime = 1;
    for(int i = 0; i < divisor.divisors; i++) {
      if(number % divisor.primes[i] == 0) {
        flag_prime = 0;
        break;
      }
      if(divisor.primes[i] > largest_divider)
      {
          break;
      }
    }
    return flag_prime;
  }

  public static void main(String[] args) {
    int last = 10000000;
    System.out.println("Calculation prime numbers to " + last + " in Java v5.0.2023.");
    long start = System.nanoTime();
    int limit = (int)Math.sqrt(last);
    if(limit % 2 == 0) {
      limit++;
    }
    System.out.print("Find primes numbers to " + limit + ". ");
    find_primes(limit);
    System.out.println("Found " + divisor.found + " primes. Now using them as divisors.");

    for(int number = limit + 2; number < last; number = number + 2) {
      divisor.found += is_prime_fast(number);
    }
    long end = System.nanoTime();
    System.out.print("I found " + divisor.found + " prime numbers. ");
    System.out.print("This took me " + ((end - start) / 1000000000.0) + " seconds.");
  }
}
