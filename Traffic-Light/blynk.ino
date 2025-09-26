/*#####################################################################################################################################################
 File Name     : blynk.ino
 Module        : control LED ON / OFF From dashboard
 Description   : public function to control LED From Blynk platform
 Created on    : Sep 1, 2025
 Version       : V00
 Author        : Moaaz_Zaki
#####################################################################################################################################################*/
#include "hardware.h"

#include "config.h"

/*##################################
# Libraries for The Blynk Platform #
##################################*/
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Prototype
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

/*=============================================================================================
 Function Name: setup blynk
 Description  : setup Blynk platform via Acess Token, Wifi SSID and Wifi Passward
 Input        : Void
=============================================================================================*/

void setup_blynk(void) {
  Blynk.begin(acess_token, ssid, password);
}

/*=======================================================================================================================
 Function Name: blynk connection
 Description  : Maintain Connection, Process Incoming Data and Handle Outgoing Data
 Input        : Void
 Note         : It must be called on every cycle to ensure that the device remains online and responsive to commands. 
========================================================================================================================*/

void blynk_connection(void) {
  Blynk.run();
}

/*========================================================================================================
 Function Name: check_blynk_connection
 Description  : check connection with platform.
                  -if connection failed => try setup again
                  -if connected => Maintain Connection, Process Incoming Data and Handle Outgoing Data
 Input        : Void
=========================================================================================================*/

void check_blynk_connection( void ) {
  if (!Blynk.connected()) {
    while (!Blynk.connected()) {
      setup_blynk();
    }
  } else {

    blynk_connection();
  }
}

/*=============================================================================================
 Function Name: reset switch
 Description  : turn off all switch on dashboard
 Input        : Void
=============================================================================================*/

void reset_switch( void ) {
  for (int i = 0; i < NUMBER_OF_LED; i++) {
    Blynk.virtualWrite(switch_state[i], LOW);
  }
}

/*=============================================================================================
 Function Name: BLYNK WRITE
 Description  : read switch state from dachboard
 Input        : Virtual pin Number
 Output       : read switch state if reading true
                -Saves the remaining time to last state before turn off
                -turn off all led
                -turn off all switch
                -turn on switch which change state from dashboard

                if reading false
                  -turn off switch which change state from dashboard
=============================================================================================*/

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
