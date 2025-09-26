/*#####################################################################################################################################################
 File Name     : config.h
 Description   : Contain Configration about Serial Baud Rate, Identification constants of Blynk platform, Wifi contact information and Datastream
 Created on    : Sep 1, 2025
 Version       : V00
 Author        : Moaaz_Zaki
#####################################################################################################################################################*/

#ifndef _CONFIG_H
#define _CONFIG_H

/*######################################################################
# define the unique identity of your project within the Blynk platform #
######################################################################*/

#define BLYNK_TEMPLATE_ID "TMPL2KWUs9Wtq"
#define BLYNK_TEMPLATE_NAME "Watering Plant"


/*###########################################
# Conect information For the Blynk Platform #
###########################################*/

#define WIFI_SSID "WE_E25B3B"
#define WIFI_PASSWORD "vodafone01097674852"
#define BLYNK_AUTH_TOKEN "-BXw6vD2QnGv0UeZFATFXk3yD6uhlFMN"

/*##############################################################
# Setup Serial Communication to print result on Serial Monitor #
##############################################################*/
#define DEBUG_MODE
#define SERIAL_BAUD_RATE 115200

/*################################################
# Critical Soil Moisture and water level reading #
################################################*/

#define CRITICAL_SOIL_MOISTURE 20
#define CRITICAL_WATER_LEVEL 20

/*#########################################################
# delay Time of send signal by ultrasonic                 #
# Delay of wait to return connect to wifi                 #
# time of send soil moisture and water level to dashboard #
#########################################################*/
#define SIGNAL_HIGH_TIME 10
#define SIGNAL_LOW_TIME 2
#define DELAY_CONNECTION 500
#define SOIL_MOISTURE_TIME 3000
#define WATER_LEVEL_TIME 3000

/*##################################################
# Information change by enviromantal and tank size #
##################################################*/

#define SOUND_SPEED 0.0343
#define MAX_DISTANCE 22
#define DISTANCE_TO_BOTTON 2

#endif