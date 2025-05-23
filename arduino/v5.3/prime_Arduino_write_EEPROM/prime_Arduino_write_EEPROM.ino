/* Prime numbers in Arduino C v5.3 2024/01/15 for Arduino Uno */
// code v5.0 is limited to 25 million for Arduino Uno since we can only store 
// less than 750 primes in the limited RAM for this fast algorithm
// but 672 primes are enough since prime #671 is 5009 which is > sqrt(25 million)

#include <time.h>
#include <math.h>
#include <EEPROM.h>

double start;
int column = 10;
long found = 4;   // we already know 2, 3, 5, 7
int divisors = found;
int missing = 0;  // not yet calculated values
int spaces  = 10;
int primes[672] = {3, 5, 7}; // prime #671 is 5009 > sqrt(25 million) 88% RAM used
int primes[6543] = {3, 5, 7}; // for Mega 2560
int led = LED_BUILTIN; // LED_BUILTIN

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  for (int i = 0; i < 3; i++) {
    Serial.print(".");
    delay(1000);
  }
  const long scope[] = {100, 1000, 10000, 100000, 1000000, 10000000, 25000000};
  const long reference[] = {25, 168, 1229, 9592, 78498, 664579, 1565927};
  // const char*    label[] = {"100", "1,000", "10,000", "100,000", "1,000,000", "10,000,000", "25,000,000"};
  // const int label_length[] = {3, 5, 6, 7, 9, 10, 10};

  // previous run
  Serial.print("\nPrevious results Arduino Uno:\n");
  Serial.print("    last        seconds   \n");
  for(int i = 0; i < 11; i++) {
    // spaces = 12 - label_length[i];
    spaces = 11 - (int)log10(scope[i]);
    for(int j = 0; j < spaces; j++) { 
      Serial.print(" ");
    }    
    float last_time;
    if (last_time > 0) { missing++; }    
    EEPROM.get(i * 4 + 1, last_time);
    // Serial.print(label[i]);
    Serial.print(scope[i]);
    Serial.print("    ");
    Serial.print(last_time, 3);
    Serial.print("\n");
  }

  // start calculating
  for (int i = missing; i < 11; i++) // can only go to 25 million
  {
    long last = scope[i];
    found = 4;   // we already know 2, 3, 5, 7
    Serial.println("\n\nPrime v5.3");
    Serial.print("Primes until ");
    Serial.println(last);
    start = millis();      // use micros() for more precision
    // Serial.println(start/1000000, 6);
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
          elapsed_time(dot/1000);
          Serial.print(" - ");
          Serial.print(number);
          Serial.print(" ");
          Serial.print((int)(number / (last / 100)));
          Serial.print("% \n");
        }
      }
    }
    const float duration = (millis() - start)/1000;
    if(duration > 2) {
      Serial.print("\n");
    }    
    Serial.print("Found ");
    Serial.print(found);
    Serial.print(" prime numbers. It should be ");
    Serial.print(reference[i]);
    Serial.print(".\nThis took ");
    Serial.print(duration, 3);
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
      digitalWrite(led, HIGH);  // turn the LED on (HIGH is the voltage level)
      delay(20);                       // wait for a second
      digitalWrite(led, LOW);   // turn the LED off by making the voltage LOW
      delay(30);   
    }
  }
  Serial.print(".\n");
}

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


