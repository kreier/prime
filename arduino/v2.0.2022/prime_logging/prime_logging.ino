/* Prime numbers in Arduino C v2.0 2023/11/23 */
#include <time.h>
#include <math.h>

double start;
int column = 10;

void setup() {
  Serial.begin(115200);
}

void loop() {
  for (int i = 0; i < 3; i++) {
    Serial.print(".");
    delay(1000);
  }
  const int scope[] = {100, 1000, 10000, 100000, 1000000, 10000000, 25000000, 100000000, 1000000000};
  const int reference[] = {25, 168, 1229, 9592, 78498, 664579, 1565927, 5761455, 50847534};
  for (int i = 0; i < 9; i++)
  {
    int last = scope[i];
    int found = 4;   // we already know 2, 3, 5, 7
    Serial.println("\n\nPrime v2.0 in Arduino C 2023/11/23");
    Serial.print("Calculating prime numbers until ");
    Serial.println(last);
    start = millis();      // use micros() for more precision
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
      //  if (found % 100 == 0) { Serial.print("."); }
      //  if (found % 10000 == 0) { Serial.println(" "); }
      }
    }
    Serial.print("Found ");
    Serial.print(found);
    Serial.print(" prime numbers. It should be ");
    Serial.print(reference[i]);
    Serial.print(".\nThis took ");
    Serial.print((millis() - start)/1000, 3);
    Serial.println(" seconds.");
  }
  for(int line = 0; line < 24; line++){
    for(int i = 0; i < 80; i++) {
      Serial.print(".");
      delay(2000);
    }
    Serial.print(".\n");
  }
}
