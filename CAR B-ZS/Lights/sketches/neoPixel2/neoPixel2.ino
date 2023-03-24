#include <Adafruit_NeoPixel.h>

#define NUM_PIXELS     4  // The number of LEDs (pixels) on NeoPixel
#define PIN_NEO_PIXEL  13   // Arduino pin that connects to NeoPixel

Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);

void setup() {
  NeoPixel.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
  NeoPixel.clear(); // set all pixel colors to 'off'. It only takes effect if pixels.show() is called

  // turn on all pixels to red at the same time for a second
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) { // for each pixel
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(255, 0, 255)); // it only takes effect if pixels.show() is called
  }
  
  NeoPixel.show(); // send the updated pixel colors to the NeoPixel hardware.
  delay(1000);     // on time

  NeoPixel.clear(); // turn off all pixels for a second
  NeoPixel.show(); // send the updated pixel colors to the NeoPixel hardware.
  delay(1000);     // off time
}
