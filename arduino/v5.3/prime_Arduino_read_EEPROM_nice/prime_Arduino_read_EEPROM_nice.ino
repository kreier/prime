// read EEPROM for the 11x4 bytes where time is stored as float

#include <EEPROM.h>

const uint32_t scope[]     = {100, 1000, 10000, 100000, 1000000, 10000000, 25000000, 100000000, 1000000000, 2147483647, 4294967295};
const uint32_t nr_primes[] = {25, 168, 1229, 9592, 78498, 664579, 1565927, 5761455, 50847534, 105097564, 203280221}; 
const char*    label[]     = {"100", "1,000", "10,000", "100,000", "1,000,000", "10,000,000", "25,000,000", "100,000,000", "1,000,000,000", "2,147,483,647", "4,294,967,295"};

void setup(void) {
  Serial.begin(9600);  
  Serial.print("\nGet previous results for this Arduino Uno:\n");
  Serial.print(" calculated to    time in seconds   \n");
  for(int i = 0; i < 11; i++) {
    int spaces = 14 - strlen(label[i]);
    for(int j = 0; j < spaces; j++) { Serial.print(" "); }
    Serial.print(label[i]);
    Serial.print("    ");
    float last_time_seconds;
    EEPROM.get(i * 4 + 1, last_time_seconds);
    Serial.println(last_time_seconds, 6);
  }  
}

void loop(void) {
}
