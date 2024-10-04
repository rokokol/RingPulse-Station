static ulong tick_time = TICK_CLOCK_TIME;
static ulong tick_colon = TICK_COLON_TIME;
bool colon = true;


void time_tick() {
  if (millis() - tick_time >= TICK_CLOCK_TIME) {
    time += 60;
    setTime(time);
    Serial.print(hour());
    Serial.print(':');
    Serial.println(minute());

    bool indentmin = false;
    bool indenthr = false;

    if (minute() < 10) {
      indentmin = true;
    }

    if (hour() < 10) {
      indenthr = true;
    }

    anim.setCursor(0);
    if (indenthr) {
      anim.print(0);
    }
    anim.print(hour());

    if (indentmin) {
      anim.print(0);
    }
    anim.print(minute());

    anim.waitEnd();

    tick_time = millis();
  }
}

void colon_tick() {
  if (millis() - tick_colon >= TICK_COLON_TIME) {
    disp.colon(colon);
    colon = !colon;

    tick_colon = millis();
  }
}
