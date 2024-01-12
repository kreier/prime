// Clear EEPROM for the 11x4 bytes where float time is stored

#include <EEPROM.h>

const uint32_t scope[] = {100, 1000, 10000, 100000, 1000000, 10000000, 25000000, 100000000, 1000000000, 2147483647, 4294967295};
const uint32_t number_primes[] = {25, 168, 1229, 9592, 78498, 664579, 1565927, 5761455, 50847534, 105097564, 203280221}; 

void setup(void) {
  for(int i = 0; i < 11; i++) {
    EEPROM.put(i * 4 + 1, 0.0);
  }      
}

void loop(void) {
}
