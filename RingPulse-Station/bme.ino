static ulong bme_tick_millis = RUN_PERIOD;
char data[16] = "";

void bme_tick() {
  if (run.running()) {
    run.tick();
    if (millis() - bme_tick_millis >= (strlen(data) + 5) * RUN_PERIOD) {
      for (int i = 0; i < strlen(data); i++) {
        data[i] = "";
      }
      run.stop();
      start_update_time();
      Serial.println("stop");
    }
  }
}

void start_bme_cycle() {
  stop_update_time();
  int temp = bme.readTemperature();
  int pressuse = bme.readPressure() / 133.322;
  int humidity = bme.readHumidity();

  itoa(temp, data, DEC);
  strcat(data, "*C ");

  ltoa(pressuse, data + strlen(data), DEC);
  strcat(data, "Xg ");

  itoa(humidity, data + strlen(data), DEC);
  strcat(data, "Pr");

  Serial.println(data);
  run.setText(data);
  run.start();
  bme_tick_millis = millis();
}
