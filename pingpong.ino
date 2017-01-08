// set symmetrically

void pingpong() {
  int dir = 1;
  int row = 0;
  int reps = 10;
  int colors[] = {BLUE, RED};
  colorWipe(BLACK);
  for(int step = 0; step < 100000; step++) {
    int period = ledsPerStrip / reps;
    for(int i = 0; i < reps; i++) {      
      pixel(row, (i * period + step) % ledsPerStrip, colors[0]);
      pixel((5 - row), (i * period + step + period/2) % ledsPerStrip, colors[1]);
    }
    row += dir;
    if (row == 0 || row == nStrips - 1) dir *= -1;
    leds.show();
    delayMicroseconds(20000);
    colorFade(BLACK, 0.8);
  }
}

