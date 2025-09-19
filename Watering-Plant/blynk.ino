#include "config.h"
#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp8266.h>

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
const char* access_token = BLYNK_AUTH_TOKEN;

BlynkTimer soil_moisture_delay,water_level_delay;

BLYNK_WRITE(V4);

void setup_blynk(void) {
  Blynk.begin(access_token, ssid, password);
  soil_moisture_delay.setInterval(SOIL_MOISTURE_TIME,send_soil_moisture_reading);
  water_level_delay.setInterval(WATER_LEVEL_TIME, send_water_level_reading);
}

void blynk_connection(void) {
  Blynk.run();
  soil_moisture_delay.run();
  water_level_delay.run();
}

void check_blynk_connection(void) {
  if (!Blynk.connected()) {
    while (!Blynk.connected()) {
      setup_blynk();
      delay(DELAY_CONNECTION);
    }
  } else {
    blynk_connection();
  }
}

BLYNK_WRITE(V4){
  int value = param.asInt();
  Blynk.virtualWrite(V4 ,value );
  toggle_pumb_state();
}

