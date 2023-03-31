#include <Adafruit_NeoPixel.h>

#define PIN 13
#define NUM_LEDS 4
Adafruit_NeoPixel leds(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

const uint32_t RED=leds.Color(0,255,0);
const uint32_t GREEN=leds.Color(255,0,0); //FOR SOME REASON RGB WORKS LIKE IT'S GreenRedBlue. (255,0,0) is green rather than red
const uint32_t BLUE=leds.Color(0,0,255);
const uint32_t YELLOW=leds.Color(255,255,0);
const uint32_t WHITE=leds.Color(255,255,255);
const uint32_t PINK=leds.Color(51,255,153);
const uint32_t PURPLE=leds.Color(0,51,51);
const uint32_t ORANGE=leds.Color(165,255,0);

/* list of colors
Red: (255, 0, 0)
Green: (0, 255, 0)
Blue: (0, 0, 255)
Yellow: (255, 255, 0)
Cyan: (0, 255, 255)
Magenta: (255, 0, 255)
White: (255, 255, 255)
Black: (0, 0, 0)
Gray: (128, 128, 128)
Brown: (165, 42, 42)
Orange: (255, 165, 0)
Pink: (255, 192, 203)
Purple: (128, 0, 128)
*/


void blinkColor(uint32_t Color, int blinkCount) {
  for (int i = 0; i < blinkCount; i++) {
    leds.begin();
    leds.fill(Color, 0, NUM_LEDS);
    leds.show();
    delay(500);
    leds.clear();
    leds.show();
    delay(500);
  }
}

void setup() {
  /*
  leds.begin();
  leds.fill(BLUE, 0, NUM_LEDS);
  leds.show();
  delay(500);
  leds.clear();
  leds.show();
  delay(500);
  */
}

void loop() {
  blinkColor(RED, 1);
}
