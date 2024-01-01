/* Prime numbers in Arduino C v5.4 2023/12/17 */
/* calculate the prime numbers to the square root of the largest number, 
use these prime numbers as dividers for the remaining numbers */

#include <time.h>
#include <math.h>
#include <ESP_EEPROM.h>

int last = 100000;    // 4294967295   2147483647
double start;
int column = 10;
int found = 4;                 // we already know 2, 3, 5, 7
int primes[6542] = {3, 5, 7};  // for up to 2^32 limit 

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
    if(primes[i] >= largest_divider)
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
  Serial.begin(74880);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  for (int i = 0; i < 3; i++) {
    Serial.print(".");
    delay(1000);
  }
  EEPROM.begin(16);
  Serial.print("\n\nLast calculation was until ");
  uint32_t old_limit;
  EEPROM.get(1, old_limit);
  Serial.print(old_limit);
  Serial.print(" with a time of ");
  float old_time;
  EEPROM.get(5, old_time);
  Serial.print(old_time);
  Serial.print(" seconds.\n");

  // new calculation starts here
  Serial.println("\nPrime v5.3 2023/12/17");
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
  float test;
  for(int number = largest_divider + 2; number < last; number += 2)
  {
    found += is_prime_fast(number);
    if((millis() - dot) > 2000) {
      Serial.print(".");
      dot = millis();
      column += 1;
      if(column % 2 == 0) {
        digitalWrite(LED_BUILTIN, HIGH);
      }
      else
      {
        digitalWrite(LED_BUILTIN, LOW);
      }      
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
  float duration = (millis() - start)/1000;
  Serial.print("\nFound ");
  Serial.print(found);
  Serial.print(" prime numbers.\nThis took ");
  Serial.print(duration, 3);
  Serial.print(" seconds.");
  elapsed_time(duration);
  Serial.print("\n");
  int new_limit = last;
  EEPROM.put(1, new_limit);
  float new_time = duration;
  EEPROM.put(5, new_time);
  column = 0;
  boolean ok1 = EEPROM.commit();
  Serial.println((ok1) ? "New data written.\n" : "Commit failed");
  Serial.print("New data written.\n");
  Serial.print("\n\nLast calculation was until ");
  EEPROM.get(1, old_limit);
  Serial.print(old_limit);
  Serial.print(" with a time of ");
  EEPROM.get(5, old_time);
  Serial.print(old_time);
  Serial.print(" seconds.\n");  
}

void loop() {
  for(int blink=0; blink < 10; blink++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
  Serial.print(".");
  column++;
  if(column > 80) { Serial.print("\n"); column = 0;}
}
