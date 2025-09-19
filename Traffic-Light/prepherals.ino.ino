void setup_hardware(void) {
  for (int i = 0; i < NUMBER_OF_LED; i++) {
    pinMode(led[i], OUTPUT);
  }
}
void reset_led(void) {
  for (int i = 0; i < NUMBER_OF_LED; i++) {
    digitalWrite(led[i], LOW);
  }
}

boolean check_normal_control( void ) {
      Serial.print(red_state);
    Serial.print("\t");
    Serial.print(yellow_state);
    Serial.print("\t");
    Serial.println(green_state);
  return ( green_state == SWITCH_OFF && yellow_state == SWITCH_OFF && red_state == SWITCH_OFF);
}

boolean check_remaining_time_normal_control(void) {
  return remaining_time <= 0;
}

void normal_control(void) {
  if (millis() - my_time > delay_time[current_led]) {
    my_time = millis();
    digitalWrite(led[current_led], LOW);
    Blynk.virtualWrite(switch_state[current_led], LOW);
    current_led = (current_led + 1) % NUMBER_OF_LED;
    digitalWrite(led[current_led], HIGH);
    Blynk.virtualWrite(switch_state[current_led], HIGH);
  }
}

void remaining_normal_control(void) {
  if (millis() - my_time > remaining_time) {
    my_time = millis();
    remaining_time = 0;
    digitalWrite(led[current_led], LOW);
    Blynk.virtualWrite(switch_state[current_led], LOW);
    current_led = (current_led + 1) % NUMBER_OF_LED;
    digitalWrite(led[current_led], HIGH);
    Blynk.virtualWrite(switch_state[current_led], HIGH);
  }
}






