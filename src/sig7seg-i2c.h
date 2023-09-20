#pragma once

/* sig7seg-i2c library by b3nn */

// Uncomment the next line if using with a Particle board
// #include "Particle.h"

#if defined (PARTICLE)
#include <Adafruit_MCP23X17.h>
#else
#include <Wire.h>
#include <Adafruit_MCP23X17.h>
#endif

// This is your main class that users will import into their application
class Sig7segi2c
 {
public:
  void begin(uint8_t addr);
  void begin(void);
  void clear(void);
  void write(int8_t d);
  void setFlipTime(uint8_t millis);
  void setSegments(uint8_t bits);
  void setDash(void);

private:
  uint8_t _fliptime;
  Adafruit_MCP23X17 _mcp;

};
