static ulong led_tick_time;
static ulong vol_tick;
int tick_dur;
int prev_volume;
const int levels = LED_NUM / 2 + 1;
CRGB leds[LED_NUM];
byte led_counter;


void led_init() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, LED_NUM);
  update_brightness();
}

void led_tick() {
  if (led_mode != OFF_RING && millis() - led_tick_time >= tick_dur) {
    switch (led_mode) {
      case LGBTQ_RING:
        lgbtq_ring_tick();
        tick_dur = LED_TICK_LGBTQ;
        break;
      case VOICE_RING:
        voice_ring_tick();
        tick_dur = LED_TICK_VOICE;
        break;
      case TEMP_RING:
        temp_ring_tick();
        tick_dur = LED_TICK_TEMP;
        break;
      case CLOCK_RING:
        clock_ring_tick();
        tick_dur = LED_TICK_CLOCK;
        break;
    }
    led_tick_time = millis();
  }
}

void lgbtq_ring_tick() {
  for (int i = 0; i < LED_NUM; i++) {
    leds[i].setHue(led_counter + i * 255 / LED_NUM);
  }
  led_counter++;
  FastLED.show();
}

void voice_ring_tick() {
  FastLED.clear();
  int current_volume;
  if (millis() - vol_tick >= TICK_VOL_DIFF) {
    current_volume = volume;
    prev_volume = current_volume;
    vol_tick = millis();
  } else {
    prev_volume = max(volume, prev_volume);
    current_volume = prev_volume;
  }

  int val = constrain(current_volume, VOLUME_FLOOR, VOLUME_CEILING);
  int level = map(val, VOLUME_FLOOR, VOLUME_CEILING, 0, levels);

  leds[0].setRGB(0, 255, 0);
  for (int i = 0; i < level; i++) {
    int red_amount = map(i + 1, 0, levels, 0, 255);

    int red = red_amount;
    int green = 1 - red_amount;
    leds[i].setRGB(red, green, 0);
    leds[LED_NUM - i].setRGB(red, green, 0);
  }
  FastLED.show();
}

void temp_ring_tick() {
  CRGB color = colorTemperatureFromCelsius(bme.readTemperature());
  FastLED.showColor(color);
}

void clock_ring_tick() {
  FastLED.clear();
  int sec = map(second(), 0, 59, 0, LED_NUM - 1);
  sec = (sec + 8) % LED_NUM;
  int min = map(minute(), 0, 59, 0, LED_NUM - 1);
  min = (min + 8) % LED_NUM;
  int hr = map(hour() % 12, 0, 11, 0, LED_NUM - 1);
  hr = (hr + 8) % LED_NUM;
  leds[sec].blue = 255;
  leds[min].green = 255;
  leds[hr].red = 255;
  FastLED.show();
}

CRGB colorTemperatureFromCelsius(float celsius) {
  float kelvin = celsius + 273.15;

  if (kelvin < 1000) kelvin = 1000;
  if (kelvin > 40000) kelvin = 40000;

  float temp = kelvin / 100.0;
  float red, green, blue;

  if (temp <= 66) {
    red = 255;
    green = temp;
    green = 99.4708025861 * log(green) - 161.1195681661;
    blue = (temp <= 19) ? 0 : (138.5177312231 * log(temp - 10) - 305.0447927307);
  } else {
    red = 329.698727446 * pow(temp - 60, -0.1332047592);
    green = 288.1221695283 * pow(temp - 60, -0.0755148492);
    blue = 255;
  }

  red = constrain(red, 0, 255);
  green = constrain(green, 0, 255);
  blue = constrain(blue, 0, 255);

  return CRGB((uint8_t)red, (uint8_t)green, (uint8_t)blue);
}
