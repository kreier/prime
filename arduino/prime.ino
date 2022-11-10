/* Prime numbers in Arduino C*/
#include <time.h>
#include <math.h>

int last = 10000;

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
    bool prime = true;
    for (int divider = 3; divider < (int)(sqrt(number)) + 1; divider += 2)
    {
      if (number % divider == 0)
      {
        prime = false;
        break;
      }
    }
    if (prime)
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
