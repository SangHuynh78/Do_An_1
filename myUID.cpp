#include "myUID.h"

int UID[4], i;
int UID1[4] = {129,88,223,28};
int UID2[4] = {129,30,26,28};

MFRC522 mfrc522(SS_PIN, RST_PIN);

void InitRFID(void)
{
  SPI.begin();
  mfrc522.PCD_Init();
}

byte UID_Compare(int ID1[4], int ID2[4])
{
  for (byte i=0; i< 4; i++) {
    if (ID1[i] != ID2[i]) { return 0; }
  }
  return 1;
}

byte UID_Check()
{
  if ( !mfrc522.PICC_IsNewCardPresent() )
  {
    return 0;
  }
  if ( !mfrc522.PICC_ReadCardSerial() )
  {
    return 0;
  }
  
  Serial.print("UID cua the: ");

  for (byte i = 0; i < mfrc522.uid.size; i++)
  {

    UID[i] = mfrc522.uid.uidByte[i];
    Serial.print(UID[i]);
    Serial.print(mfrc522.uid.uidByte[i] < 100 ? "  " : " ");
  }
  Serial.println();
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  if (UID_Compare(UID, UID1) || UID_Compare(UID, UID2) ) {UID[4] = (0,0,0,0);return 1;}
  else {UID[4] = (0,0,0,0);return 0;}
}

typedef enum{ S_CLOSE=0, S_OPEN, S_WAIT5S} UIDState_t;
static UIDState_t UIDState = S_CLOSE;
int UID_Timer;

void UID_State_Update(void)
{
  //chuyen trang thai
  switch (UIDState) {
  case S_CLOSE:
    if (UID_Check()) UIDState = S_OPEN;
    break;
  case S_OPEN:
    UIDState = S_WAIT5S;
    UID_Timer = 5000;
    break;
  case S_WAIT5S:
    UIDState = S_CLOSE;
    break;
  }

    //chuc nang
  switch (UIDState) {
  case S_CLOSE:
    CloseDoor();
    break;
  case S_OPEN:
    Serial.println("Dung");
    break;
  case S_WAIT5S:
    OpenDoor();
//delay(5000);
    Serial.println("wait");
    break;
  }
}
