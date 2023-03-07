#ifndef myUID_h
#define myUID.h

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include "myDoor.h"

#define RST_PIN   9
#define SS_PIN    10 

void InitRFID(void);
byte UID_Compare (int ID1[4], int ID2[4]);
byte UID_Check(void);
void UID_State_Update(void);

#endif