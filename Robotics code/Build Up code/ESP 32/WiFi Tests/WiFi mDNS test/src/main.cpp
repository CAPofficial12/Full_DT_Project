#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <time.h>

// ================== CHANGE THESE ==================
const char* SSID = "TP-Link_1650";
const char* password = "57794884";

//NTP server
const char* ntpServer = "pool.ntp.org";

// TimeZone Offset
const long GMT_offset = 10800;
const long DST_offset = 0;

// mDNS name -> http://myhome.local/
const char* mdnsName = "myhome";
// ==================================================

WebServer server(80);

String getTimeString() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return "Time not ready (NTP sync)";
  }
  char buf[32];
  strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &timeinfo);
  return String(buf);
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
    setInterval(updateTime, 50);
  </script>
</body>
</html>
)rawliteral";

  server.send(200, "text/html", page);
}

void handleTime() {
  server.send(200, "text/plain", getTimeString());
}

void setup() {
  Serial.begin(115200);

  // Wi-Fi connect
  WiFi.begin(SSID, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());

  // Start mDNS
  if (!MDNS.begin(mdnsName)) {
    Serial.println("mDNS start FAILED");
  } else {
    Serial.print("mDNS started: http://");
    Serial.print(mdnsName);
    Serial.println(".local/");
  }

  // NTP time
  configTime(GMT_offset, DST_offset, ntpServer);

  // Web routes
  server.on("/", handleRoot);
  server.on("/time", handleTime);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}