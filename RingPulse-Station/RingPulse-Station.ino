#include <GyverSegment.h>
#include <EncButton.h>
#include <TimeLib.h>

#define ulong unsigned long

#define TICK_CLOCK_TIME 2000
#define TICK_COLON_TIME 1000
#define MAX_DISPLAY_BRIGHTNESS 7

#define DIO_PIN 3
#define CLK_PIN 4
#define S1_PIN 7
#define S2_PIN 6
#define KEY_PIN 5

Disp1637Colon disp(3, 4, true);
SegAnimation<4> anim(&disp, 0);
EncButton enc(S1_PIN, S2_PIN, KEY_PIN);

ulong time = 5184000;
int brightness = 5;

void setup() {
  Serial.begin(9600);

  anim.setEffect(SegEffect::TwistClear);
  anim.start();
  disp.brightness(brightness);
  disp.clear();
  disp.update();
  setTime(time);
}

void loop() {
  ulong t1 = millis();

  colon_tick();
  time_tick();
  enc_tick();

  t1 = millis() - t1;
  if (t1 > 500) {
    Serial.println(t1);
  }
}
