void roulette(int nSteps) {  
  // Randomize when it should stop
  int freeSpin = random(200, 500);
  int delayMax = random(200000, 300000);
  
  for(int step = 0; step < nSteps; step++) {
    colorWipe(BLACK);
    drawWheel();

    // Draw ball
    drawColumn(step, 1, DIM_WHITE);

    leds.show();

    int delay = 2000 + (step - freeSpin) * 100 + pow((step - freeSpin), 2) * 0.1 + pow((step - freeSpin), 3) * 0.1;
    if (step < freeSpin) {
      delay = 2000;
    }

    if (delay < delayMax) {
      delayMicroseconds(delay);
    } else {
      // Game is over, flash winning column
      for(int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
          drawColumn(step, 1, WHITE);
        } else {
          drawWheel();
        }
        leds.show();
        
        delayMicroseconds(1000000);
      }
      
      break;
    }
  }
}

void drawWheel() {
  int colors[] = {RED,  LIGHT_BLUE, GREEN, BLUE, ORANGE, PURPLE, YELLOW, PINK, BROWN,};
  int spacing = 10;
  for(int i = 0; i < ledsPerStrip / spacing; i++) {
    drawColumn(i * spacing, 10, colors[i % 9]);
  }
}

