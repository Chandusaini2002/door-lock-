
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 int led = 7;
int  motor = 6;
int brzz = 5;

int redled = 4;

void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
pinMode(led ,OUTPUT);
    pinMode(motor ,OUTPUT);
    
pinMode(redled ,OUTPUT);
pinMode(brzz ,OUTPUT);
}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "D5 79 19 53") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    
        digitalWrite(led ,HIGH);
         digitalWrite(motor ,HIGH);
        delay(3000);
        
        digitalWrite(led ,LOW);
        delay(3000);
        
        digitalWrite(motor ,LOW);
  }
 
 else   {
    Serial.println(" Access denied");
    
        digitalWrite(brzz ,HIGH);
         digitalWrite(redled ,HIGH);
        delay(3000);
        digitalWrite(redled ,LOW);
        delay(3000);
        digitalWrite(brzz ,LOW);
        delay(3000);
        
        
        }
} 