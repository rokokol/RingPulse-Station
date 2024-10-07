static ulong off_tick = 0;

void micro_tick() {
  if (!power) {
    int vol = analogRead(MICRO_PIN);
    if (vol > VOLUME_BARRIER) {
      Serial.println(vol);
      set_power(true);
      disp.update();
      off_tick = millis() + BRIGHTNESS_ON_TIME;
    }
  } else if (brightness == 0 && millis() >= off_tick) {
    set_power(false);
    disp.update();
  }
}
