void pacman(int nSteps) {
  while (nSteps--) {
    int start = random(ledsPerStrip);
    int offset = eating(start);
    victory(start + offset);
  }
}

void victory(int offset) {
  int flashes = 3;
  for (int step = 0; step < (flashes * 2) + 1; step++) {
    colorWipe(BLACK);
    drawWall(step % 2 == 0 ? BLUE : WHITE);
    
    drawPacman(offset, true);
    leds.show();
    delayMicroseconds(800000);
  }
  delayMicroseconds(1500000);
}

int eating(int start) {
  int offset = 0;
  bool mouthOpen = true;
  int dotCount = 30;
  int dotColor = PINK;
  bool stillEating = true;
  
  while (stillEating) {
    colorWipe(BLACK);
    drawWall(BLUE);

    // DOTS
    for (int i = 0; i < dotCount; i++) {
      int mid = start + i * (ledsPerStrip / dotCount);
      if (mid > start + offset) {
        wrappedPixel(0, mid, dotColor);
        wrappedPixel(0, mid + 1, dotColor);
      }
    }

    // PACMAN
    drawPacman(start + offset, mouthOpen);

    if (offset + (ledsPerStrip / dotCount) >= ledsPerStrip) {
      stillEating = false;
    }

    offset = wrap(offset + 1, ledsPerStrip);
    mouthOpen = !mouthOpen;

    leds.show();
    delayMicroseconds(100000);
  }

  return offset;
}

void wrappedPixel(int row, int col, int color) {
  pixel(wrap(row, nStrips), wrap(col, ledsPerStrip), color);
}

void drawWall(int color) {
  for (int i = 0; i < ledsPerStrip; i++) {
    pixel(5, i, color); 
  }
}

void drawPacman(int x, bool mouthOpen) {
    wrappedPixel(0, x - 2, YELLOW);
    wrappedPixel(1, x - 2, YELLOW);
    wrappedPixel(0, x - 1, YELLOW);
    wrappedPixel(1, x - 1, YELLOW);
    wrappedPixel(2, x - 1, YELLOW);
    wrappedPixel(1, x, YELLOW);
    wrappedPixel(2, x, YELLOW);
    wrappedPixel(2, x + 1, YELLOW);

    if (!mouthOpen) {
      wrappedPixel(0, x, YELLOW);
      wrappedPixel(0, x + 1, YELLOW);
      wrappedPixel(1, x + 1, YELLOW);
      wrappedPixel(0, x + 2, YELLOW);
      wrappedPixel(1, x + 2, YELLOW);
    }

}
