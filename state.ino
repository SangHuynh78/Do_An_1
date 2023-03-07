#include <Arduino.h>
#include "myDoor.h"
#include "myUID.h"

void setup() {
  Serial.begin(9600);
  InitRFID();
}

void loop() {
UID_State_Update();
}
