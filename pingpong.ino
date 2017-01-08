// set symmetrically

void pingpong() {
  int reps = 5;
  colorWipe(BLACK);
  for(int step = 0; step < 100000; step++) {
    int period = ledsPerStrip / reps;
    for(int i = 0; i < reps; i++) {      
      addPixel(bounce(step + i, 6), (i * period + step) % ledsPerStrip, BLUE);
      addPixel(bounce(step + i + 6, 6), (i * period + step + period/2) % ledsPerStrip, GREEN);
      addPixel(bounce(step + i + 0, 6), ledsPerStrip - (i * period + step + 3 * period/4) % ledsPerStrip, ORANGE);
      addPixel(bounce(step + i + 6, 6), ledsPerStrip - (i * period + step + period/4) % ledsPerStrip, RED);
    }
    leds.show();
    delayMicroseconds(20000);
    colorFade(BLACK, 0.7);
  }
}

