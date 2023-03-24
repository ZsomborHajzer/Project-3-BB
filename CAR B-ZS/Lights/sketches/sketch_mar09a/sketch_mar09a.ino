#include <Adafruit_NeoPixel.h>

//===[ Pixels ]====================================

const int PIXEL_PIN=13;
const int PIXEL_NUMBER=4;


//===[ Led Pixels ]================================

Adafruit_NeoPixel leds(PIXEL_NUMBER, PIXEL_PIN, NEO_RGB + NEO_KHZ800);
const uint32_t RED=leds.Color(255,0,0);
const uint32_t YELLOW=leds.Color(255,150,0);
const uint32_t BLUE=leds.Color(0,0,255);
const uint32_t WHITE=leds.Color(255,255,255);
const uint32_t START=leds.Color(0,0,0);

//===[SETUP ]============================

void setup() {
  leds.begin();
  leds.fill(WHITE,0,4);
  leds.show();

}
void loop() {
 leds.clear();
 leds.fill(BLUE,0,4);
leds.show();
}
