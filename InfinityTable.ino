#include <OctoWS2811.h>

const int nStrips = 6;
const int ledsPerStrip = 180;

#define led(row, col)  row * ledsPerStrip + col
#define pixel(row, col, color)  leds.setPixel(led(row, col), color)

DMAMEM int displayMemory[ledsPerStrip*nStrips];
int drawingMemory[ledsPerStrip*nStrips];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

void setup() {
  leds.begin();
  leds.show();
}

#define BLACK  0x000000
#define RED    0xFF0000
#define GREEN  0x00FF00
#define BLUE   0x0000FF
#define YELLOW 0xFFFF00
#define PINK   0xFF1088
#define ORANGE 0xE05800
#define WHITE  0xFFFFFF

#define DIM_RED    0x160000
#define DIM_GREEN  0x001600
#define DIM_BLUE   0x000016
#define DIM_YELLOW 0x101400
#define DIM_PINK   0x120009
#define DIM_ORANGE 0x100400
#define DIM_WHITE  0x101010

//int colors[] = {RED, GREEN, BLUE, YELLOW, DIM_RED, DIM_GREEN, DIM_BLUE, DIM_YELLOW};

void loop() {
//  rainbow(40, 0.05, 100000);
//  drawText("cabaaa");
  pingpong();
}

void colorWipe(int color)
{
  for (int i=0; i < leds.numPixels(); i++) {
    leds.setPixel(i, color);
  }
}

