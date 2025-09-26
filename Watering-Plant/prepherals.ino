/*##############################################################################################################################
 File Name     : prepherals.ino
 Module        : control in pumb ON / Off 
 Description   : public function to Read soil moisture, water level and control pumb via  specific modes via  specific modes
 Created on    : Sep 1, 2025
 Version       : V00
 Author        : Moaaz_Zaki
###############################################################################################################################*/

#include "hardware.h"


int soil_moisture_reading;
unsigned long my_time = 0;
unsigned long distance, duration;
long water_level = 0;
boolean pumb_state = true;


/*=============================================================================================
 Function Name: setup hardware
 Description  : setup Mode of Pins 
 Input        : Void
 Output       : Make mode of pin OUTPUT and turn off pumb 
=============================================================================================*/

void setup_hardware(void) {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(PUMB, OUTPUT);
  digitalWrite(PUMB, HIGH);
}

/*=============================================================================================
 Function Name: update soil moisture reading
 Description  : Read soil moisture and rerange the value from 0 : 1023 to 0 : 100
 Input        : Void
=============================================================================================*/

void update_soil_moisture_reading(void) {
  soil_moisture_reading = analogRead(SOIL_MOISTURE);
  soil_moisture_reading = map(soil_moisture_reading, 0, 1023, 0, 100);
}

/*=====================================================================================================
 Function Name: send soil moisture reading
 Description  : [1] call update soil moisture reading function and send send reading to dashboard 
                [2] call check soil moisture function if return true => turn on automatic mode 
 Input        : Void
======================================================================================================*/

void send_soil_moisture_reading(void) {
  update_soil_moisture_reading();
  Blynk.virtualWrite(V0, soil_moisture_reading);
  Serial.println(soil_moisture_reading);
  if (check_soil_moisture()) {
    automatic_mode();
  }
}


/*========================================================================================================================================
 Function Name: setup ultrasonic signal
 Description  : setup signal by Low wave coming out for 2 Micro sec thus high wave coming out for 10 Micro sec thus Low wave coming out
 Input        : Void
========================================================================================================================================*/
void setup_ultrasonic_signal(void) {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(SIGNAL_LOW_TIME);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(SIGNAL_HIGH_TIME);
  digitalWrite(TRIG, LOW);
}

/*======================================================================================================
 Function Name: update water level reading
 Description  : [1] call setup ultrasonic signal function 
                [2] Calculates the time of wave exit and return 
                [3] Calculates the distance of water by divide time by 2 and time with sound speed
                [4] rerange water level from 2 : 21 to 0 : 100
 Input        : Void
=======================================================================================================*/
void update_water_level_reading(void) {
  setup_ultrasonic_signal();
  duration = pulseIn(ECHO, HIGH);
  distance = (duration / 2) * SOUND_SPEED;
  water_level = map(distance, MAX_DISTANCE, DISTANCE_TO_BOTTON, 0, 100);
  Serial.println(distance);
}

/*=============================================================================================
 Function Name: send water level reading
 Description  : [1] call send water level reading function
                [2] call check empty tank function
                [3] Send water level reading to dashboard
 Input        : Void
=============================================================================================*/
void send_water_level_reading(void) {
  update_water_level_reading();
  check_empty_tank();
  Blynk.virtualWrite(V1, water_level);
}

/*=========================================================================================================
 Function Name: check empty tank
 Description  : check if water level less than 20 turn on led on dashboard and send one time notification
                else longer than 20 turn off led on dashboard
 Input        : Void
============================================================================================================*/
void check_empty_tank(void) {
  static bool flag = true;

  if (water_level < CRITICAL_WATER_LEVEL) {
    Blynk.virtualWrite(V2, HIGH);
    if (flag) {
      Blynk.logEvent("alart", "The Water level is low");
      flag = false;
    }
  } else {
    Blynk.virtualWrite(V2, LOW);
  }
}


/*=============================================================================================
 Function Name: check soil moisture
 Input        : Void
 Output       : return true => soil moisture less than 20 and water level longer than 20
 Note         : must two conditional achieved
=============================================================================================*/
boolean check_soil_moisture(void) {
  return soil_moisture_reading < CRITICAL_SOIL_MOISTURE && water_level > CRITICAL_WATER_LEVEL;
}

/*=============================================================================================
 Function Name: automatic_mode same utilize of turn on function
 Description  : chang state of pumb to false and turn on pumb
 Input        : Void
=============================================================================================*/
void automatic_mode(void) {
  pumb_state = false;
  Blynk.virtualWrite(V3, pumb_state);
  digitalWrite(PUMB, pumb_state);
}

/*=============================================================================================
 Function Name: turn off
 Description  : chang state of pumb to true and turn off pumb
 Input        : Void
=============================================================================================*/
void turn_off(void) {
  digitalWrite(PUMB, HIGH);
  pinMode(PUMB, INPUT);
}

/*=============================================================================================
 Function Name: turn on
 Description  : chang state of pumb to false and turn on pumb
 Input        : Void
=============================================================================================*/
void turn_on(void) {
  pinMode(PUMB, OUTPUT);
  digitalWrite(PUMB, LOW);
}
