/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp32-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <esp_now.h>
#include <WiFi.h>


typedef struct struct_message {
  int id;
  int motion;
  String cause;
} struct_message;

// Create a struct_message called myData
struct_message myData;
// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  if(myData.motion==1)
  {
      Serial.print("Motion Detected in Zone number :");
      Serial.print(myData.id);
      Serial.print("\nCause :");
      Serial.print(myData.cause);
  }
  else{
    Serial.print("Zone number : ");
    Serial.print(myData.id);
    Serial.print(" NORMAL\n");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
  delay(4000);
}
 
void loop() {
esp_now_register_recv_cb(OnDataRecv);
delay(8000);
}