#include <Arduino.h>
#include <SCServo.h>
#include <ESPAsyncWebServer>
#include "roarm_html.h"

// put function declarations here:
int myFunction(int, int);

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() {
  
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}