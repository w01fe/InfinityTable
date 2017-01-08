char font[] = {
  14, 17, 31, 17, 17,
  30, 17, 30, 17, 30,
  15, 16, 16, 16, 15
};

void drawText(const char s[]) {
  for(int i = 0; i < leds.numPixels(); i++) leds.setPixel(i, 0);
  int p = 0;
  for(const char *c = s; *c; c++) {
    for(int i = 0; i < 5; i++) {
      char row = font[*c - 'a' + i];
      for(int j = 0; j < 5; j++) {
        if (row % 2 == 1) leds.setPixel((i + 1) * ledsPerStrip + p + 4 - j, 0xFF0000);
        row /= 2;
      }
    }
    p += 6;
  }
  leds.show();
}

