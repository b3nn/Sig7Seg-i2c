// Example usage for sig7seg-i2c library by b3nn.
// This will try to include the Adafruit MCP23017 library
// see the README for more info

#include "sig7seg-i2c.h"

// Example using four 7 Segment SIGNALEX displays
Sig7segi2c sig1;
Sig7segi2c sig2;
Sig7segi2c sig3;
Sig7segi2c sig4;

void setup(){
    // Each controller should have its own i2c address set
    sig1.begin(0x03);
    sig2.begin(0x02);
    sig3.begin(0x01);
    sig4.begin(0x00);
    
    // The 4 inch display can flip faster than the 6 inch ones
    // Set the flip time to a 50ms delay
    sig1.setFlipTime(50);
    sig2.setFlipTime(50);
    sig3.setFlipTime(50);
    sig4.setFlipTime(50);
}


void clear(){
    sig1.clear();
    sig2.clear();
    sig3.clear();
    sig4.clear();
}


void flipTenThousand(int delayTime){
    for(int a=0; a<10; a++){
        sig1.write(a);
        sig2.write(a);
        sig3.write(a);
        sig4.write(a);
        delay(delayTime);
    }
}


void countToTenThousand(){
    for(int a=0; a<10; a++){
        sig4.write(a);
        for(int b=0; b<10; b++){
            sig3.write(b);
            for(int c=0; c<10; c++){
                sig2.write(c);
                for(int d=0; d<10; d++){
                    sig1.write(d);
                }
            }
        }
    }
}


void drawEachSegment(Sig7segi2c sig, int delayTime){
    sig.clear();
    uint8_t segments = 1;
    
    for(int i=0; i<7; i++){
        sig.setSegments(segments);
        segments = (segments <<1 ) + 1;
        delay(delayTime);
    }
    
}


void loop(){
    
    // Flip all displays to the same number, then do it faster
    flipTenThousand(300);
    flipTenThousand(150);
    flipTenThousand(0);
    clear();
    
    // Flip on each segment one at a time on each display with 100ms delay
    drawEachSegment(sig1, 100);
    sig1.clear();
    drawEachSegment(sig2, 100);
    sig2.clear();
    drawEachSegment(sig3, 100);
    sig3.clear();
    drawEachSegment(sig4, 100);
    sig4.clear();

    // Use all 4 displays to count up to 9999 (will take a while)
    countToTenThousand();
    clear();

}

