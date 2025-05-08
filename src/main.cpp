#include "config.h"
#include "roarm_html.h"
#include "arm_functn.h"

// AsyncWebServer server(80);

const char* ssid = "moto";
const char* password = "123456789";

// void WifiConnect(){
//   while (WiFi.status() != WL_CONNECTED){
//     delay(500);
//     Serial.print(".");
//   }
// }
void  web_movement(AsyncWebServerRequest *request, uint8_t *data, size_t len){
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, data, len);
  if (error) {
      request->send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
      return;
  }
  
  position1 = doc["base"];
  st.WritePosEx(11, position1, SERVO_SPEED, SERVO_ACC);
}


void setup() {
  Serial.begin(115200);
  Serial1.begin(1000000, SERIAL_8N1, S_RXD, S_TXD);

  st.pSerial = &Serial1;

  torqueEnable();
  WiFi.softAP("Roarm", "12345678");
  // WiFi.begin(ssid, password);
  // WifiConnect();
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
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

}

void loop() {
  
}