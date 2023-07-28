#include "BearRescue_HackPublisher.hpp"
#include "BearRescue_Ultrasonic.hpp"
#include "BearRescue_Secrets.hpp"

const char *ssid = SSID;
const char *password = PASSWORD;
constexpr int ledPin = 13;

HackPublisher publisher("hackers");  // publisher instance for team "hackers"
int temp = 0;  // variable that holds the temperature

void setup() {
    // Initialize serial communication
  Serial.begin(115200);
  while (!Serial) continue;

  // Connect to wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Initialize publisher
  publisher.begin();
}

void loop() {
  publisher.store("ultrasonic", 12.56); // store value for ultrasonic sensor
  publisher.store("temp", temp);        // store value for temp
  publisher.store("meow", "woof");      // store value for meow

  publisher.send();                     // send stored data to website

  delay(2000);
  temp++;
}
