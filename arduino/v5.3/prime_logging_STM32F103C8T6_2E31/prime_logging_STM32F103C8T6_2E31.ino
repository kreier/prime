/* Prime numbers in Arduino C v5.4 2023/12/14 for STM32F103C8T6 */
#include <time.h>
#include <math.h>
#include <EEPROM.h>

#define END_PRIMES 3540
#define LED_PIN PC13

double start;
int column = 10;
int found = 4;   // we already know 2, 3, 5, 7
int divisors = found;
int last;
uint32_t primes[END_PRIMES] = {3, 5, 7}; // limit due to RAM on F103

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
    if( found > END_PRIMES ) {
      Serial.print("Largest prime that fits into the RAM is ");
      Serial.print(number);
      Serial.print(".\nFor numbers larger than ");
      Serial.print((int)(number*number));
      Serial.print(" to ");
      Serial.print(last);
      Serial.print(" we will use the regular algorithm.");
      break;
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
    if(primes[i] >= largest_divider) // valid for smaller test numbers 
    {
      break;
    }
  }
  // if( flag_prime == 1) && ()
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
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN,LOW);
  for (int i = 0; i < 3; i++) {
    Serial.print(".");
    delay(1000);
  }
  const uint32_t scope[] = {2147483647, 4294967295}; //
  const int reference[] = {105097564, 203280221};    //

  // previous run
  Serial.print("\nResults of previous prime calculations STM32F103C8T6:\n");
  Serial.print("    last        seconds   \n");
  for(int i = 0; i < 2; i++) {
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

  // start calculating just for 2E31 and 2E32
  for (int i = 0; i < 2; i++) 
  {
    last = scope[i];
    found = 4;   // we already know 2, 3, 5, 7
    Serial.println("\n\nPrime v5.4 in Arduino C - 2023/12/18");
    Serial.print("Calculating until ");
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
    for(uint32_t number = largest_divider + 2; number < last; number += 2)
    {
      found += is_prime_fast(number);
      if((millis() - dot) > 1000) {
        Serial.print(".");
        dot = millis();
        column += 1;
        if(column % 2 == 0) {
          digitalWrite(LED_PIN, HIGH);
        }
        else
        {
          digitalWrite(LED_PIN, LOW);
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
//    float duration = (micros() - start)/1000000; // use micros() for more precision in runtimes < 70 minutes
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
      digitalWrite(LED_PIN, HIGH);
      delay(20);     
      digitalWrite(LED_PIN, LOW); 
      delay(30);   
    }
  }
  Serial.print(".\n");
}
