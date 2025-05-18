#include <Arduino.h>
#include <ArduinoJson.h>
#include <SCServo.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include <ElegantOTA.h>

SMS_STS st;
AsyncWebServer server(80);

#define S_RXD 18
#define S_TXD 19

// const int servoID = 1;

#define SERVO_1_ID 12
#define SERVO_2_ID 13

#define SERVO_0_ID 11
#define SERVO_3_ID 14
#define SERVO_4_ID 15
#define SERVO_5_ID 1

#define SERVO_SPEED 600
#define SERVO_ACC 15

int initialPosition = 2047;
short position1 = initialPosition;
short position2 = initialPosition;
short position3 = initialPosition;
short position4 = initialPosition;
short position5 = initialPosition;
short position6 = initialPosition;

