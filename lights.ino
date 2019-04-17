#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// WiFi connection info
#define WIFISSID "YourWifiName"
#define WIFIPASSWORD "YourWifiPassword"

// Whichever pin on your arduino you connect the 
// MOSFET transistor to
#define PIN D8

// web server info
const char* host = "your.host.server.com";

// Global brightness variable
int brightness = 50;


// Initial setup
void setup() {
  Serial.begin(9600);
  pinMode(D8, OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFISSID, WIFIPASSWORD);
}


// Loop function
void loop() {

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient client;
    
    // Server should return single string brightness value, e.g. "100"
    //  ranging from 0-1023
    client.begin(host);
    
    int httpCode = client.GET();

    // Check that our request succeeded
    if(httpCode == 200) {
      String payload = client.getString();

      // Clean our input
      int new_brightness = constrain(payload.toInt(), 0, 1023);
   
      // Make the lights fade into our new desired brightness
      while(new_brightness != brightness) {
        int diff = (new_brightness - brightness)/40;
        if(diff < 1) {
          while(brightness < new_brightness) {
            brightness++;
            analogWrite(D8, brightness);
            delay(10);
          }
          brightness = new_brightness;
          analogWrite(D8, brightness);
          break;
        }
        brightness += diff;
        analogWrite(D8, brightness);
        delay(10);
      }
    }
    client.end();
  }
  delay(100); // Check for changes 10 times per second
  return;
} 
