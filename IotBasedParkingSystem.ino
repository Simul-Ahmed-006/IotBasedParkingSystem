#include "WiFi.h"
#include <HTTPClient.h>

// Defining LED PINs on the ESP32 Board.
#define On_Board_LED_PIN  2


const int irPins[] = {26, 25, 33, 32, 35, 34};
const int numSensors = 6;
String Slot[6] ; // Store pin numbers as integers
// Google script Web_App_URL.
String Web_App_URL = "https://script.google.com/macros/s/AKfycbxyJI5C1ER_ny99EZ2oJhCEC2zRveaktq64joqZ9kJwZjP7NZrBpH5xcEmLn2vFlr3V/exec?sts=write&"; // ADD ?sts=write&

//----------------------------------------SSID and PASSWORD of your WiFi network.
const char* ssid = "5G";  //--> Your wifi name
const char* password = "mizan880389"; //--> Your wifi password
//----------------------------------------




//________________________________________________________________________________VOID SETUP()
void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
   delay(1000);
  for (int i = 0; i < numSensors; i++) {
  pinMode(irPins[i], INPUT);
  }
  Serial.println(); 
  pinMode(On_Board_LED_PIN, OUTPUT);

  //----------------------------------------Set Wifi to STA mode
  Serial.println();
  Serial.println("-------------");
  Serial.println("WIFI mode : STA");
  WiFi.mode(WIFI_STA);
  Serial.println("-------------");
  //---------------------------------------- 

  //----------------------------------------Connect to Wi-Fi (STA).
  Serial.println();
  Serial.println("------------");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  //:::::::::::::::::: The process of connecting ESP32 with WiFi Hotspot / WiFi Router.
  // The process timeout of connecting ESP32 with WiFi Hotspot / WiFi Router is 20 seconds.
  // If within 20 seconds the ESP32 has not been successfully connected to WiFi, the ESP32 will restart.
  // I made this condition because on my ESP32, there are times when it seems like it can't connect to WiFi, so it needs to be restarted to be able to connect to WiFi.

  int connecting_process_timed_out = 20; //--> 20 = 20 seconds.
  connecting_process_timed_out = connecting_process_timed_out * 2;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(On_Board_LED_PIN, HIGH);
    delay(250);
    digitalWrite(On_Board_LED_PIN, LOW);
    delay(250);
    if (connecting_process_timed_out > 0) connecting_process_timed_out--;
    if (connecting_process_timed_out == 0) {
      delay(1000);
      ESP.restart();
    }
  }

  digitalWrite(On_Board_LED_PIN, LOW);
  
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("------------");
  //::::::::::::::::::
  //----------------------------------------

 
}
//________________________________________________________________________________

//________________________________________________________________________________VOID LOOP()
void loop() {
 
  for (int i = 0; i < numSensors; i++) {
    int sensorValue = digitalRead(irPins[i]);
    if (sensorValue == 0) {
      Slot[i] = "Occupied";
      Serial.print("Slot ");
      Serial.print(i);
      Serial.println(": Occupied");
    } else {
      Slot[i] = "Available";
      Serial.print("Slot ");
      Serial.print(i);
      Serial.println(": Available");
    }
  }
String Send_Data_URL = Web_App_URL + "slot0=" + Slot[0] + "&slot1=" + Slot[1] + "&slot2=" + Slot[2] + "&slot3=" + Slot[3] + "&slot4=" + Slot[4] + "&slot5=" + Slot[5];
  //----------------------------------------Conditions that are executed when WiFi is connected.
  // This condition is the condition for sending or writing data to Google Sheets.
  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(On_Board_LED_PIN, HIGH);



    Serial.println();
    Serial.println("-------------");
    Serial.println("Send data to Google Spreadsheet...");
    Serial.print("URL : ");
    Serial.println(Send_Data_URL);

    //::::::::::::::::::The process of sending or writing data to Google Sheets.
      // Initialize HTTPClient as "http".
      HTTPClient http;
  
      // HTTP GET Request.
      http.begin(Send_Data_URL.c_str());
      http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  
      // Gets the HTTP status code.
      int httpCode = http.GET(); 
      Serial.print("HTTP Status Code : ");
      Serial.println(httpCode);
  
      // Getting response from google sheets.
      String payload;
      if (httpCode > 0) {
        payload = http.getString();
        Serial.println("Payload : " + payload);    
      }
      
      http.end();
    //::::::::::::::::::
    
    digitalWrite(On_Board_LED_PIN, LOW);
    Serial.println("-------------");
  }
  //----------------------------------------

  delay(5000);
}
//________________________________________________________________________________
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




