void setup() {
setup_blynk();
setup_hardware();

#ifdef DEBUG_MODE
Serial.begin(SERIAL_BAUD_RATE);
#endif
}

void loop() {
  check_blynk_connection();

  if(check_button_press()){
    switch_on_off_pumb();
  }
}