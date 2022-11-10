/* Prime numbers in Arduino C*/
#include <time.h>
#include <math.h>

int last = 100000;

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
  delay(60000);  
}

void loop() {
  Serial.print(".");
  column += 1;
  if (column % 80 == 0) { Serial.print("\n"); }
  delay(2000);
}
