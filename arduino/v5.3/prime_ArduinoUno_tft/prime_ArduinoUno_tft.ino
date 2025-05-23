/* Prime numbers in Arduino C v5.3 2024/01/16 for Arduino Uno */
// Put results onto the TFT screen

#include <time.h>
#include <math.h>
#include <EEPROM.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library for 2.4" 320x240 lcd

#define LCD_CS    A3 // Chip Select goes to Analog 3
#define LCD_CD    A2 // Command/Data goes to Analog 2
#define LCD_WR    A1 // LCD Write goes to Analog 1
#define LCD_RD    A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

double start;
int column = 10;
long found = 4;   // we already know 2, 3, 5, 7
int divisors = found;
int missing = 0;  // not yet calculated values
uint16_t primes[350] = {3, 5, 7}; // only 3402 primes to 31623 = sqrt(1000000000)
const int led = LED_BUILTIN; // LED_BUILTIN
const uint32_t scope[]     = {100, 1000, 10000, 100000, 1000000, 10000000, 25000000, 100000000, 1000000000, 2147483647, 4294967295};
const uint32_t nr_primes[] = {25, 168, 1229, 9592, 78498, 664579, 1565927, 5761455, 50847534, 105097564, 203280221}; 
const char*    label[]     = {"100", "1,000", "10,000", "100,000", "1,000,000", "10,000,000", "25,000,000", "100,000,000", "1,000,000,000", "2,147,483,647", "4,294,967,295"};

void setup(void) {
  Serial.begin(9600);
  Serial.println(F("Calculating primes with output on 320x240 lcd"));
  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(identifier);
  recentResults();
  delay(500);
  Serial.print("calculating missing");
  // start calculating
  for (int i = missing; i < 7; i++) // 9
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
    Serial.print(nr_primes[i]);
    Serial.print(".\nThis took ");
    Serial.print(duration, 3);
    Serial.print(" seconds.");
    elapsed_time(duration);
    EEPROM.put(i * 4 + 1, duration);
  }
  Serial.print("\n");
}

void loop(void) {
}

void recentResults() {
  // previous run
  Serial.print("\nGet previous results for this Arduino Uno:\n");
  Serial.print(" calculated to    time in seconds   \n");
  tft.setRotation(1);
  tft.fillScreen(BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(GREEN); tft.setTextSize(2);
  tft.println("Prime calculations");
  tft.setTextColor(WHITE);  tft.setTextSize(1);
  tft.println("Algorithm v5.0 in C on Arduino Uno\n");
  tft.setTextColor(RED); tft.setTextSize(2);
  tft.println("Recent results:\n");
  tft.setTextColor(YELLOW);
  tft.println("    last       seconds\n");
  tft.setTextColor(WHITE); 
  for(int i = 0; i < 7; i++) {  // 7 is 25 million which is the limit with this algorithm
    int spaces = 12 - strlen(label[i]);
    for(int j = 0; j < spaces; j++) { 
      Serial.print(" ");
      tft.print(" ");
    }
    float last_time_seconds;
    if (last_time_seconds > 0) { missing++; }
    EEPROM.get(i * 4 + 1, last_time_seconds);
    Serial.print(label[i]);
    Serial.print("    ");
    Serial.println(last_time_seconds, 6);
    tft.print(label[i]);
    tft.print("  ");
    tft.println(last_time_seconds, 6);
  }
  delay(10000);
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




















unsigned long testText() {
  tft.fillScreen(BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(WHITE);  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(YELLOW); tft.setTextSize(2);
  tft.println(1234.56);
  tft.setTextColor(RED);    tft.setTextSize(3);
  tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.setTextColor(GREEN);
  tft.setTextSize(5);
  tft.println("Groop");
  tft.setTextSize(2);
  tft.println("I implore thee,");
  tft.setTextSize(1);
  tft.println("my foonting turlingdromes.");
  tft.println("And hooptiously drangle me");
  tft.println("with crinkly bindlewurdles,");
  tft.println("Or I will rend thee");
  tft.println("in the gobberwarts");
  tft.println("with my blurglecruncheon,");
  tft.println("see if I don't!");
  return micros() - start;


  // unsigned long start = micros();


  tft.setTextColor(WHITE);  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(YELLOW); tft.setTextSize(2);
  tft.println(1234.56);
  tft.setTextColor(RED);    tft.setTextSize(3);
  tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.setTextColor(GREEN);
  tft.setTextSize(5);
  tft.println("Groop");
  tft.setTextSize(2);
  tft.println("I implore thee,");
  tft.setTextSize(1);
  tft.println("my foonting turlingdromes.");
  return micros() - start;
}








