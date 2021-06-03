#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10
MFRC522 module_rfid(SS_PIN, RST_PIN);

const int buttonPin = 5;

int serrure = 6;
int led_rouge = 4;
int led_verte = 3;
int buzz = 2;
int buttonState = 0;

void setup() {
  pinMode(led_rouge, OUTPUT);
  pinMode(led_verte, OUTPUT);
  pinMode(buttonPin, INPUT);
  SPI.begin();
  module_rfid.PCD_Init();

  //animation démarrage
  
  delay(50);
  digitalWrite(led_verte,1);
  tone(buzz,2093, 150); delay(150);
  digitalWrite(led_verte,0); delay(150);
  tone(buzz, 2093, 150); digitalWrite(led_verte,1); delay(150);
  digitalWrite(led_verte,0);

}

void loop() {

  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) { //ouverture avec boutton
    // turn LED on:
    digitalWrite(led_verte, HIGH);
    digitalWrite(serrure, HIGH);
    tone(buzz,523,50);
    delay(50);
    tone(buzz, 783, 50);
    delay(50);
    tone(buzz, 1046, 50);
    delay(50);
    tone(buzz, 1568, 50);
    delay(50);
    tone(buzz, 2093, 70);
    delay(250);
    delay(3000);
    digitalWrite(led_verte, LOW);
    digitalWrite(serrure, LOW);
  } else {
    // turn LED off:
    digitalWrite(led_rouge, LOW);
  }
  
  if ( ! module_rfid.PICC_IsNewCardPresent()) 
  {
    return;
  }

  if ( ! module_rfid.PICC_ReadCardSerial()) 
  {
    return;
  }

  String UID = "";

  for (byte i = 0; i < module_rfid.uid.size; i++) {
    UID.concat(String(module_rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    UID.concat(String(module_rfid.uid.uidByte[i], HEX));
  }

  UID.toUpperCase(); 
  
  if ((UID.substring(1) == "C2 11 BE 6E" )  || (UID.substring(1) == "1B 77 65 22" )  || (UID.substring(1) == "7B B8 63 EF" ) ) //verifie si l'udi recup correspond a l'un de la liste
 {
    digitalWrite(serrure, HIGH);
    digitalWrite(led_verte, HIGH);
    tone(buzz,523,50);
    delay(50);
    tone(buzz, 783, 50);
    delay(50);
    tone(buzz, 1046, 50);
    delay(50);
    tone(buzz, 1568, 50);
    delay(50);
    tone(buzz, 2093, 70);
    delay(250);
    
    delay(1500);
    digitalWrite(led_verte, LOW);
    digitalWrite(serrure, LOW);
  }
    else {
    digitalWrite(led_rouge, HIGH);
    tone(buzz,370,50);
    delay(100);
    tone(buzz, 370, 300);
    delay(2000);
    digitalWrite(led_rouge, LOW);
  }
    }
