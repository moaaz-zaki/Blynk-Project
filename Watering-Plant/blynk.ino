/*#####################################################################################################################################################
 File Name     : blynk.ino
 Module        : control Pumb ON / OFF From dashboard
 Description   : public function to control Pumb From Blynk platform
 Created on    : Sep 1, 2025
 Version       : V00
 Author        : Moaaz_Zaki
#####################################################################################################################################################*/

#include "config.h"

/*##################################
# Libraries for The Blynk Platform #
##################################*/

#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp8266.h>

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
const char* access_token = BLYNK_AUTH_TOKEN;

BlynkTimer soil_moisture_delay,water_level_delay;

//Prototype
BLYNK_WRITE(V3);



/*============================================================================================================================
 Function Name: setup blynk
 Description  : [1] setup Blynk platform via Acess Token, Wifi SSID and Wifi Passward
                [2] setup timer which soil moisture reading and water level reading every specific periode of time
 Input        : Void
============================================================================================================================*/

void setup_blynk(void) {
  Blynk.begin(access_token, ssid, password);
  soil_moisture_delay.setInterval(SOIL_MOISTURE_TIME,send_soil_moisture_reading);
  water_level_delay.setInterval(WATER_LEVEL_TIME, send_water_level_reading);
}

/*=======================================================================================================================
 Function Name: blynk connection
 Description  : [1] Maintain Connection, Process Incoming Data and Handle Outgoing Data
                [2] send soil moisture reading and water level reading every specific periode of time
 Input        : Void
 Note         : It must be called on every cycle to ensure that the device remains online and responsive to commands. 
========================================================================================================================*/
void blynk_connection(void) {
  Blynk.run();
  soil_moisture_delay.run();
  water_level_delay.run();

}

/*===========================================================================================================================
 Function Name: check_blynk_connection
 Description  : check connection with platform.
                  -if connection failed => try setup again
                  -if connected => Maintain Connection, Process Incoming Data and Handle Outgoing Data
                                => send soil moisture reading and water level reading every specific periode of time
 Input        : Void
============================================================================================================================*/
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

/*=============================================================================================
 Function Name: BLYNK WRITE
 Description  : read switch state from dachboard
 Input        : Virtual pin Number
 Output       : read switch state if reading true
                -turn on Pumb which change state from dashboard
                if reading false
                  -turn off pumb which change state from dashboard
=============================================================================================*/

BLYNK_WRITE(V3){
  int value = param.asInt();
  // Blynk.virtualWrite(V3 ,value );
  if(value==HIGH)
  {
    turn_on();
  }
  if(value==LOW)
  {
    turn_off();
  }
}

