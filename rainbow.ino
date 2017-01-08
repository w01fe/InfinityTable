/*  OctoWS2811 BasicTest.ino - Basic RGB LED Test
    http://www.pjrc.com/teensy/td_libs_OctoWS2811.html
    Copyright (c) 2013 Paul Stoffregen, PJRC.COM, LLC
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
  Required Connections
  --------------------
    pin 2:  LED Strip #1    OctoWS2811 drives 8 LED Strips.
    pin 14: LED strip #2    All 8 are the same length.
    pin 7:  LED strip #3
    pin 8:  LED strip #4    A 100 ohm resistor should used
    pin 6:  LED strip #5    between each Teensy pin and the
    pin 20: LED strip #6    wire to the LED strip, to minimize
    pin 21: LED strip #7    high frequency ringining & noise.
    pin 5:  LED strip #8
    pin 15 & 16 - Connect together, but do not use
    pin 4 - Do not use
    pin 3 - Do not use as PWM.  Normal use is ok.
  This test is useful for checking if your LED strips work, and which
  color config (WS2811_RGB, WS2811_GRB, etc) they require.
*/

#include <OctoWS2811.h>

const int nStrips = 8;
const int ledsPerStrip = 180;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

void setup() {
  leds.begin();
  leds.show();
}

/*
#define RED    0xFF0000
#define GREEN  0x00FF00
#define BLUE   0x0000FF
#define YELLOW 0xFFFF00
#define PINK   0xFF1088
#define ORANGE 0xE05800
#define WHITE  0xFFFFFF
*/

// Less intense...

#define RED    0x160000
#define GREEN  0x001600
#define BLUE   0x000016
#define YELLOW 0x101400
#define PINK   0x120009
#define ORANGE 0x100400
#define WHITE  0x101010

char font[] = {
  14, 17, 31, 17, 17,
  30, 17, 30, 17, 30,
  15, 16, 16, 16, 15
};

void loop() {
  // int microsec = 2000000 / leds.numPixels();  // change them all in 2 seconds

  // uncomment for voltage controlled speed
  // millisec = analogRead(A9) / 40;
//  int colors[] = {0xFF, 0xFF00, 0xFF0000, 0xFFFF00, 0xFF00FF, 0x00FFFF, 0x000011, 0x111111};
//  for(int i = 0; i < 8; i++) {
//    for (int j = 0; j < 180; j++) {
//      leds.setPixel(i * 180 + j, 0);
//    }
//    for (int j = 0; j < 180; j += (i + 1)) {
//      leds.setPixel(i * 180 + j, colors[i]);
//    }
//  }
//  leds.show();
  rainbow(60, 0.05, 100000);
//  drawText("cabaaa");
}

void drawText(const char s[]) {
  for(int i = 0; i < leds.numPixels(); i++) leds.setPixel(i, 0);
  int p = 0;
  for(const char *c = s; *c; c++) {
    for(int i = 0; i < 5; i++) {
      char row = font[*c - 'a' + i];
      for(int j = 0; j < 5; j++) {
        if (row % 2 == 1) leds.setPixel((i + 1) * ledsPerStrip + p + 4 - j, 0xFF0000);
        row /= 2;
      }
    }
    p += 6;
  }
  leds.show();
}

int rainbowColor(float f) {
  float c = 3 * fmod(f + 1000000.0, 1.0);
  int res = 0;
  for (int cutoff = 0; cutoff < 3; cutoff++) {
    float rc = (cutoff == 0 && c > 1) ? c - 3 : c;
    res = res * 256 + max(0, (int)(255 * (1 - abs(rc - cutoff))));
  }
  return res;
}

void rainbow(int period, float quantum, int nSteps) {
  for (int s=0; s < nSteps; s++) {
    for (int strip = 0; strip < nStrips; strip++) {
      for (int i=0; i < ledsPerStrip; i++) {
        // (strip % 2 == 0 ? -1 : 1)
         leds.setPixel(strip * ledsPerStrip + i, rainbowColor(((float)i / period) + (strip / 10.0) - s * quantum));
      }
      leds.show();
      //delayMicroseconds(delayMs);
    }
  }
}

void colorWipe(int color, int wait)
{
  for (int i=0; i < leds.numPixels(); i++) {
    leds.setPixel(i, color);
    //delayMicroseconds(1);
  }
    leds.show();
    delayMicroseconds(1000000);
}

