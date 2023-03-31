#include <Adafruit_NeoPixel.h>

// Define the NeoPixel LED strip and its parameters
#define PIN 13
#define NUM_LEDS 4
Adafruit_NeoPixel led(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Initialize the LED strip
  led.begin();
}

void loop() {
  blue(); // Call the blue() function
  green(); // Call the green() function
  red(); // Call the red() function 
}

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
