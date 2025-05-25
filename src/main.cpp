#include "config.h"
#include "roarm_html.h"
#include "arm_functn.h"
#include "led_ctrl.h"
#include "arm_wifi.h"
#include "p_supply.h"

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
    position[0] = doc["sholder"];
    // position3 = 2047 + (2047 - position2) + 1;
    position[1] = 4095 - position[0];
    // byte ID[2] = {12, 13};
    // short position[2] = {position2, position3};
    // unsigned short speed[2] = {300, 300};  // Speed for both servos
    // byte acc[2] = {15, 15};
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
  Wire.begin(S_SDA,S_SCL);
  Serial.begin(115200);
  Serial1.begin(1000000, SERIAL_8N1, S_RXD, S_TXD);
  InitINA219();

  switchPinInit();



  st.pSerial = &Serial1;

  torqueEnable();

  setupWiFi();
  connectToWiFi();

  if (!MDNS.begin("roarm")) {
    Serial.println("Error starting mDNS");
    return;
  }

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

  server.on("/battery", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", htmlPage);
      });
      server.on("/temps", HTTP_GET, [](AsyncWebServerRequest *request){
        String json = "{";
        json += "\"temp1\":" + String(loadVoltage_V) + ",";
        json += "\"temp2\":" + String(current_mA);
        json += "}";
        request->send(200, "application/json", json);
        // Serial.println(json);
    });

  server.begin();

  Serial.println(WiFi.localIP());
  ElegantOTA.begin(&server);
  lightCtrl(255);

}

void loop() {
  if (WiFi.status() != WL_CONNECTED && millis() - previousOnlineCheck > 12000) {
        Serial.println("Wifi Check1");
        // onlineMode = false;
        connectToWiFi();
        previousOnlineCheck = millis();
    }
    st.WritePosEx(15, 1000, SERVO_SPEED, SERVO_ACC);
    delay(6000);
    st.WritePosEx(15, 2047, SERVO_SPEED, SERVO_ACC);
    delay(6000);
    st.WritePosEx(14, 2900, SERVO_SPEED, SERVO_ACC);
    delay(6000);
    st.WritePosEx(14, 1100, SERVO_SPEED, SERVO_ACC);
    delay(9000);
    position[0] = 1250;
    position[1] = 4095 - position[0];
    st.SyncWritePosEx(ID, 2, position, speed, acc);
    delay(9000);
    position[0] = 2700;
    position[1] = 4095 - position[0];
    st.SyncWritePosEx(ID, 2, position, speed, acc);
    delay(9000);
    position[0] = 2047;
    position[1] = 4095 - position[0];
    st.SyncWritePosEx(ID, 2, position, speed, acc);
    delay(9000);
    st.WritePosEx(11, 0, SERVO_SPEED, SERVO_ACC);
    delay(9000);
    st.WritePosEx(11, 4095, SERVO_SPEED, SERVO_ACC);
    delay(9000);
    st.WritePosEx(11, 3000, SERVO_SPEED, SERVO_ACC);
    delay(6000);

    

  
    InaDataUpdate();
    // allDataUpdate();

  // lightCtrl(255);
  ElegantOTA.loop();
}