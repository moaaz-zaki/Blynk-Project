/*#####################################################################################################################################################
 File Name     : prepherals.ino
 Module        : control LED ON / OFF
 Description   : public function to control LED via  specific modes 
 Created on    : Sep 1, 2025
 Version       : V00
 Author        : Moaaz_Zaki
#####################################################################################################################################################*/


/*=============================================================================================
 Function Name: setup hardware
 Description  : setup Mode of Pins
 Input        : Void
 Output       : Make mode of pin OUTPUT
=============================================================================================*/

void setup_hardware(void) {
  for (int i = 0; i < NUMBER_OF_LED; i++) {
    pinMode(led[i], OUTPUT);
  }
}

/*=============================================================================================
 Function Name: reset led
 Description  : turn off all led
 Input        : Void
=============================================================================================*/

void reset_led(void) {
  for (int i = 0; i < NUMBER_OF_LED; i++) {
    digitalWrite(led[i], LOW);
  }
}

/*=================================================================================================
 Function Name: check normal control
 Description  : Normal mode of traffic light turn on when all switch state in dashboard => false
 Input        : Void
==================================================================================================*/

boolean check_normal_control( void ) {
    Serial.print(red_state);
    Serial.print("\t");
    Serial.print(yellow_state);
    Serial.print("\t");
    Serial.println(green_state);
  return ( green_state == SWITCH_OFF && yellow_state == SWITCH_OFF && red_state == SWITCH_OFF);
}

/*=============================================================================================
 Function Name: check remaining time normal control
 Description  : check the remaing time of last led finished or not
 Input        : Void
=============================================================================================*/

boolean check_remaining_time_normal_control(void) {
  return remaining_time <= 0;
}

/*=======================================================================================================================================
 Function Name: normal control
 Description  : turn on Normal Mode of traffic light
 Input        : Void
 Output       : [1] turn on red led and turn off after delay time finish
                [2] turn on yellow led and turn off after delay time finish
                [3] turn on green led and turn off after delay time finish

Note          : normal mode remain turn on untill change switch state at dachboard and return after turn off all switch on dachboard
========================================================================================================================================*/

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

/*==================================================================================================================================
 Function Name: reset remaining_normal_control
 Description  : turn on Normal Mode of traffic light when switch state on dashboard change before delay time of last led finish
 Input        : Void
 Output       : turn on last led with remaining time and return to normal Mode
====================================================================================================================================*/

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






