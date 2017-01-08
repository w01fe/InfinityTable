#include <OctoWS2811.h>

const int nStrips = 6;
const int ledsPerStrip = 180;

#define led(row, col) (row * ledsPerStrip + col)
#define lastPixel(row, col, color)  leds.setPixel(led(row, col), color)
#define pixel(row, col, color)  leds.setPixel(led(row, col), color)

#define R(color) ((char)(color >> 16))
#define G(color) ((char)(color >> 8))
#define B(color) ((char)(color))
#define RGB(red, green, blue) ((((char)red) << 16) + (((char)green) << 8) + ((char)blue))

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
//  pingpong();
//  randomBlocks();
  alternatingCheckerboard();
}

void colorWipe(int color)
{
  for (int i=0; i < leds.numPixels(); i++) {
    leds.setPixel(i, color);
  }
}

int interpolateRGB(int c1, int c2, float w, float nw) {
  char r = ((int)(R(c1) * w + R(c2) * nw)) & 255;
  char g = ((int)(G(c1) * w + G(c2) * nw)) & 255;
  char b = ((int)(B(c1) * w + B(c2) * nw)) & 255;
  return RGB(r, g, b);
}

void colorFade(int color, float w) {
  for (int i=0; i < leds.numPixels(); i++) {
    leds.setPixel(i, interpolateRGB(leds.getPixel(i), color, w, 1-w));
  }
}

// Add and saturate
void addPixel(int pixel, int color) {
  leds.setPixel(pixel, interpolateRGB(color, leds.getPixel(pixel), 1, 1));  
}

void addPixel(int row, int col, int color) {
  addPixel(led(row, col), color);
}

// Linear speed bounce from 0 to width-1
int bounce(int x, int width) {
  x = x % ((width - 1) * 2);
  if (x >= width) return (width * 2 - 2 - x);
  else return x;
}


