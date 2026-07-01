#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <time.h>

// Internet details
const char* SSID = "TP-Link_1650";
const char* password = "57794884";

//NTP server
const char* ntpserver = "pool.ntp.org";

// TimeZone Offset
const long GMT_offset = 10800;
const long DST_offset = 0;

// ===== WEB =====
WebServer server(80);

// Format time
String getTimeString() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return "Time not ready";
  }
  char buf[32];
  strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &timeinfo);
  return String(buf);
}

// Root page
void handleRoot() {
  String page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <title>ESP32 Local Time</title>
  <meta http-equiv="refresh" content="1">
</head>
<body>
  <h2>ESP32 Local Time</h2>
  <p>)rawliteral" + getTimeString() + R"rawliteral(</p>
</body>
</html>
)rawliteral";

  server.send(200, "text/html", page);
}

void setup() {
  Serial.begin(115200);

  // WiFi
  WiFi.begin(SSID, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // mDNS name -> myhome.local
  if (!MDNS.begin("myhome")) {
    Serial.println("mDNS failed");
  } else {
    Serial.println("mDNS started: http://myhome.local/");
  }

  // Time
  configTime(GMT_offset, DST_offset, ntpserver);

  // Web server
  server.on("/", handleRoot);
  server.begin();

  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}
