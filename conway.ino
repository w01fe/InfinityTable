boolean isAlive(int row, int col) {
  return !(lastPixel(row,col) == BLACK);
}

int countCell(int row, int col) {
  if (isAlive(row, col)) {
    return 0;
  } else {
    return 1;
  }
}

int neighbors[nStrips][ledsPerStrip];

int numNeighborsHelper(int row, int col) {
  int totalCount = 0;
  for (int r = -1; r <= 1; r++) {
    for (int c = -1; c <= 1; c++) {
      if (!(c == 0 && r == 0)) {
        if (isAlive(wrap(row + r, nStrips), 
                    wrap(col + c, ledsPerStrip))) {
          totalCount += 1;
        }
      }
    }
  }
  return totalCount;
}

void countNeighbors() {
  for (int row=0; row < nStrips; row++) {
    for (int col = 0; col < ledsPerStrip; col++) {
      neighbors[row][col] = numNeighbors(row,col);
    }
  }
}

int numNeighbors(int row, int col) {
  return neighbors[row][col];
}

void evolveCell(int row, int col) {
  int n = numNeighbors(row, col);
  if (isAlive(row,col)) {
    if (n == 2 || n == 3) {
      pixel(row,col,DIM_WHITE);
    } else {
      pixel(row,col,BLACK);
    }
  } else {
    if (n == 3) {
      pixel(row,col,DIM_WHITE);
    } else {
      pixel(row,col,BLACK);
    }
  }
}

void evolve () {
  for (int row=0; row < nStrips; row++) {
    for (int col = 0; col < ledsPerStrip; col++) {
      evolveCell(row,col);
    }
  }
}

void setupGlider() {
  pixel(0,ledsPerStrip/2+1,DIM_WHITE);
  pixel(1,ledsPerStrip/2+2,DIM_WHITE);
  pixel(2,ledsPerStrip/2+0,DIM_WHITE);
  pixel(2,ledsPerStrip/2+1,DIM_WHITE);
  pixel(2,ledsPerStrip/2+2,DIM_WHITE);
}

void conway() {
  setupGlider();
  for (int i = 0; i< 1000000; i++) {
    leds.show();
    delayMicroseconds(2000000);
    countNeighbors();
    evolve();
  }
}
