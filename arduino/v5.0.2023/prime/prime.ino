/* Prime numbers in Arduino C v5.0 2023/12/01 */
/* calculate the prime numbers to the square root of the largest number, 
use these prime numbers as dividers for the remaining numbers */
#include <time.h>
#include <math.h>

int last = 1000000000;
double start;
int column = 10;
int found = 4;   // we already know 2, 3, 5, 7
int primes[10000] = {3, 5, 7};

int is_prime(int number) {
  int prime = 1;
  for (int divider = 3; divider < (int)(sqrt(number)) + 1; divider += 2)
  {
    if (number % divider == 0)
    {
      prime = 0;
      break;
    }
  }
  return prime;
}

int find_primes(int limit) {
  for(int number=11; number < limit + 1; number += 2) { 
    if( is_prime(number) == 1) {
      primes[found - 1] = number;
      found++;
    }
  }
  primes[found-1] = limit;
  return 1;
}

int is_prime_fast(int number) {
  int largest_divider = (int)(sqrt(number));
  int flag_prime = 1;
  for(int i=0; i < found; i++)
  {
    if(number % primes[i] == 0) 
    {
      flag_prime = 0;
      break;
    }
    if(primes[i] > largest_divider)
    {
      break;
    }
  }
  return flag_prime;
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  for (int i = 0; i < 3; i++) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\n\nPrime v5.0 2023/12/01");
  Serial.print("Calculating prime numbers until ");
  Serial.println(last);
  start = millis();
  int largest_divider = (int)(sqrt(last)); 
  if(largest_divider % 2 == 0)
  {
    largest_divider += 1;
  }
  find_primes(largest_divider);
  Serial.print("Found ");
  Serial.print(found);
  Serial.print(" primes until ");
  Serial.print(largest_divider);
  Serial.print(" to use as dividers.\n");
  for(int number = largest_divider + 2; number < last; number += 2)
  {
    found += is_prime_fast(number);
  }
  Serial.print("\nFound ");
  Serial.print(found);
  Serial.print(" prime numbers.\nThis took ");
  Serial.print((millis() - start)/1000, 3);
  Serial.println(" seconds.");
  for(int line = 0; line < 24; line++){
    for(int i = 0; i < 80; i++) {
      Serial.print(".");
      delay(10000);
    }
    Serial.print(".\n");
  }
}
