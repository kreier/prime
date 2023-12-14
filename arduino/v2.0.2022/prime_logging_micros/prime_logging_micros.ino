/* Prime numbers in Arduino C v2.0 2023/12/05 */
#include <time.h>
#include <math.h>

double start;
int column = 10;

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
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  for (int i = 0; i < 3; i++) {
    Serial.print(".");
    delay(1000);
  }
  const int scope[] = {100, 1000, 10000, 100000, 1000000, 10000000, 25000000, 100000000, 1000000000};
  const int reference[] = {25, 168, 1229, 9592, 78498, 664579, 1565927, 5761455, 50847534};
  for (int i = 0; i < 9; i++) {
    int last = scope[i];
    int found = 4;   // we already know 2, 3, 5, 7
    Serial.println("\n\nPrime v2.0 in Arduino C 2023/12/05");
    Serial.print("Calculating prime numbers until ");
    Serial.println(last);
    start = micros();      // use micros() for more precision
    int dot = millis();
    int column = 0;
    for (int number = 11; number < last; number += 2) {
      bool prime = true;
      for (int divider = 3; divider < (int)(sqrt(number)) + 1; divider += 2) {
        if (number % divider == 0) {
          prime = false;
          break;
        }
      }
      if (prime) {
        found += 1;
        // if(found % 500 == 0) {
        //   Serial.print(number);
        //   Serial.print(" ");
        // }
        // if(found % 10000 == 0) {
        //   Serial.print(" - ");
        //   elapsed_time(dot/1000);
        //   Serial.print("- ");
        //   Serial.println(number);          
        // }
      }
      if((millis() - dot) > 1000) {
        Serial.print(".");
        dot = millis();
        column += 1;
        if(column % 2 == 0) {
          digitalWrite(LED_BUILTIN, HIGH);
        }
        else
        {
          digitalWrite(LED_BUILTIN, LOW);
        }
        if(column > 40) {
          column = 0;
          elapsed_time((micros() - start)/1000000);
          Serial.print("- ");
          Serial.print(number);
          Serial.print(" ");
          Serial.print(int(number * 100 / last));
          Serial.print("% \n");
        }
      }
    }
    float duration = (micros() - start)/1000000;
    if(duration > 1) {
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
  }
  // program finished, just keep printing some dots
  for(int line = 0; line < 24; line++){
    for(int i = 0; i < 80; i++) {
      Serial.print(".");
      delay(2000);
    }
    Serial.print(".\n");
  }
}
