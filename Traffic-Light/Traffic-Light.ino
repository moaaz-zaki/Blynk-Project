void setup() {
#ifdef DEBUG_MODE
  Serial.begin(SERIAL_BAUD_RATE);
#endif

  setup_hardware();
  setup_blynk();
}

void loop() {
  check_blynk_connection();

  if (check_normal_control()) {
    if (check_remaining_time_normal_control()) {
      normal_control();
    } else {
      remaining_normal_control();
    }
  }
}
