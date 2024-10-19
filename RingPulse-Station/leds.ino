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
  if (millis() - led_tick_time >= tick_dur) {
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
        tick_dur = LED_TICK_DATA;
        break;
      case HUMID_RING:
        humid_ring_tick();
        tick_dur = LED_TICK_DATA;
        break;
    }
    FastLED.show();
    led_tick_time = millis();
  }
}

void lgbtq_ring_tick() {
  for (int i = 0; i < LED_NUM; i++) {
    leds[i].setHue(led_counter + i * 255 / LED_NUM);
  }
  led_counter++;
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
}

void temp_ring_tick() {
}

void humid_ring_tick() {
}

void clock_ring_tick() {
}
