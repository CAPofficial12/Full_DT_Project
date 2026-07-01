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
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP32 Time</title>
  <style>
    body { font-family: Arial, sans-serif; margin: 24px; }
    .card { padding: 16px; border: 1px solid #ddd; border-radius: 12px; max-width: 420px; }
    #t { font-size: 1.6rem; font-weight: 700; }
    .small { color: #666; margin-top: 8px; }
  </style>
</head>
<body>
  <div class="card">
    <div>Current time:</div>
    <div id="t">Loading...</div>
    <div class="small">Updates every second</div>
  </div>

  <script>
    async function updateTime(){
      try{
        const r = await fetch('/time', { cache: 'no-store' });
        const text = await r.text();
        document.getElementById('t').textContent = text;
      } catch(e){
        document.getElementById('t').textContent = 'Error';
      }
    }
    updateTime();
    setInterval(updateTime, 1000);
  </script>
</body>
</html>
)rawliteral";

  server.send(200, "text/html", html);
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