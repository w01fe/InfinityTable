void dicks(int nSteps) {
  
  int dickCount = 9;  
  int dickLengths[] = {15, 20, 18, 20, 25, 10, 30, 20, 12};
  int dickColors[] = {PINK, WHITE, BROWN, PINK, BROWN, PINK, 0x4C3434, WHITE, BROWN};
  int dickThicknesses[] = {1, 2, 2, 3, 2, 2, 2, 1, 3};

  
  for(int step = 0; step < nSteps; step++) {
    colorWipe(BLACK);

    int offset = 0;
    int spacing = 1;
    for (int i = 0; i < dickCount; i++) {
      int length = min(10 + (step % dickLengths[i]), dickLengths[i]);
      drawDick(step + offset, length, dickThicknesses[i], dickColors[i]);
       
      offset += dickLengths[i] + spacing;
    }
    leds.show();

    delayMicroseconds(100000);
  }
}


// Draw a dick
void drawDick(int col, int length, int thickness, int color) {

  // shaft
  for (int columnCount = 0; columnCount < length - 2; columnCount++) {
    for (int i=0; i < thickness; i++) {
      pixel(i, (col + columnCount) % ledsPerStrip, color);
    }
  }

  // head
  int headColor = interpolateRGB(color, PINK, 0.5, 0.5);
  pixel(0, (col + length - 1) % ledsPerStrip, headColor);
  pixel(0, (col + length - 2) % ledsPerStrip, headColor);
  pixel(1, (col + length - 2) % ledsPerStrip, headColor);
  pixel(1, (col + length - 3) % ledsPerStrip, headColor);
  pixel(2, (col + length - 3) % ledsPerStrip, headColor);

  if (thickness == 3) {
    pixel(3, (col + length - 4) % ledsPerStrip, headColor);
  }

  // balls
  int ballColor = interpolateRGB(color, BLACK, 0.25, 0.9);
  pixel((thickness - 2), (col + 1) % ledsPerStrip, ballColor);
  pixel((thickness - 2), (col + 2) % ledsPerStrip, ballColor);
  pixel((thickness - 1), col % ledsPerStrip, ballColor);
  pixel((thickness - 1), (col + 1) % ledsPerStrip, ballColor);
  pixel((thickness - 1), (col + 2) % ledsPerStrip, ballColor);
  pixel((thickness - 1), (col + 3) % ledsPerStrip, ballColor);
  pixel(thickness, col % ledsPerStrip, ballColor);
  pixel(thickness, (col + 1) % ledsPerStrip, ballColor);
  pixel(thickness, (col + 2) % ledsPerStrip, ballColor);
  pixel(thickness, (col + 3) % ledsPerStrip, ballColor);
  pixel((thickness + 1), (col + 1) % ledsPerStrip, ballColor);
  pixel((thickness + 1), (col + 2) % ledsPerStrip, ballColor);
}
