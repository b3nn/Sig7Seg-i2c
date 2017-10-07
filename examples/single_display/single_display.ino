// Example usage for sig7seg-i2c library by b3nn.
// This will try to include the Adafruit MCP23017 library
// see the README for more info

#include "sig7seg-i2c.h"

// Example using one 7 Segment SIGNALEX display
Sig7segi2c sig;

void setup(){
    sig.begin(0x00);
}


void displayNumbers(Sig7segi2c _sig, int delayTime){
    for(int i=0; i<16; i++){
        // Write the number to the display
        _sig.write(i);
        delay(delayTime);
    }

    // Clear the display for the next item
    _sig.clear(); 
}


void drawEachSegment(Sig7segi2c _sig, int delayTime){
    _sig.clear();
    uint8_t segments = 1;
    
    for(int i=0; i<7; i++){
        // Set the segments we want to show
        _sig.setSegments(segments);
        segments = (segments <<1 ) + 1;
        delay(delayTime);
    }
    
    // Clear the display for the next item
    _sig.clear();
}


void loop(){
    
    // Lets show the number 4 on the display
    sig.write(4);
    delay(1000);
    
    // Lets show the number 2 on the display
    sig.write(2);
    delay(1000);

    // The display can show 0-9 and A-F with 200ms delay
    displayNumbers(sig, 200);
    delay(1000);
    
    // display each segement one at a time with 100ms delay
    drawEachSegment(sig, 100);
    delay(1000);
}
