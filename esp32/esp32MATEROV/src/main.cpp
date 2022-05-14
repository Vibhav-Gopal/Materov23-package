#include <Arduino.h>
#include "wifi_functs.h"
#include "ota_server.h"
#include "ros_functs.h"

void setup() {

    initWiFi();
    initOTAServer();
    initROS();
 }

void loop() {
  // put your main code here, to run repeatedly:
}