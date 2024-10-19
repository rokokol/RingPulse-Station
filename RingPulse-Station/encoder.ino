void enc_tick() {
  enc.tick();

  if (enc.action()) {
    switch_enc_actions();
  }
}

void switch_enc_actions() {
  if (enc.right()) {
    increase_brightness();
  } else if (enc.left()) {
    decrease_brightness();
  } else if (enc.rightH()) {
    increase_mins();
  } else if (enc.leftH()) {
    decrease_mins();
  } else if (enc.step(1)) {
    increase_hrs();
  } else if (enc.hasClicks(3)) {
    start_bme_cycle();
  } else if (enc.hasClicks(2)) {
    next_led_mode();
  }
}

void increase_brightness() {
  if (brightness <= MAX_DISPLAY_BRIGHTNESS) {
    brightness += 1;

    update_brightness();
    set_power(true);
  }
}

void increase_hrs() {
  ulong time = now() + 3600;

  setTime(time);
}

void decrease_brightness() {
  if (brightness == 0) {
    set_power(false);
    disp.update();
  } else if (brightness > 0) {
    brightness -= 1;
    update_brightness();
  }
}

void increase_mins() {
  ulong time = now() - now() % 60;
  time += 60;

  setTime(time);
}

void decrease_mins() {
  ulong time = now() - now() % 60;
  time -= 60;

  setTime(time);
}

void update_brightness() {
  int level = constrain(brightness - 1, 0, 7);
  FastLED.setBrightness(map(level, 0, 7, 0, 255));
  FastLED.show();
  disp.brightness(level);
  disp.update();
}

void next_led_mode() {
  led_mode = (led_mode + 1) % MODS_COUNT;
}
