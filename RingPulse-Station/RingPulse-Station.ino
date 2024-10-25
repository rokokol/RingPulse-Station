#include <GyverSegment.h>
#include <EncButton.h>
#include <TimeLib.h>
#include <GyverBME280.h>
#include <FastLED.h>

#define ulong unsigned long

#define TICK_CLOCK_TIME 2500
#define TICK_COLON_TIME 500
#define TICK_VOL_DIFF 500
#define MAX_DISPLAY_BRIGHTNESS 7
#define RUN_PERIOD 500

#define LED_TICK_LGBTQ 30
#define LED_TICK_VOICE 70
#define LED_TICK_TEMP 500
#define LED_TICK_CLOCK 500
#define VOLUME_BARRIER 1000
#define VOLUME_CEILING 800
#define VOLUME_FLOOR 300
#define BRIGHTNESS_ON_TIME 3000
#define LED_NUM 16
#define VOLUME_LINE 100
#define VOLUME_SPEED_COEF 0.3

#define MODS_COUNT 5
#define LGBTQ_RING 0
#define VOICE_RING 1
#define TEMP_RING 2
#define CLOCK_RING 3
#define OFF_RING 4

#define DIO_PIN 6
#define CLK_PIN 7
#define S1_PIN 3
#define S2_PIN 4
#define KEY_PIN 5
#define MICRO_PIN A7
#define LED_PIN 9

Disp1637Colon disp(DIO_PIN, CLK_PIN, true);
SegRunner run(&disp);
SegAnimation<4> anim(&disp, 0);
EncButton enc(S1_PIN, S2_PIN, KEY_PIN);
GyverBME280 bme;

int brightness = 5;
bool power = true;
int led_mode = LGBTQ_RING;
int volume = 0;


void setup() {
  Serial.begin(9600);

  analogReference(EXTERNAL);
  Serial.println(bme.begin(0x76));
  anim.setEffect(SegEffect::TwistClear);
  anim.start();
  run.setPeriod(RUN_PERIOD);
  disp.brightness(brightness);
  disp.clear();
  disp.update();
  led_init();
  setTime(5227200);
}

void loop() {
  ulong t1 = millis();

  colon_tick();
  bme_tick();
  time_tick();
  micro_tick();
  led_tick();
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
