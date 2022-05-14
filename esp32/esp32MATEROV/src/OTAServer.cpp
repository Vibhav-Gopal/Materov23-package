#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include "ota_server.h"


AsyncWebServer OTAServer(80);


void initOTAServer(){
    
  OTAserver.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hi! This is a sample response.");
  });

  AsyncElegantOTA.begin(&OTAserver);    // Start AsyncElegantOTA
  OTAserver.begin();
}