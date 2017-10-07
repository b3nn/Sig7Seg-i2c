# sig7seg-i2c

A library for the sig7seg-i2c controller

This library allows you to easily set numbers or segments on displays connected with the sig7seg-i2c controller. There are two versions of the board: one with a breakout for a Particle Photon and one version without. Both support two sets of i2c connections allowing the board to be chained together or be controlled from any microcontroller (such as an Arduino).

![7segwithuno](https://user-images.githubusercontent.com/449841/31311720-50c3250c-ab80-11e7-8966-6e89462dbd3e.jpg)

## Install

For Arduino, click the DOWNLOADS button in the top right corner in GitHub, rename the uncompressed folder *sig7seg-i2c*. Place the *sig7seg-i2c* library folder your <arduinosketchfolder>/libraries/ folder. You may need to create the *libraries* subfolder if its your first library. Restart the IDE. This library also requires the [Adafruit MCP23017 library](https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library)

For Particle boards, this library can be installed via the Library Manager in the Web IDE or via the command line.
```
particle library add sig7seg-i2c
```
Ensure you also have the Adafruit_MCP23017 library installed as well. This should be included automatically if using the Particle web IDE. 
```
particle library add Adafruit_MCP23017
```

## Setup

For non-Photon boards, ensure power, ground, and both i2c line (SDA, SCL) are connected to the sig7seg-i2c board. Connect a 12 volt power supply to the sig7seg-i2c board (it may draw up to 500mA). Ensure the i2c address jumpers are set (more details below in the begin method).


## Usage

You can run the following example to test out all digits on a display:

```
#include "sig7seg-i2c.h"
Sig7segi2c sig;

void setup() {
  sig.begin(0x00);  // All 3 jumper pins at zero will be 0x00
}

void loop() {
  // write from 0 to 9 then A-F on the display
  for(int i=0; i<16; i++){
    sig.write(i);
    delay(100);
  }
}
```

See the [examples](examples) folder for more details.



## Documentation

This code is designed to work with the sig7seg-i2c open source hardware board for electromechanical seven segment displays like Signalex "02L" series flip displays. The board is based on the MCP23017 and requires the awesome [Adafruit MCP23017 library](https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library). 

The sig7seg-i2c library support the methods of other common 7 segment displays. Mainly *begin()* to start the communication bus, *write(int)* to display a number, and *clear()* to hide all segments of the display. The sig7seg-i2c library also includes **setDash()**, **setSegments(uint8_t)** and **setFlipTime(uint8_t)**

### write(int number)
Sets the 7 segment display to the number value passed in. Supports hex values, allowing for 0-16 decimal.

### clear()
Sets all segments of the display to be hidden. 

### setDash()
This will flip the middle 7 segment bar of the display be shown, hiding all other segments. Use **clear()** to flip the segment back off.

### setFlipTime(uint8_t millis)
This will set the length of control pulse time for each segment. The default is 90ms which should support the 4" to 12" displays. However, the 4" can run even faster at 50ms.  

### setSegments(uint8_t bits)
This can be used to set individual segments of the display which is useful when displaying non-numeric values. 

```
    0
    _
5 |   | 1
  |   |
    - <----- 6
4 |   | 2
  | _ |

    3
```
*setSegments(0b00000001)* would set the center top segement to be displayed, while *setSegments(0b00001001)* would set the center top and center bottom segments to be displayed. The MSB of the int is not used since there are only 7 segments of the display.

### begin(uint8_t addr);

Up to 8 boards can be chained together on the same i2c bus. Each board will need the begin method called in the setup along with which i2c address to use. The address pins must have a jumper to pull the address either high or low. The board will not work correctly without these jumpers. The following table maps the pins to the proper address value

| A0 | A1 | A2 | Begin Hex |
|----|----|----|-----------|
|  0 |  0 |  0 |  0x00     |
|  1 |  0 |  0 |  0x01     |
|  0 |  1 |  0 |  0x02     |
|  1 |  1 |  0 |  0x03     |
|  0 |  0 |  1 |  0x04     |
|  1 |  0 |  1 |  0x05     |
|  0 |  1 |  1 |  0x06     |
|  1 |  1 |  1 |  0x07     |


## LICENSE
Copyright 2017 b3nn

Licensed under the MIT license
