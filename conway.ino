boolean isAlive(int row, int col) {
  return !(lastPixel(row,col) == BLACK);
}

int neighbors[nStrips][ledsPerStrip];

int numNeighborsHelper(int row, int col) {
  int totalCount = 0;
  for (int r = -1; r <= 1; r++) {
    for (int c = -1; c <= 1; c++) {
      if (isAlive(wrap(row + r, nStrips),
                    wrap(col + c, ledsPerStrip))) {
        totalCount += 1;
      }
    }
  }
  if (isAlive(row,col)) {
    return totalCount-1;
  } else {
    return totalCount;
  }
}

void countNeighbors() {
  for (int row=0; row < nStrips; row++) {
    for (int col = 0; col < ledsPerStrip; col++) {
      neighbors[row][col] = numNeighborsHelper(row,col);
    }
  }
}

int numNeighbors(int row, int col) {
  return neighbors[row][col];
}

void evolveCell(int row, int col, int color) {
  int n = numNeighbors(row, col);
  if (isAlive(row,col)) {
    if (n == 2 || n == 3) {
      pixel(row,col,color);
    } else {
      pixel(row,col,BLACK);
    }
  } else {
    if (n == 3) {
      pixel(row,col,color);
    } else {
      pixel(row,col,BLACK);
    }
  }
}

void evolve (int color) {
  for (int row=0; row < nStrips; row++) {
    for (int col = 0; col < ledsPerStrip; col++) {
      evolveCell(row,col, color);
    }
  }
}

void setupGlider(int color) {
  pixel(0,ledsPerStrip/2+1,color);
  pixel(1,ledsPerStrip/2+2,color);
  pixel(2,ledsPerStrip/2+0,color);
  pixel(2,ledsPerStrip/2+1,color);
  pixel(2,ledsPerStrip/2+2,color);
}

void randomSetup(int color) {
  for (int row = 0; row < nStrips; row++) {
    for (int col = 0; col < ledsPerStrip; col++) {
      if (random(12) == 2) {
        pixel(row, col, color);
      }
    }
  }
}

void conway(int color) {
  randomSetup(color);
  for (int i = 0; i< 1000000; i++) {
    leds.show();
    delayMicroseconds(20000);
    countNeighbors();
    evolve(color);
  }
}
