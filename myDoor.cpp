#include "pins_arduino.h"
#include "Arduino.h"
#include "myDoor.h"

void OpenDoor(void)
{
  pinMode(LED, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}
void CloseDoor(void)
{
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}
