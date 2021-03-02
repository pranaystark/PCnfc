#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN D4
#define RST_PIN D2
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 #ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>
// define the GPIO connected with Relays
#define RelayPin1 D8
//D1
// prototypes
boolean connectWifi();
//callback functions
void firstLightChanged(uint8_t brightness);
// WiFi Credentials
const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";
String Device_1_Name = "unlock computer";
boolean wifiConnected = false;
Espalexa espalexa;
void setup() 
{
  
  pinMode(RelayPin1, OUTPUT);
 digitalWrite(RelayPin1, HIGH); 
  pinMode(LED_BUILTIN, OUTPUT);
   // Initialise wifi connection
  wifiConnected = connectWifi();
  if (wifiConnected)
  {
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
    // Define your devices here.
    espalexa.addDevice(Device_1_Name, firstLightChanged); //simplest definition, default state off


    espalexa.begin();
  }
  else
  {
    while (1)
    {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }


}
void loop() 
{
  espalexa.loop();
  delay(1);
  
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
 byte  i = 00;
 if (i == 00){
  
  for (byte i = 00; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));

  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "04 88 AA FA 97 3B 80")//change here the UID of the card/cards that you want to give access
     
    Serial.println("Authorized access");
                        // wait for a second
      digitalWrite(RelayPin1, LOW);
      Serial.println("Device1 ON");
    Serial.println();
    delay(15000);
     digitalWrite(RelayPin1, HIGH);
    Serial.println("Device1 OFF");
    Serial.println("im in loop one");
  
  }
  else { 

  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
 
    
          for (byte i = 00; i < mfrc522.uid.size; i--) 
 {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.println("1");//Debug
     Serial.println();
  
     
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     Serial.println("2"); //Debug
     Serial.println();
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      Serial.println("3");//Debug
      Serial.println();
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
     Serial.println();
     Serial.println("im in else loop if ");//Debug
  
 
  Serial.print("Message : ");

    if (content.substring(1) == "08" )//change here the UID of the card/cards that you want to give access, fortunately this method only reads first two digits so, this makes it less secure  
  {
     
    Serial.println("Authorized access");
                        // wait for a second
      digitalWrite(RelayPin1, LOW);
      Serial.println("Device1 ON");
    Serial.println();
    delay(15000);
     digitalWrite(RelayPin1, HIGH);
    Serial.println("Device1 OFF");
     Serial.println("im in else loop if if "); //Debug
    
  }
   else   {
    Serial.println(" Access denied");
    digitalWrite(RelayPin1, HIGH);
    Serial.println("Device1 OFF");

    delay(3000);
    Serial.println("im in else loop if if else "); //Debug
  }
    }
 

}
}
}
void firstLightChanged(uint8_t brightness)
{
  //Control the device using alexa 
  if (brightness == 255)
    {
      digitalWrite(RelayPin1, LOW);
      Serial.println("Device1 ON");
       delay(15000);
     digitalWrite(RelayPin1, HIGH);
    Serial.println("Device1 OFF");
    
    }
  else
  {
    digitalWrite(RelayPin1, HIGH);
    Serial.println("Device1 OFF");
  }
} 
// connect to wifi  returns true if successful or false if not
boolean connectWifi()
{
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20) {
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state) {
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}
