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
#include "NewPing.h"
#include <stdlib.h>

NewPing s(33,33,400);

uint8_t broadcastAddress[] = {0x78, 0xE3, 0x6D, 0x0A, 0xF3, 0x58};

typedef struct struct_message {
  int id;
  int motion;
  String cause;
} struct_message;

struct_message myData;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return; 
  }
}
 int temp,hum,dist,motion;
void loop() {

  // Set values to send
  if(analogRead(21)>1900);
  {
    Serial.print(analogRead(12));
    myData.motion=digitalRead(35);
    //Serial.println(digitalRead(35));
  myData.id=rand()%10+1;
    if(digitalRead(35)==1)
  {
    Serial.println(digitalRead(35));
  if(s.ping_cm()<275){
    myData.cause="potentially a person";
  }
  else
  {
    myData.cause="probably some small animal";
  }
  }
  else
  {
    myData.cause="no motion";
  }
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(7000);
  }
}