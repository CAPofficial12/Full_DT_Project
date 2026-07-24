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

// Web Server
WebServer server(80);
String mDNS = "time";

String formatTimeNow(){
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)){
    return String("Failed to obtain Time");
    delay(1000);
    return "";
  }

  char time [32];
  strftime(time, sizeof(time), "%Y-%m-%d %H:%M:%S", &timeinfo);
  return String(time);
}

void handleRoot() {
  // Smooth updates: page loads once, then fetches /time every second
  String page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP32 Time</title>
  <style>
    body { font-family: Arial, sans-serif; margin: 24px; }
    .card { padding: 16px; border: 1px solid #ddd; border-radius: 12px; max-width: 420px; }
    #clock { font-size: 1.8rem; font-weight: 700; margin-top: 8px; }
    .small { color: #666; margin-top: 10px; }
  </style>
</head>
<body>
  <div class="card">
    <div>Current time:</div>
    <div id="clock">Loading...</div>
    <div class="small">Updates every second • Served by ESP32</div>
  </div>

  <script>
    async function updateTime() {
      try {
        const r = await fetch('/time', { cache: 'no-store' });
        const t = await r.text();
        document.getElementById('clock').textContent = t;
      } catch (e) {
        document.getElementById('clock').textContent = 'Error getting time';
      }
    }
    updateTime();
    setInterval(updateTime, 1000);
  </script>
</body>
</html>
)rawliteral";

  server.send(200, "text/html", page);
}

void handleTime(){
  server.send(200, "text/plain", formatTimeNow());
}

void setup(){
  Serial.begin(115200);

  WiFi.begin(SSID, password);
  Serial.print("Conting to WiFi");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  
  Serial.println("\n WiFi Connected");
  Serial.print("ESP32 IPv4 address: ");
  Serial.println(WiFi.localIP());
  Serial.print("ESP32 IPv6 address: ");
  Serial.println(WiFi.localIPv6());

  if (!MDNS.begin(mDNS)) {
    Serial.println("mDNS failed");
  } else {
    Serial.print("mDNS started: http://");
    Serial.print(mDNS);
    Serial.println(".local/");
  }

  configTime(GMT_offset, DST_offset, ntpserver);

  Serial.println("Syncing time...");
  for (int i = 0; i < 15; i++) {
    if (formatTimeNow().indexOf("not available") == -1) break;
    delay(500);
  }
  Serial.println("Current time: " + formatTimeNow());

  // Web routes
  server.on("/", handleRoot);
  server.on("/time", handleTime);

  server.begin();
  Serial.println("Web server started. Open the IPv4 adress in your browser.");
}

void loop(){
  server.handleClient();
}