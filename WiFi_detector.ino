#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

struct HttpClient {
  String ip;
  int count;
  unsigned long firstReq;
};
HttpClient clients[5];

// HTML content with proper form
const char* HTML_FORM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Test Page</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
  <h1>Login Form</h1>
  <form action="/login" method="POST">
    <input type="text" name="username" placeholder="Username">
    <input type="password" name="password" placeholder="Password">
    <input type="submit" value="Login">
  </form>
</body>
</html>
)rawliteral";

void handleRoot() {
  Serial.println("Serving root page");
  server.send(200, "text/html", HTML_FORM);
  trackRequest(server.client().remoteIP().toString());
}

void handleLogin() {
  Serial.println("Login attempt received");
  server.send(200, "text/plain", "Login Failed");
  trackRequest(server.client().remoteIP().toString());
}

void trackRequest(String ip) {
  Serial.print("Request from: ");
  Serial.println(ip);
  
  // Request tracking logic
  for(int i=0; i<5; i++) {
    if(clients[i].ip == ip) {
      clients[i].count++;
      if(clients[i].count >= 10 && (millis() - clients[i].firstReq) < 5000) {
        Serial.print("FLOOD:");
        Serial.println(ip);
        clients[i].count = 0;
      }
      return;
    }
  }
  
  // Add new client
  for(int i=0; i<5; i++) {
    if(clients[i].ip == "") {
      clients[i] = {ip, 1, millis()};
      break;
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(100);
  
  // WiFi Setup
  Serial.println("Creating AP...");
  WiFi.softAP("FloodDetector", "password123");
  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());

  // Server Routes
  server.on("/", handleRoot);
  server.on("/login", HTTP_POST, handleLogin);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  delay(2); // Prevent watchdog reset
  
  // Periodic client list reset
  static unsigned long lastReset = 0;
  if(millis() - lastReset > 5000) {
    for(int i=0; i<5; i++) clients[i] = {"", 0, 0};
    lastReset = millis();
    Serial.println("Client list reset");
  }
}
