#include <Adafruit_NeoPixel.h>

#define PIN 13
#define NUM_LEDS 4
Adafruit_NeoPixel leds(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

const uint32_t START=leds.Color(0,0,0);
const uint32_t RED=leds.Color(0,255,0);
const uint32_t GREEN=leds.Color(255,0,0);
const uint32_t BLUE=leds.Color(0,0,255);
const uint32_t WHITE=leds.Color(255,255,255);
const uint32_t PINK=leds.Color(0,255,255);
const uint32_t ORANGE=leds.Color(128,255,0);
const uint32_t YELLOW=leds.Color(255,255,0);

void setup() {
  leds.begin();
  leds.fill(START,0,4);
  leds.show();
}

void loop() {
  leds.clear();
  leds.begin();
  leds.fill(PINK,0,4);
  leds.show();
  delay(500);
  
  leds.clear();
  leds.show();
  delay(500);
}
