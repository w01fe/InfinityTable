
int rainbowColor(float f) {
  float c = 3 * fmod(f + 1000000.0, 1.0);
  int res = 0;
  for (int cutoff = 0; cutoff < 3; cutoff++) {
    float rc = (cutoff == 0 && c > 1) ? c - 3 : c;
    res = res * 256 + max(0, (int)(255 * (1 - abs(rc - cutoff))));
  }
  return res;
}

void rainbow(int period, float quantum, int nSteps) {
  for (int s=0; s < nSteps; s++) {
    for (int strip = 0; strip < nStrips; strip++) {
      for (int i=0; i < ledsPerStrip; i++) {
         pixel(strip, i, rainbowColor(((float)i / period) + (strip / 6.0) - s * quantum));
      }
    }
    leds.show();
  }
}

