/* Prime numbers in Arduino C v5.4 2023/12/14 for STM32F401CCU6 84 MHz */
#include <time.h>
#include <math.h>
#include <EEPROM.h>

double start;
int column = 10;
int found = 4;   // we already know 2, 3, 5, 7
int divisors = found;
uint32_t primes[3550] = {3, 5, 7};
int led = PC13; // LED_BUILTIN

int is_prime(uint32_t number) {
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

int find_primes(uint32_t limit) {
  for(uint32_t number=11; number < limit + 1; number += 2) { 
    if( is_prime(number) == 1) {
      primes[found - 1] = number;
      found++;
    }
  }
  primes[found - 1] = limit;
  divisors = found - 1;
  return 1;
}

int is_prime_fast(uint32_t number) {
  uint32_t largest_divider = (int)(sqrt(number));
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
  pinMode(led, OUTPUT);
  digitalWrite(led,LOW);
  for (int i = 0; i < 3; i++) {
    Serial.print(".");
    delay(1000);
  }
  const uint32_t scope[] = {100, 1000, 10000, 100000, 1000000, 10000000, 25000000, 100000000, 1000000000, 2147483647, 4294967295 };
  const int reference[] = {25, 168, 1229, 9592, 78498, 664579, 1565927, 5761455, 50847534, 105097564, 203280221};

  // previous run
  Serial.print("\nGet previous results for this STM32F401CCU6:\n");
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

  // start calculating scope 0 to 7 aka 100 to 100 million
  for (int i = 0; i < 8; i++) 
  {
    int last = scope[i];
    found = 4;   // we already know 2, 3, 5, 7
    Serial.println("\n\nPrime v5.4 in Arduino C - 2023/12/17");
    Serial.print("Calculating prime numbers until ");
    Serial.println(last);
    // start = millis();      
    start = micros();        // use micros() for more precision in runtimes < 70 minutes
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
    for(uint32_t number = largest_divider + 2; number < last; number += 2)
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
          elapsed_time((micros()-start)/1000000);
          Serial.print(" - ");
          Serial.print(number);
          Serial.print(" ");
          Serial.print((int)(number / (last / 100)));
          Serial.print("% \n");
        }
      }
    }
    // float duration = (millis() - start)/1000;
    float duration = (micros() - start)/1000000; // use micros() for more precision in runtimes < 70 minutes
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
  Serial.print("\n");

  // start calculating scope 8 to 10 aka 1 billion to 4 billion - now in millis since micros overflows after 71 minutes
  for (int i = 8; i < 11; i++) 
  {
    int last = scope[i];
    found = 4;   // we already know 2, 3, 5, 7
    Serial.println("\n\nPrime v5.4 in Arduino C - 2023/12/17");
    Serial.print("Calculating prime numbers until ");
    Serial.println(last);
    start = millis();      
    // start = micros();        // use micros() for more precision in runtimes < 70 minutes
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
    for(uint32_t number = largest_divider + 2; number < last; number += 2)
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
    float duration = (millis() - start)/1000;
    // float duration = (micros() - start)/1000000; // use micros() for more precision in runtimes < 70 minutes
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
  Serial.print("\n");
}

void loop() {  // program finished, just keep printing some dots
  for(int i = 0; i < 80; i++) {
    Serial.print(".");
    for(int x = 0; x < 100; x++) {
      digitalWrite(led, HIGH);
      delay(20);     
      digitalWrite(led, LOW); 
      delay(30);   
    }
  }
  Serial.print(".\n");
}
