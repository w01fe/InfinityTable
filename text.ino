char font[] = {
  14, 17, 31, 17, 17,
  30, 17, 30, 17, 30,
  15, 16, 16, 16, 15
};

void drawText(const char s[]) {
  colorWipe(BLACK);
  int p = 0;
  for(const char *c = s; *c; c++) {
    for(int i = 0; i < 5; i++) {
      char column = font[*c - 'a' + i];
      for(int j = 0; j < 5; j++) {
        if (column % 2 == 1) pixel(i + 1, p + 4 - j + 90, RED);
        column /= 2;
      }
    }
    p += 6;
  }
  leds.show();
}

