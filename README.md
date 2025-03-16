# Http-flood-detector
NodeMCU V3 + Arduino Uno based Http flooding Detector
# WiFi Attack Detection System  
**Detect Deauthentication & HTTP Flood Attacks with ESP8266 & Arduino Uno**  

---

## 📝 Description  
This system detects two common WiFi attacks in real-time:   
1. **HTTP Flood Attacks**: Excessive requests overwhelming web servers  

**Components**:  
- **ESP8266**: Sniffs WiFi packets ,hosts attack detection logic and host website server  
- **Arduino Uno**: Controls alerts (LEDs, buzzer, LCD)  
- **I2C LCD**: Displays attack details  
- **LEDs & Buzzer**: Visual/audio alerts  

---

## 🚀 Features  
- Real-time attack detection  
- Visual (LEDs/LCD) and audible (buzzer) alerts  
- Web interface for HTTP flood monitoring  
- Auto-reset after 10 seconds  

---

## 📦 Hardware Components  
| Component          | Quantity |  
|---------------------|----------|  
| Arduino Uno         | 1        |  
| ESP8266 (NodeMCU)   | 1        |  
| I2C LCD (16x2)      | 1        |  
| Red LED             | 1        |  
| Green LED           | 1        |  
| Buzzer              | 1        |  
| 220Ω Resistors      | 2        |  
| Breadboard          | 1        |
| Jumper wires M to F | 10       |

---

## 🔌 Wiring Guide  
| Component       | Arduino Pin | ESP8266 Pin | Notes |  
|-----------------|-------------|-------------|-------|  
| Red LED         | 11          | -           | 220Ω resistor |  
| Green LED       | 12          | -           | 220Ω resistor |  
| Buzzer (+)      | 13          | -           |   
| I2C LCD SDA     | A4          | -           |   
| I2C LCD SCL     | A5          | -           | 
| ESP8266 TX      | RX (0)      | TX (GPIO1)  |    
| ESP8266 GND     | GND         | GND         | 
| ESP8266         | 3.3V        | 3V          |
