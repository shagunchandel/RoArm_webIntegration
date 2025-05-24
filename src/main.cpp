#include "config.h"
#include "roarm_html.h"
#include "arm_functn.h"
#include "led_ctrl.h"
#include "arm_wifi.h"

// AsyncWebServer server(80);

// const char* ssid = "moto";
// const char* password = "123456789";

// void WifiConnect(){
//   while (WiFi.status() != WL_CONNECTED){
//     delay(500);
//     Serial.print(".");
//   }
// }
// void  web_movement(AsyncWebServerRequest *request, uint8_t *data, size_t len){
//   StaticJsonDocument<256> doc;
//   DeserializationError error = deserializeJson(doc, data, len);
//   if (error) {
//       request->send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
//       return;
//   }
  
//   position1 = doc["base"];
//   st.WritePosEx(11, position1, SERVO_SPEED, SERVO_ACC);
// }


void web_movement(AsyncWebServerRequest *request, uint8_t *data, size_t len) {
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, data, len);

  if (error) {
    request->send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
    return;
  }

  if (doc.containsKey("base")) {
    position1 = doc["base"];
    st.WritePosEx(11, position1, SERVO_SPEED, SERVO_ACC);
  }
  else if (doc.containsKey("wrist")) {
    position5 = doc["wrist"];
    st.WritePosEx(15, position5, SERVO_SPEED, SERVO_ACC);
  }
  else if (doc.containsKey("sholder")) {
    position2 = doc["sholder"];
    // position3 = 2047 + (2047 - position2) + 1;
    position3 = 4095 - position2;
    byte ID[2] = {12, 13};
    short position[2] = {position2, position3};
    unsigned short speed[2] = {SERVO_SPEED, SERVO_SPEED};  // Speed for both servos
    byte acc[2] = {SERVO_ACC, SERVO_ACC};
    st.SyncWritePosEx(ID, 2, position, speed, acc);
  }
  else if (doc.containsKey("elbow")) {
    position4 = doc["elbow"];
    st.WritePosEx(14, position4, SERVO_SPEED, SERVO_ACC);
  }
  else if (doc.containsKey("gripper")) {
    position6 = doc["gripper"];
    st.WritePosEx(1, position6, SERVO_SPEED, SERVO_ACC);
  }
  else if (doc.containsKey("lightctrl")) {
    int led = doc["lightctrl"];
    lightCtrl(led);
  }
  else {
    request->send(400, "application/json", "{\"error\":\"No valid joint specified\"}");
    return;
  }

  request->send(200, "application/json", "{\"status\":\"OK\"}");
}



void setup() {
  Serial.begin(115200);
  Serial1.begin(1000000, SERIAL_8N1, S_RXD, S_TXD);


  switchPinInit();



  st.pSerial = &Serial1;

  torqueEnable();

  setupWiFi();
  connectToWiFi();

  // WiFi.softAP("Roarm", "12345678");
  // WiFi.begin(ssid, password);
  // WifiConnect();

  

  server.on("/controls", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", main_page);
  });
  server.onRequestBody([](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){
    if (request->url() == "/action" && request->method() == HTTP_POST) {
      web_movement(request, data, len);
    }
  });

//   server.on("/djs", HTTP_GET, [](AsyncWebServerRequest *request) {
//     request->send(200, "text/html", html_djs);
// });
  server.begin();

  Serial.println(WiFi.localIP());
  ElegantOTA.begin(&server);
  // lightCtrl(255);

}

void loop() {
  if (WiFi.status() != WL_CONNECTED && millis() - previousOnlineCheck > 2000) {
        Serial.println("Wifi Check1");
        // onlineMode = false;
        connectToWiFi();
        previousOnlineCheck = millis();
    }

  // lightCtrl(255);
  ElegantOTA.loop();
}