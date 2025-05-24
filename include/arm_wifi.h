#include <Preferences.h>

Preferences preferences;

const char *ssid_hotspot = "roarm_v1";
const char *password_hotspot = "12345678";

const char* htmlForm_wiFi = R"(
<!DOCTYPE html>
<html>
  <head>
    <title>ESP32 WiFi Config</title>
  </head>
  <body>
    <h1>Configure WiFi</h1>
    <form action="/save" method="POST">
      SSID: <input type="text" name="ssid" required /><br />
      Password: <input type="password" name="password" required /><br /><br />
      <input type="submit" value="Save" />
    </form>
  </body>
</html>
)"; 

void handleWifiCredentials(AsyncWebServerRequest *request) {
    preferences.end();
    preferences.begin("wifi-config", false);
    String ssid = request->getParam("ssid", true)->value();
    String password = request->getParam("password", true)->value();

    // Save SSID and password to Preferences
    preferences.putString("wifi_ssid", ssid);
    preferences.putString("wifi_password", password);

    // Respond with a message
    String response =
        "<html><body><h1>Credentials Saved</h1><p>ESP32 will try to connect to "
        "the new network.</p></body></html>";
    request->send(200, "text/html", response);
    Serial.println("saved");
    // Reboot ESP32 to apply new Wi-Fi credentials
    delay(1500);
    preferences.end();
    ESP.restart();
}


// Set the static IP for the ESP32 hotspot
// IPAddress local_ip(184, 95, 163, 21);
// IPAddress gateway(184, 95, 163, 21);
// IPAddress subnet(255, 255, 255, 0);

// IPAddress local_ip1(192, 168, 68, 250);
// IPAddress gateway1(192, 168, 68, 1);
// IPAddress dns1(8, 8, 8, 8);
// IPAddress dns2(1, 1, 1, 1);


void connectToWiFi() {
    // This function will try to connect to the saved Wi-Fi credentials
    preferences.begin("wifi-config", false);
    String ssid = preferences.getString("wifi_ssid", "");
    String password = preferences.getString("wifi_password", "");

    if (ssid.length() > 0 && password.length() > 0) {
      
    //   if (!WiFi.config(local_ip1, gateway1, subnet, dns1, dns2)) {
    //         Serial.println("STA Failed to configure static IP");
    //     }

        WiFi.begin(ssid.c_str(), password.c_str());

        unsigned long startAttemptTime = millis();
        while (WiFi.status() != WL_CONNECTED &&
               millis() - startAttemptTime < 4500) {
                 delay(500);
            Serial.print(".");
        }

        if (WiFi.status() == WL_CONNECTED) {
            Serial.println("Connected to WiFi!");
            Serial.print("IP Address: ");
            Serial.println(WiFi.localIP());
        } else {
            Serial.println("Failed to connect to WiFi");
        }
    }
    preferences.end();
}

void setupWiFi() {
    // WiFi.softAPConfig(local_ip, gateway, subnet);
    WiFi.softAP(ssid_hotspot, password_hotspot);

    // Print IP address to Serial
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());
  server.on("/wifi_config", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", htmlForm_wiFi);
  });
  server.on("/save", HTTP_POST, handleWifiCredentials);
}




