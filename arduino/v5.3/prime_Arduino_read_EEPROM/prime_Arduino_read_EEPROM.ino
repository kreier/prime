// read EEPROM for the 11x4 bytes where time is stored as float

#include <EEPROM.h>

const uint32_t scope[] = {100, 1000, 10000, 100000, 1000000, 10000000, 25000000, 100000000, 1000000000, 2147483647, 4294967295};

void setup(void) {
  Serial.begin(9600);  
  Serial.print("\nGet previous results for this Arduino Uno:\n");
  Serial.print("    last         time  \n");
  for(int i = 0; i < 11; i++) {
    int spaces = 10 - (int)log10(scope[i]);
    for(int j = 0; j < spaces; j++) { Serial.print(" "); }
    Serial.print(scope[i]);
    Serial.print("    ");
    float last_time;
    EEPROM.get(i * 4 + 1, last_time);
    Serial.print(last_time, 6);
    Serial.print("\n");
  }  
}

void loop(void) {
}
