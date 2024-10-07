#include <GyverSegment.h>
#include <EncButton.h>
#include <TimeLib.h>
#include <GyverBME280.h>

#define ulong unsigned long

#define TICK_CLOCK_TIME 2500
#define TICK_COLON_TIME 1000
#define MAX_DISPLAY_BRIGHTNESS 7
#define RUN_PERIOD 500
#define VOLUME_BARRIER 520
#define BRIGHTNESS_ON_TIME 3000

#define DIO_PIN 3
#define CLK_PIN 4
#define S1_PIN 7
#define S2_PIN 6
#define KEY_PIN 5
#define MICRO_PIN A7

Disp1637Colon disp(3, 4, true);
SegRunner run(&disp);
SegAnimation<4> anim(&disp, 0);
EncButton enc(S1_PIN, S2_PIN, KEY_PIN);
GyverBME280 bme;

int brightness = 5;
bool power = true;

void setup() {
  Serial.begin(9600);

  Serial.println(bme.begin(0x76));
  anim.setEffect(SegEffect::TwistClear);
  anim.start();
  run.setPeriod(RUN_PERIOD);
  disp.brightness(brightness);
  disp.clear();
  disp.update();
  setTime(5184000);
}

void loop() {
  ulong t1 = millis();

  colon_tick();
  bme_tick();
  time_tick();
  micro_tick();
  enc_tick();

  t1 = millis() - t1;
  if (t1 > 150) {
    Serial.println(t1);
  }
}

void set_power(bool state) {
  disp.power(state);
  power = state;
}
