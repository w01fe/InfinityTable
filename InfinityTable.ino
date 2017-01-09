#include <OctoWS2811.h>

const int nStrips = 6;
const int ledsPerStrip = 180;

#define led(ROW, COL) (ROW * ledsPerStrip + COL)
#define lastPixel(ROW, COL, COLOR)  leds.setPixel(led(ROW, COL), COLOR)
#define pixel(ROW, COL, COLOR)  leds.setPixel(led(ROW, COL), COLOR)

#define R(COLOR) ((char)(COLOR >> 16))
#define G(COLOR) ((char)(COLOR >> 8))
#define B(COLOR) ((char)(COLOR))
#define RGB(RV, GV, BV) ((((char)RV) << 16) + (((char)GV) << 8) + ((char)BV))

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
//  alternatingCheckerboard();
//  test();
  rainbow4(0.01, 100000, 0.3);
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

// like mod but if x is negative always produces number bewteen x and m
int wrap(int x, int m) {
  return ((x % m) + x) % m;
}

// Set a periodic pattern (where period should divide ledsPerStrip)
void periodic(int period, int row, int col, int color) {
  for(int stride = 0; stride < ledsPerStrip; stride += period) {
    pixel(row, col + stride, color);
  }
}

// Set a periodic horizontally symmetric pattern (where period should divide ledsPerStrip/2).
// If period = 6, makes a 4-fold symmetric pattern.
void reflected(int period, int row, int col, int color) {
  for(int stride = 0; stride < ledsPerStrip; stride += period*2) {
    pixel(row, col + stride, color);
    pixel(row, period*2 - 1 - col + stride, color);
  }
}

// Set a periodic pattern with 8-fold symmetry.
// should only be called for col = {1, 2, 3, 3, 2, 1}
void reflected8(int row, int col, int color) {
  int period = 6;
  for(int stride = 0; stride < ledsPerStrip; stride += period) {
    leds.setPixel(row * ledsPerStrip + stride + col, color);
    leds.setPixel((5 - row) * ledsPerStrip + stride + period - 1 - col, color);
    leds.setPixel((5 - col) * ledsPerStrip + stride + row, color);
    leds.setPixel(col * ledsPerStrip + stride + period - 1 - row, color);
    leds.setPixel((5 - row) * ledsPerStrip + stride + col, color);
    leds.setPixel(row * ledsPerStrip + stride + period - 1 - col, color);
    leds.setPixel(col * ledsPerStrip + stride + row, color);
    leds.setPixel((5 - col) * ledsPerStrip + stride + period - 1 - row, color);
    // TODO: why do macros suck?
//    pixel(row, stride + col, color);
//    pixel(period - 1 - row, stride + period - 1 - col, color);
//    pixel(col, stride + period - 1 - row, color);
//    pixel(period - 1 - col, stride + row, color);
  }
}

