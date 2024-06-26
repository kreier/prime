/* Prime numbers in Arduino C v5.3 2023/12/17 for Mega 2560 */
#include <time.h>
#include <math.h>
#include <EEPROM.h>

double start;
int column = 10;
long found = 4;   // we already know 2, 3, 5, 7
int divisors = found;
int primes[3403] = {3, 5, 7}; // only 3402 primes to 31623 = sqrt(1000000000)
int led = LED_BUILTIN; // LED_BUILTIN

int is_prime(long number) {
  int prime = 1;
  for (long divider = 3; divider < (long)(sqrt(number)) + 1; divider += 2)
  {
    if (number % divider == 0)
    {
      prime = 0;
      break;
    }
  }
  return prime;
}

int find_primes(long limit) {
  for(long number=11; number < limit + 1; number += 2) { 
    if( is_prime(number) == 1) {
      primes[found - 1] = number;
      found++;
    }
  }
  primes[found - 1] = limit;
  divisors = found - 1;
  return 1;
}

int is_prime_fast(long number) {
  long largest_divider = (long)(sqrt(number));
  int flag_prime = 1;
  for(int i=0; i < divisors; i++)
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

void elapsed_time(long seconds) {
  long hours = (long)seconds/3600;
  long minutes = (long)(seconds/60 - hours*60);
  long sec = (long)(seconds - minutes*60 - hours*3600);
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
  pinMode(led, OUTPUT);
  for (int i = 0; i < 3; i++) {
    Serial.print(".");
    delay(1000);
  }
  const uint32_t scope[] = {100, 1000, 10000, 100000, 1000000, 10000000, 25000000, 100000000, 1000000000, 2147483647, 4294967295};
  const long reference[] = {25, 168, 1229, 9592, 78498, 664579, 1565927, 5761455, 50847534, 105097564, 203280221};

  // previous run
  Serial.print("\nGet previous results for this Mega2560:\n");
  Serial.print("    last        seconds   \n");
  for(int i = 0; i < 11; i++) {
    int spaces = 12 - (int)log10(scope[i]);
    for(int j = 0; j < spaces; j++) {
      Serial.print(" ");
    }
    Serial.print(scope[i]);
    Serial.print("    ");
    float last_time;
    EEPROM.get(i * 4 + 1, last_time);
    Serial.print(last_time, 6);
    Serial.print("\n");
  }

  // start calculating
  for (int i = 8; i < 10; i++) // only until 1 billion - not enough memory for more primes
  {
    long last = scope[i];
    found = 4;   // we already know 2, 3, 5, 7
    Serial.println("\n\nPrime v5.3 in Arduino C - 2023/12/14");
    Serial.print("Calculating prime numbers until ");
    Serial.println(last);
    start = millis();      
    // start = micros(); // use micros() for more precision in runtimes up to 70 minutes
    long largest_divider = (long)(sqrt(last)); 
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
    long dot = millis();
    int column = 0;
    for(long number = largest_divider + 2; number < last; number += 2)
    {
      found += is_prime_fast(number);
      if((millis() - dot) > 1000) {
        Serial.print(".");
        dot = millis();
        column += 1;
        if(column % 2 == 0) {
          digitalWrite(led, HIGH);
        }
        else
        {
          digitalWrite(led, LOW);
        }
        if(column > 40) {
          column = 0;
          elapsed_time((millis()-start)/1000);
          Serial.print(" - ");
          Serial.print(number);
          Serial.print(" ");
          Serial.print((int)(number / (last / 100)));
          Serial.print("% \n");
        }
      }
    }
    const float duration = (millis() - start)/1000;
    // const float duration = (micros() - start)/1000000; // use micros for hiher precision
    if(duration > 2) {
      Serial.print("\n");
    }    
    Serial.print("Found ");
    Serial.print(found);
    Serial.print(" prime numbers. It should be ");
    Serial.print(reference[i]);
    Serial.print(".\nThis took ");
    Serial.print(duration, 6);
    Serial.print(" seconds.");
    elapsed_time(duration);
    EEPROM.put(i * 4 + 1, duration);
  }
  // preferences.end();
  Serial.print("\n");
}

void loop() {  // program finished, just keep printing some dots
  for(int i = 0; i < 80; i++) {
    Serial.print(".");
    for(int x = 0; x < 100; x++) {
      digitalWrite(led, HIGH);  // turn the LED on (HIGH is the voltage level)
      delay(20);                       // wait for a second
      digitalWrite(led, LOW);   // turn the LED off by making the voltage LOW
      delay(30);   
    }
  }
  Serial.print(".\n");
}
