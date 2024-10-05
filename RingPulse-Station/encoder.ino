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
  }
}

void increase_brightness() {
  if (brightness < MAX_DISPLAY_BRIGHTNESS) {
    brightness += 1;

    disp.brightness(brightness);
    disp.update();
  }
}

void increase_hrs() {
  time += 3600;

  setTime(time);
}

void decrease_brightness() {
  if (brightness > 0) {
    brightness -= 1;

    disp.brightness(brightness);
    disp.update();
  }
}

void increase_mins() {
  time -= time % 60;
  time += 60;

  setTime(time);
}

void decrease_mins() {
  time -= time % 60;
  time -= 60;

  setTime(time);
}
