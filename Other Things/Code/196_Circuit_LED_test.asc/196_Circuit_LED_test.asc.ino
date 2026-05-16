#include <FastLED.h>

#define LED_PIN     6
#define WIDTH       16
#define HEIGHT      16
#define NUM_LEDS    (WIDTH * HEIGHT)
#define BRIGHTNESS  64    // Keep low — 256 LEDs at full white = ~15A!
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

// Convert (x,y) to serial index for serpentine wiring
uint16_t XY(uint8_t x, uint8_t y) {
  if (y & 0x01) {
    // Odd rows run right-to-left
    return (y * WIDTH) + (WIDTH - 1 - x);
  } else {
    // Even rows run left-to-right
    return (y * WIDTH) + x;
  }
}

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  static uint8_t offset = 0;
  for (uint8_t y = 0; y < HEIGHT; y++) {
    for (uint8_t x = 0; x < WIDTH; x++) {
      leds[XY(x, y)] = CHSV(offset + (x + y) * 8, 255, 255);
    }
  }
  FastLED.show();
  offset++;
  delay(20);
}