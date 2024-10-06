static ulong tick = RUN_PERIOD;
char data[15] = "";

void bme_tick() {
  if (run.running()) {
    run.tick();
    if (millis() - tick >= (strlen(data) + 5) * RUN_PERIOD) {
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
  strcat(data, "Hg ");

  itoa(humidity, data + strlen(data), DEC);
  strcat(data, "%");

  Serial.println(data);
  run.setText(data);
  run.start();
  tick = millis();
}
