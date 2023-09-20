/* sig7seg-i2c library by b3nn */
#include "sig7seg-i2c.h"

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

static const uint8_t numbertable[] = {
  0x3F, /* 0 */
  0x06, /* 1 */
  0x5B, /* 2 */
  0x4F, /* 3 */
  0x66, /* 4 */
  0x6D, /* 5 */
  0x7D, /* 6 */
  0x07, /* 7 */
  0x7F, /* 8 */
  0x6F, /* 9 */
  0x77, /* A */
  0x7C, /* b */
  0x39, /* C */
  0x5E, /* d */
  0x79, /* E */
  0x71, /* F */
};


void Sig7segi2c::begin(uint8_t addr) {
  // MCP code has check to limit the address range
  _mcp.begin_I2C(addr);

  // Sets all the MCP pins to output
  for(int i=0; i<15; i++){
    _mcp.pinMode(i, OUTPUT);
  }

  // Datasheet has 50ms for 4inch and 90ms for 6inch displays
  // http://www.scoretronics.com/components/Digits_Brochure.pdf
  // Change this by calling setFlipTime()
  _fliptime = 90;

}

void Sig7segi2c::begin(void) {
  begin(0);
}

void Sig7segi2c::clear(void) {
  setSegments(0);
}

void Sig7segi2c::setDash(void){
  setSegments(0b01000000);
}

void Sig7segi2c::setFlipTime(uint8_t millis) {
  _fliptime = millis;
}

void Sig7segi2c::write(int8_t d) {
  if (d > 15) return;
  if (d < 0) {
      setDash();
      return;
  }
  setSegments(numbertable[d]);
}


/**
 * Take the 8 bits passed in and shift out the 7 bits for the display.
 * Each segment has an "hide" and "show" wire, so we'll make sure not to set both
 * high at the same time. The "digitalWrite" command is slower than setting all
 * bits at once, but prevents pulling too much current. The delay ensures the
 * solenoid is powered long enough to flip on or off.
 */
void Sig7segi2c::setSegments(uint8_t bits){

    for(int i=0; i<8; i++){
        bool v = (bits & 1);
        bits = bits >> 1;

        int pin_show = i;

        // 4-11 are "show" pins on the hardware controller
        if (i<4) {
            pin_show = i + 8;
        }

        // If wired correctly, the "hide" pin is always 8 away from the "show" pin
        int pin_hide = (pin_show +8) % 16;

        // Sets either the "show" or "hide" to high for a segement
        if(v){
           _mcp.digitalWrite(pin_show, HIGH);
           _mcp.digitalWrite(pin_hide, LOW);
        } else {
           _mcp.digitalWrite(pin_show, LOW);
           _mcp.digitalWrite(pin_hide, HIGH);
        }
    }
    delay(_fliptime);

    // Turn off power for all pins
    for(int i=0; i<16; i++){
        _mcp.digitalWrite(i, LOW);
    }

}
