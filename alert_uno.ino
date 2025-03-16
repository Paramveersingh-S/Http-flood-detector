#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int RED = 10, GREEN = 12, BUZZER = 13;
bool alertActive = false;
unsigned long alertStart = 0;

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(115200);
  
  lcd.init();
  lcd.backlight();
  lcd.print("System Ready");
  digitalWrite(GREEN, HIGH);
}

void loop() {
  // Handle serial input
  if(Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    
    if(input.startsWith("FLOOD:")) {
      String ip = input.substring(6);
      triggerAlert(ip);
    }
  }

  // Manage alert state
  if(alertActive && millis() - alertStart > 10000) {
    resetSystem();
  }
}

void triggerAlert(String ip) {
  alertActive = true;
  alertStart = millis();
  
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, HIGH);
  tone(BUZZER, 1000);
  
  lcd.clear();
  lcd.print("HTTP Flood Detected");
  lcd.setCursor(0, 1);
  lcd.print("IP: " + ip);
}

void resetSystem() {
  alertActive = false;
  digitalWrite(RED, LOW);
  noTone(BUZZER);
  digitalWrite(GREEN, HIGH);
  lcd.clear();
  lcd.print("Monitoring...");
}
