/*#####################################################################################################################################################
 File Name     : config.h
 Description   : Contain Configration about Serial Baud Rate, Identification constants of Blynk platform, Wifi contact information and Datastream
 Created on    : Sep 1, 2025
 Version       : V00
 Author        : Moaaz_Zaki
#####################################################################################################################################################*/
#ifndef _CONFIG_H
#define _CONFIG_H


/*##############################################################
# Setup Serial Communication to print result on Serial Monitor #
##############################################################*/

#define DEBUG_MODE
#define SERIAL_BAUD_RATE 115200

/*######################################################################
# define the unique identity of your project within the Blynk platform #
######################################################################*/

#define BLYNK_TEMPLATE_ID "TMPL210YJeMo-"
#define BLYNK_TEMPLATE_NAME "Traffic Light"

/*###########################################
# Conect information For the Blynk Platform #
###########################################*/

#define WIFI_SSID "WE_E25B3B"
#define WIFI_PASSWORD "vodafone01097674852"
#define BLYNK_AUTH_TOKEN "9oBxCpa7ZmyrSvhFRqGWL_aQvHrtSI00"

/*##############################################
# Delay Time For every traffic Signal in Order #
# (Red => 9s)  (Yellow => 3s)  (Green => 7.5s) #
##############################################*/
#define DELAY_TIME { 9000, 3000, 7500 }


/*##############
# Switch State #
##############*/
#define SWITCH_OFF false
#define SWITCH_ON true


/*########################################################
# Number of Vartual pin on dataStream on Blynk platform  #
##########################################################*/
#define SWITCH_STATE { V0, V1, V2 }

#endif