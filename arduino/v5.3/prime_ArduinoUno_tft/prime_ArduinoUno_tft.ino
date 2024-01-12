/* Prime numbers in Arduino C v5.3 2024/01/12 for Arduino Uno */
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
uint16_t primes[3403] = {3, 5, 7}; // only 3402 primes to 31623 = sqrt(1000000000)
const uint32_t scope[] = {100, 1000, 10000, 100000, 1000000, 10000000, 25000000, 100000000, 1000000000, 2147483647, 4294967295};
const long reference[] = {25, 168, 1229, 9592, 78498, 664579, 1565927, 5761455, 50847534, 105097564, 203280221}; 

void setup(void) {
  Serial.begin(9600);
  Serial.println(F("Calculating primes with output on 320x240 lcd"));
  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(identifier);

  recentResults();
  delay(500);
  Serial.println(F("Done!"));
}

void loop(void) {
  recentResults();
  delay(10000);
  for(uint8_t rotation=0; rotation<4; rotation++) {
    tft.setRotation(rotation);
    testText();
    delay(2000);
  }
}

void recentResults() {
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
  tft.setRotation(1);
  tft.fillScreen(BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(YELLOW); tft.setTextSize(2);
  tft.println("Prime calculations");
  tft.setTextColor(WHITE);  tft.setTextSize(1);
  tft.println("Algorithm v5.0 in C on Arduino Uno");
  tft.setTextColor(RED);
  tft.println("Recent results:");

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
}








