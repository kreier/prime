/* Prime numbers in Arduino C v5.0 2023/12/05 */
/* calculate the prime numbers to the square root of the largest number, 
use these prime numbers as dividers for the remaining numbers */
#include <time.h>
#include <math.h>

int last = 10000000;
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

void elapsed_time(int seconds) {
  int hours = (int)seconds/3600;
  int minutes = (int)(seconds/60 - hours*60);
  int sec = (int)(seconds - minutes*60 - hours*3600);
  Serial.print(" ");
  Serial.print(hours);
  Serial.print("h ");
  Serial.print(minutes);
  Serial.print("min ");
  Serial.print(sec);
  Serial.print("s ");
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  for (int i = 0; i < 3; i++) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\n\nPrime v5.0 2023/12/05");
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
  Serial.print(" to use as divisors.\n");
  int dot = millis();
  int column = 0;
  for(int number = largest_divider + 2; number < last; number += 2)
  {
    found += is_prime_fast(number);
    if((millis() - dot) > 2000) {
      Serial.print(".");
      dot = millis();
      column += 1;
      if(column > 40) {
        column = 0;
        elapsed_time(dot/1000);
        Serial.print(" - ");
        Serial.print(number);
        Serial.print(" ");
        Serial.print((int)number * 100 / last);
        Serial.print("% \n");
      }
    }
  }
  Serial.print("\nFound ");
  Serial.print(found);
  Serial.print(" prime numbers.\nThis took ");
  Serial.print((millis() - start)/1000, 3);
  Serial.print(" seconds.");
  elapsed_time((millis() - start)/1000);
  Serial.print("\n");
  for(int line = 0; line < 24; line++){
    for(int i = 0; i < 80; i++) {
      Serial.print(".");
      delay(10000);
    }
    Serial.print(".\n");
  }
}
