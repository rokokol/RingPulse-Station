static ulong tick_time = TICK_CLOCK_TIME;
static ulong tick_colon = TICK_COLON_TIME;
static int prevmin = 100;
static int prevhr = 100;
bool colon = true;


void time_tick() {
  bool wait = false;

  if (minute() != prevmin) {
    update_mins();

    prevmin = minute();
    wait = true;
  }

  if (hour() != prevhr) {
    update_hrs();

    prevhr = hour();
    wait = true;
  }

  if (wait) {
    anim.waitEnd();
  }
}

void update_mins() {
  bool indentmin = false;

  if (minute() < 10) {
    indentmin = true;
  }

  anim.setCursor(2);
  if (indentmin) {
    anim.print(0);
  }
  anim.print(minute());
}

void update_hrs() {
  bool indenthr = false;

  if (hour() < 10) {
    indenthr = true;
  }

  anim.setCursor(0);
  if (indenthr) {
    anim.print(0);
  }
  anim.print(hour());
}

void colon_tick() {
  if (millis() - tick_colon >= TICK_COLON_TIME) {
    disp.colon(colon);
    colon = !colon;

    tick_colon = millis();
  }
}
