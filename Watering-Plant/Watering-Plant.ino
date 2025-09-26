void setup() {

#ifdef DEBUG_MODE
Serial.begin(SERIAL_BAUD_RATE);
#endif

setup_blynk();
setup_hardware();

}

void loop() {
  check_blynk_connection();
}
