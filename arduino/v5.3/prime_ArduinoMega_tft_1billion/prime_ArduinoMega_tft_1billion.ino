/* Prime numbers in Arduino C v5.3 2024/01/16 for Arduino Mega 2560 */
// Put results onto the 480x320 TFT screen
// with an estimated time of 120 days it should calculate the prime
// numbers to 1 million (all 50847534). To do so it will first find
// the prime 3632 numbers until 33923 which is slighly larger than
// the square root of 1 billion and use these prime numbers as divisors.

#include <time.h>
#include <math.h>
#include <EEPROM.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <MCUFRIEND_kbv.h>   // Hardware-specific library for 3.5" 480x320 lcd

// Assign human-readable names to some common 16-bit color values:
#define WHITE   0xFFFF
#define BLACK   0x0000
#define GREEN   0x07E0

MCUFRIEND_kbv tft;

double start;
int column = 10;
uint32_t found = 4;   // we already know 2, 3, 5, 7
int8_t divisors = found;
float duration;
long number;
long dot;
uint16_t primes[3402] = {3, 5, 7}; // only 3402 primes to 31623 = sqrt(1,000,000,000)
const int8_t led = LED_BUILTIN; // LED_BUILTIN
const uint32_t scope[]     = {100, 1000, 10000, 100000, 1000000, 10000000, 25000000, 100000000, 1000000000, 2147483647, 4294967295};
const uint32_t nr_primes[] = {25, 168, 1229, 9592, 78498, 664579, 1565927, 5761455, 50847534, 105097564, 203280221}; 
const char*    label[]     = {"100", "1,000", "10,000", "100,000", "1,000,000", "10,000,000", "25,000,000", "100,000,000", "1,000,000,000", "2,147,483,647", "4,294,967,295"};
const uint32_t last = scope[8];

void setup(void) {
  Serial.begin(9600);
  Serial.println("Calculating primes with output on 480x320 lcd");

  // start calculating
  found = 4;   // we already know 2, 3, 5, 7
  Serial.println("\nPrime v5.3");
  Serial.print("Primes until ");
  Serial.println(label[8]);

  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(2);
  tft.fillScreen(BLACK);  
  tft.setTextColor(GREEN, BLACK);
  tft.setTextSize(2);
  tft.setCursor(0, 0);
  tft.println("Calculating to");
  tft.println(label[8]);
  tft.println("Search prime factors");
  Serial.println("Search prime factors");
  start = millis();      // use micros() for more precision - timer starts here **********************
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
  tft.print("Found ");
  tft.print(found);
  tft.println(" primes until ");
  tft.print(largest_divider);
  tft.print(" to use as divisors.\n");
  tft.setCursor(0, 88);
  dot = millis();
  column = 0;
  for(number = largest_divider + 2; number < last; number += 2)
  {
    found += is_prime_fast(number);
    if((millis() - dot) > 5000) {
      Serial.print(".");
      tft.setCursor(column*12, 88);
      tft.print(". ");
      dot = millis();
      column += 1;
      if(column > 24) {
        column = 0;
        update_status((millis() - start)/1000);
      }
    }
  }
  duration = (millis() - start)/1000;
  if(duration > 2) {
    Serial.print("\n");
  }    
  Serial.print("Found ");
  Serial.print(found);
  Serial.print(" prime numbers. It should be ");
  Serial.print(nr_primes[8]);
  Serial.print(".\nThis took ");
  Serial.print(duration, 3);
  Serial.print(" seconds.");
  elapsed_time(duration);
  EEPROM.put(8 * 4 + 1, duration);
}

void loop(void) {
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
  tft.print(hours);
  tft.print("h ");
  tft.print(minutes);
  tft.print("min ");
  tft.print(sec);
  tft.print("s ");
}

void update_status(long s) {
  tft.setCursor(0, 128);
  elapsed_time(s);
  Serial.print(" - ");
  Serial.print(number);
  Serial.print(" ");
  Serial.print((number / (last / 100.0)), 3);
  Serial.print("% \n");
  tft.setCursor(0, 144);
  tft.print("currently at ");
  tft.println(number);
  tft.print("\nProgress: ");
  tft.print((number / (last / 100.0)));
  tft.println("% \n");  
  tft.println("Current estimate:");
  float seconds_estimated = (float)s;
  seconds_estimated *= last;
  seconds_estimated /= (float)number;
  uint16_t days = seconds_estimated / 86400;
  uint16_t hours = seconds_estimated / 3600 - days * 24;
  tft.print(days);
  tft.print("d ");
  tft.print(hours);
  tft.print("h ");
  tft.print((int)(seconds_estimated / 60 - days * 1440 - hours * 60));
  tft.println("min");
  tft.setCursor(0, 88);
}