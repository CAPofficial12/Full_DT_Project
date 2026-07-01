#include <Arduino.h>
#include <WiFi.h>
#include <time.h>

// Internet details
const char* SSID = "TP-Link_1650";
const char* password = "57794884";

//NTP server
const char* server = "pool.ntp.org";

// TimeZone Offset
const long GMT_offset = 0;
const long DST_offset = 0;

void setup() {
  WiFi.begin(SSID, password);
  Serial.begin(115200);
  Serial.print("Connecting to Wifi...");
  while (WiFi.status() != WL_CONNECTED){  //Checks if ESP32 has connected to Wifi
    delay(300);
    Serial.print(".");
  }
  Serial.print("Connected to WiFi");
  configTime(GMT_offset, DST_offset, server);
  Serial.print("Time Initlaised");
}

void loop() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain Time");
    delay(1000);
    return;
  }

  Serial.printf("Date: %04d-%02d-%02d ",
                timeinfo.tm_year + 1900,
                timeinfo.tm_mon + 1,
                timeinfo.tm_mday);
  Serial.printf("Date: %04d-%02d-%02d \n",
                timeinfo.tm_hour,
                timeinfo.tm_min,
                timeinfo.tm_sec);
  delay(1000);
}