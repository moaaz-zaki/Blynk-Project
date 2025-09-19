#include "hardware.h"


int soil_moisture_reading;
unsigned long my_time = 0;
unsigned long distance, duration;
long water_level = 0;
boolean pumb_state = false;





void setup_hardware(void) {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(PUMB_BUTTON , BUTTON_PIN_MODE );
  pinMode(PUMB , OUTPUT);
  digitalWrite(PUMB , HIGH);
}

void update_soil_moisture_reading(void) {
  soil_moisture_reading = analogRead(SOIL_MOISTURE);
  soil_moisture_reading = map(soil_moisture_reading, 0, 1023, 0, 100);
}

void send_soil_moisture_reading(void) {
  update_soil_moisture_reading();
  Blynk.virtualWrite(V0, soil_moisture_reading);
  Serial.println(soil_moisture_reading);
  if (check_soil_moisture()){
    automatic_mode();
  }

}

void setup_ultrasonic_signal(void) {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(SIGNAL_LOW_TIME);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(SIGNAL_HIGH_TIME);
  digitalWrite(TRIG, LOW);
}

void update_water_level_reading(void) {
  setup_ultrasonic_signal();
  duration = pulseIn(ECHO, HIGH);
  distance = (duration / 2) * SOUND_SPEED;
  water_level = map(distance, MAX_DISTANCE, DISTANCE_TO_BOTTON, 0, 100);
  Serial.println(water_level);
}

void send_water_level_reading(void) {
  update_water_level_reading();
  check_empty_tank();
  Blynk.virtualWrite(V1, water_level);
}

void check_empty_tank ( void ){
  if(water_level < CRITICAL_WATER_LEVEL){
    Blynk.virtualWrite(V2, HIGH);
  }else{
    Blynk.virtualWrite(V2, LOW);
  }
}

boolean check_button_press ( void ){
  if(millis() - my_time > PUMB_BUTTON_DELAY){
    my_time = millis();
    return digitalRead(PUMB_BUTTON) == BUTTON_ACTIVE_STATE;
  }
    return digitalRead(PUMB_BUTTON) == BUTTON_ACTIVE_STATE;
}

void toggle_pumb_state ( void ){
  pumb_state = !pumb_state;
  digitalWrite(PUMB , pumb_state);
}

void switch_on_off_pumb ( void ){
  toggle_pumb_state();
  Blynk.virtualWrite(V4 ,pumb_state);
}

boolean check_soil_moisture ( void ){
  return soil_moisture_reading < CRITICAL_SOIL_MOISTURE && water_level > CRITICAL_WATER_LEVEL;
}

void automatic_mode ( void ){
    toggle_pumb_state();
    Blynk.virtualWrite(V4 ,pumb_state);
}

