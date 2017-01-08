
int rainbowColor(float f, float alpha) {
  float c = 3 * fmod(f + 1000000.0, 1.0);
  int res = 0;
  for (int cutoff = 0; cutoff < 3; cutoff++) {
    float rc = (cutoff == 0 && c > 1) ? c - 3 : c;
    res = res * 256 + max(0, (int)(255 * alpha * (1 - abs(rc - cutoff))));
  }
  return res;
}

void rainbow(int period, float quantum, int nSteps) {
  for (int s=0; s < nSteps; s++) {
    for (int strip = 0; strip < nStrips; strip++) {
      for (int i=0; i < ledsPerStrip; i++) {
        // (strip % 2 == 0 ? -1 : 1)
         leds.setPixel(strip * ledsPerStrip + i, rainbowColor(((float)i / period) + (strip / 10.0) - s * quantum, 1.0));
      }
      leds.show();
      //delayMicroseconds(delayMs);
    }
  }
}

void rainbow8(float quantum, int nSteps) {
  for (int s=0; s < nSteps; s++) {
    for (int strip = 0; strip < nStrips/2; strip++) {
      for (int i=0; i <= min(strip, nStrips - 1 - strip); i++) {
         reflected8(strip, i, rainbowColor(((float)i / 10.0) + (strip / 10.0) - s * quantum, 0.3));
      }
    }
    leds.show();
    delayMicroseconds(20000);
  }
}

