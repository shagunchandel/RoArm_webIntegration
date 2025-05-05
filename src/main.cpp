#include <Arduino.h>
#include <ArduinoJson.h>
#include <SCServo.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include "roarm_html.h"

SMS_STS sc;

AsyncWebServer server(80);

const char* ssid = "moto";
const char* password = "123456789";

void WifiConnect(){
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  WifiConnect();
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", main_page);
  });

//   server.on("/djs", HTTP_GET, [](AsyncWebServerRequest *request) {
//     request->send(200, "text/html", html_djs);
// });
  server.begin();

  Serial.println(WiFi.localIP());

}

void loop() {
  
}