#include <GyverSegment.h>
#include <TimeLib.h>

#define ulong unsigned long

#define TICK_CLOCK_TIME 2000
#define TICK_COLON_TIME 1000

#define DIO_PIN 3
#define CLK_PIN 4

Disp1637Colon disp(3, 4, true);
SegAnimation<4> anim(&disp, 0);
ulong time = 1728073621;

void setup() {
  Serial.begin(9600);

  anim.setEffect(SegEffect::TwistFill);
  anim.start();

  disp.brightness(1);
  disp.clear();
  disp.update();
  setTime(time);
}

void loop() {
  time_tick();
  colon_tick();
}
