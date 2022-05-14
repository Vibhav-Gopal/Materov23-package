#include <WiFi.h>
#include "wifi_functs.h"

 char* ssid = "Rahul's PC";
 char* password = "2002@Rahul";




 void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  
  if (WiFi.status() != WL_CONNECTED) 
    Serial.print('Unable to connect to Wifi');
   
  else 
    Serial.println(WiFi.localIP());
}

void reconnectWiFi(){
  if ((WiFi.status() != WL_CONNECTED) ) {
  Serial.print(millis());
  Serial.println("Reconnecting to WiFi...");
  WiFi.disconnect();
  WiFi.begin(ssid,password);
}

}


