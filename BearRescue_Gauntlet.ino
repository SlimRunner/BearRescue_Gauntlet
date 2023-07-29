#include <AM232X.h>

#include "BearRescue_HackPublisher.hpp"
#include "BearRescue_Ultrasonic.hpp"
#include "BearRescue_Secrets.hpp"

const char *ssid = SSID;
const char *password = PASSWORD;
constexpr int ledPin = 13;

HackPublisher publisher("hackers");  // publisher instance for team "hackers"
int temp = 0;  // variable that holds the temperature

AM232X AM2320;

constexpr float C2F = 9 / 5 + 32;

constexpr int buzzerPin = 12;
constexpr int gasPin = A0;
constexpr int trigPin = 5;
constexpr int echoPin = 18;

int dist;
int gasVal;
int status;
int hum;
int temp;

inline float eqlTemp(int note) { return pow(2, note / 12.0) * 440; }

void introMelody() {
  pinMode(buzzerPin, INPUT);
  tone(buzzerPin, eqlTemp(2));
  delay(200);
  tone(buzzerPin, eqlTemp(0));
  delay(200);
  tone(buzzerPin, eqlTemp(4));
  delay(200);
  tone(buzzerPin, eqlTemp(7));
  delay(200);
  tone(buzzerPin, eqlTemp(12));
  delay(200);
  noTone(buzzerPin);
}

void setup() {
    // Initialize serial communication
  Serial.begin(115200);
  while (!Serial) continue;

  if (!AM2320.begin()) {
    Serial.println("Sensor not found");
    while(1);
  }

  AM2320.wakeUp();
  delay(200);

  // Connect to wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Initialize publisher
  publisher.begin();
  introMelody();
}

void loop() {
  // make sure ultrasonic sensor is on 5 V
  static UltrasonicSensor ultrasonic(trigPin, echoPin, DistUnit::CENTIMETERS);

  dist = ultrasonic.readDistance();
  gasVal = analogRead(gasPin);
  status = AM2320.read();
  hum = AM2320.getHumidity();
  temp = AM2320.getTemperature() * C2F;

  Serial.print(status);
  Serial.print(", ");
  Serial.print(hum);
  Serial.print(" %, ");
  Serial.print(temp);
  Serial.print(" F, ");
  Serial.print("gas: ");
  Serial.print(gasVal);
  Serial.print(", dist: ");
  Serial.print(dist);
  Serial.println(" cm");

  
  publisher.store("ultrasonic", dist); // store value for ultrasonic sensor
  publisher.store("humidity", hum);        // store value for temp
  publisher.store("temp", temp);        // store value for temp
  publisher.store("gas", gasVal);        // store value for temp
  // publisher.store("meow", "woof");      // store value for meow

  publisher.send();                     // send stored data to website
  delay(2000);
}
