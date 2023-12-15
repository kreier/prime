# Calculation prime on Arduino UNO, ESP8266 and ESP32 variants

This should be faster than circuitpython or micropython, but the CPUs are much slower, too. Roughly 2 times faster than circuitpython.

|     range | Arduino Uno | esp8266 80 MHz | ESP32-C3 160 MHz | ESP32 240 MHz | ESP32-S3 240 MHz |
|----------:|------------:|---------------:|-----------------:|--------------:|-----------------:|
|       100 |     0.011 s |        0.001 s |          0.001 s |       0.001 s |          0.000 s |
|     1,000 |     0.112 s |        0.014 s |          0.005 s |       0.003 s |          0.003 s |
|    10,000 |     1.747 s |        0.141 s |          0.054 s |       0.029 s |          0.028 s |
|   100,000 |    30.882 s |        1.923 s |          0.616 s |       0.320 s |          0.309 s |
| 1,000,000 |   595.122 s |       31.341 s |          7.614 s |       3.817 s |          3.661 s |

Using this code:

``` c
/* Prime numbers in Arduino C*/
#include <time.h>
#include <math.h>

int last = 1000;

double start;
int column = 10;
int found = 4;   // we already know 2, 3, 5, 7

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.print("\nCalculating prime numbers until ");
  Serial.println(last);
  Serial.println("2, 3, 5, 7, ...");
  start = millis();
  for (int number = 11; number < last; number += 2)
  {
    int prime = 1;
    for (int divider = 3; divider < (int)(sqrt(number)) + 1; divider += 2)
    {
      if (number % divider == 0)
      {
        prime = 0;
        break;
      }
    }
    if (prime ==  1)
    {
      found += 1;
      if (found % 100 == 0) { Serial.print("."); }
      if (found % 10000 == 0) { Serial.println(" "); }
    }
  }
  Serial.print("\nFound ");
  Serial.print(found);
  Serial.print(" prime numbers.\nThis took ");
  Serial.print((millis() - start)/1000);
  Serial.println(" seconds.");
}

void loop() {
  Serial.print(".");
  column += 1;
  if (column % 80 == 0) { Serial.print("\n"); }
  delay(1000);
}
```

## Up to 1 million

I don't print out all results, but every 100th prime number I get a dot. On a ESP8266 after 541.01 seconds I have 78498 dots!

``` c
/* Prime numbers in Arduino C*/
#include <time.h>
#include <math.h>

int last = 1000000;

double start;
int column = 10;
int found = 4;   // we already know 2, 3, 5, 7

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.print("\nCalculating prime numbers until ");
  Serial.println(last);
  Serial.println("2, 3, 5, 7, ...");
  start = millis();
  for (int number = 11; number < last; number += 2)
  {
    int prime = 1;
    for (int divider = 3; divider < (int)(sqrt(number)) + 1; divider += 2)
    {
      if (number % divider == 0)
      {
        prime = 0;
        break;
      }
    }
    if (prime ==  1)
    {
      found += 1;
      if (found % 100 == 0) { Serial.print("."); }
      if (found % 10000 == 0) { Serial.println(" "); }
//      if (column > 0) { Serial.print(", "); }
//      Serial.print(number);
//      column += 3;
//      if (number > 9) { column += 1; }
//      if (number > 99) { column += 1; }
//      if (number > 999) { column += 1; }
//      if (number > 9999) { column += 1; }
//      if (column > 80) { 
//        Serial.println(" "); 
//        column = 0;
//      }      
    }
  }
  Serial.print("\nFound ");
  Serial.print(found);
  Serial.println(" prime numbers.\n");
  Serial.print("This took ");
  Serial.print((millis() - start)/1000);
  Serial.println(" seconds.");
}

void loop() {
  Serial.print(".");
  column += 1;
  if (column % 80 == 0) { Serial.print("\n"); }
  delay(1000);
}

```
