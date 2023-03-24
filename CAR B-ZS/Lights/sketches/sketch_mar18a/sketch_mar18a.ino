#include <Adafruit_NeoPixel.h>

// Define the NeoPixel LED strip and its parameters
#define PIN 13
#define NUM_LEDS 4
Adafruit_NeoPixel led(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Initialize the NeoPixel strip
  led.begin();
  led.show(); // Turn off all pixels
}

void loop() {
  // Set the colors to blink
  uint32_t colors[] = {led.Color(255, 0, 0), // Red
                       led.Color(0, 255, 0), // Green
                       led.Color(0, 0, 255)}; // Blue
  int numColors = sizeof(colors) / sizeof(colors[0]);

  // Loop through each color and blink the NeoPixels
  for (int i = 0; i < numColors; i++) {
    // Turn on the color
    for (int j = 0; j < NUM_LEDS; j++) {
      led.setPixelColor(j, colors[i]);
    }
    led.show(); // Display the color on the LEDs
    delay(500); // Wait for half a second

    // Turn off the color
    for (int j = 0; j < NUM_LEDS; j++) {
      led.setPixelColor(j, 0);
    }
    led.show(); // Turn off the LEDs
    delay(500); // Wait for half a second
  }
}

/* This function defines the NeoPixel strip parameters and initializes it in the setup() function. In the loop() function, 
 * it defines an array of colors to blink, loops through each color, turns on the NeoPixels for the color, displays it on the LEDs, 
 * waits for half a second, turns off the NeoPixels, turns off the LEDs, and then repeats for the next color. 
 */
