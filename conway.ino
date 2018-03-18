bool states[nStrips][ledsPerStrip];
float fade[nStrips][ledsPerStrip];
int neighbors[nStrips][ledsPerStrip];

boolean isAlive(int row, int col) {
  return states[row][col];
}

void setState(int row, int col, bool state) {
  states[row][col] = state;
  if (state) {
    fade[row][col] = 1;
  }
}

int numNeighborsHelper(int row, int col) {
  int totalCount = 0;
  for (int r = -1; r <= 1; r++) {
    for (int c = -1; c <= 1; c++) {
      if (row + r >= 0 && row + r < nStrips &&
        isAlive(wrap(row + r, nStrips),
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

int numAlive() {
  int total = 0;
  for (int row=0; row < nStrips; row++) {
    for (int col = 0; col < ledsPerStrip; col++) {
      states[row][col] && total++;
    }
  }
  return total;
}

int numNeighbors(int row, int col) {
  return neighbors[row][col];
}

void evolveCell(int row, int col) {
  int n = numNeighbors(row, col);
  setState(row, col, isAlive(row,col) ? (n == 2 || n == 3) : n == 3);
}

void evolve () {
  for (int row=0; row < nStrips; row++) {
    for (int col = 0; col < ledsPerStrip; col++) {
      evolveCell(row, col);
    }
  }
}

int simpleShip[][5] = {
  {0, 1, 0, 0, 1},
  {1, 0, 0, 0, 0},
  {1, 0, 0, 0, 1},
  {1, 1, 1, 1, 0}
};

void initShip(int x, int y) {
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 5; col++) {
        setState(y + row, x + col, simpleShip[row][col] == 1);
    }
  }
}

void randomSetup(int color) {
  for (int row = 0; row < nStrips; row++) {
    for (int col = 0; col < ledsPerStrip; col++) {
      if (random(2) == 1) {
        setState(row, col, true);
      }
    }
  }
}

void draw(int color, float fadeSpeed) {
  for (int row=0; row < nStrips; row++) {
    for (int col = 0; col < ledsPerStrip; col++) {
      pixel(row, col, interpolateRGB(color, BLACK, fade[row][col]));
      if (!isAlive(row, col)) {
        fade[row][col] = max(fade[row][col] - fadeSpeed, 0);
      }
    }
  }
}

void conway(int nSteps, int color) {
  randomSetup(color);
  for (int i = 0; i< nSteps; i++) {
    if (i % 100 == 0) {
      countNeighbors();
      evolve();
    }

    if (i % 1000 == 0) {
      initShip(random(ledsPerStrip), random(1));
    }

    draw(color, 0.02);
    leds.show();
    delayMicroseconds(1000000);
  }
}
