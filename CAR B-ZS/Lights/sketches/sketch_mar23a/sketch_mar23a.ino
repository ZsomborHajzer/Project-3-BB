#include <Adafruit_NeoPixel.h>

// Define the NeoPixel LED strip and its parameters
#define PIN 13
#define NUM_LEDS 4
Adafruit_NeoPixel led(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void blinkColor(uint8_t red, uint8_t green, uint8_t blue) {
  // Set the color
  uint32_t color = led.Color(red, green, blue);

  // Blink the color on the NeoPixels
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < NUM_LEDS; j++) {
      led.setPixelColor(j, color);
    }
    led.show(); // Display the color on the LEDs
    delay(500); // Wait for half a second

    for (int j = 0; j < NUM_LEDS; j++) {
      led.setPixelColor(j, 0);
    }
    led.show(); // Turn off the LEDs
    delay(500); // Wait for half a second
  }
}

void blue() {
  blinkColor(0, 0, 255); // Blue
}

void green() {
  blinkColor(0, 255, 0); // Green
}

void red() {
  blinkColor(255, 0, 0); // Red
}
/*
 This code defines a function called blinkColor() that takes in three parameters for the red, green, and blue values of the color to blink. 
 *  It then sets the color on the NeoPixels and blinks it for three times, each time turning the LEDs on for half a second and then off for half a second.

 * The code also defines three separate functions for each color, blue(), green(), and red(), that call the blinkColor() function with the appropriate RGB values for each color. 
 * You can call these functions to blink the NeoPixels with the desired color.
 */
