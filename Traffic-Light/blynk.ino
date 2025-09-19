#include "hardware.h"
#include "config.h"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

BLYNK_WRITE(V0);
BLYNK_WRITE(V1);
BLYNK_WRITE(V2);

const int switch_state[] = SWITCH_STATE;

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
const char* acess_token = BLYNK_AUTH_TOKEN;

const int led[] = LED_ARRAY;
const int delay_time[] = DELAY_TIME;

unsigned long remaining_time = 0;
unsigned long my_time = 0;
int current_led = 0;


int red_state = 0;
int yellow_state = 0;
int green_state = 0;

void reset_switch() {
  for (int i = 0; i < NUMBER_OF_LED; i++) {
    Blynk.virtualWrite(switch_state[i], LOW);
  }
}
void setup_blynk(void) {
  Blynk.begin(acess_token, ssid, password);
}

void blynk_connection(void) {
  Blynk.run();
}

void check_blynk_connection() {
  if (!Blynk.connected()) {
    while (!Blynk.connected()) {
      setup_blynk();
    }
  } else {

    blynk_connection();
  }
}


BLYNK_WRITE(V0) {
  red_state = param.asInt();
  if (red_state) {
    remaining_time = delay_time[current_led] - (millis() - my_time);
    reset_led();
    reset_switch();
    digitalWrite(led[0], red_state);
    Blynk.virtualWrite(switch_state[0], red_state);

  } else if (red_state == SWITCH_OFF) {
    digitalWrite(led[0], red_state);
  }
}

BLYNK_WRITE(V1) {
  yellow_state = param.asInt();
  if (yellow_state) {
    remaining_time = delay_time[current_led] - (millis() - my_time);
    reset_led();
    reset_switch();
    digitalWrite(led[1], yellow_state);
    Blynk.virtualWrite(switch_state[1], yellow_state);
  } else if (yellow_state == SWITCH_OFF) {
    digitalWrite(led[1], yellow_state);
  }
}

BLYNK_WRITE(V2) {
  green_state = param.asInt();
  if (green_state) {
    remaining_time = delay_time[current_led] - (millis() - my_time);
    reset_led();
    reset_switch();
    digitalWrite(led[2], green_state);
    Blynk.virtualWrite(switch_state[2], green_state);
  } else if (green_state == SWITCH_OFF) {
    digitalWrite(led[2], green_state);
  }
}
