#include <AM232X.h>
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#include "BearRescue_HackPublisher.hpp"
#include "BearRescue_Ultrasonic.hpp"
#include "BearRescue_Secrets.hpp"

constexpr int LED_PIN = 19;
constexpr int LED_COUNT = 12;
constexpr int RING_BRIGHTNESS = 50;

const char *ssid = SSID;
const char *password = PASSWORD;
constexpr int ledPin = 13;

float C2F(int t) {
  return t * 9 / 5 + 32;
};

Adafruit_NeoPixel ledring(LED_COUNT, LED_PIN, NEO_GRB | NEO_KHZ800);

constexpr int buzzerPin = 12;
constexpr int gasPin = A1;
constexpr int trigPin = 5;
constexpr int echoPin = 18;

HackPublisher publisher("BearRescue");  // publisher instance for team "hackers"
AM232X AM2320;
// make sure ultrasonic sensor is on 5 V
static UltrasonicSensor ultrasonic(trigPin, echoPin, DistUnit::CENTIMETERS);

int dist;
int gasVal;
int status;
int hum;
int temp;

inline void playNote(int note) {
  tone(buzzerPin, pow(2, note / 12.0) * 440);
}

void introMelody() {
  constexpr int NOTE_DELAY = 200;
  pinMode(buzzerPin, INPUT);
  playNote(2);
  delay(NOTE_DELAY);
  playNote(0);
  delay(NOTE_DELAY);
  playNote(4);
  delay(NOTE_DELAY);
  playNote(7);
  delay(NOTE_DELAY);
  playNote(12);
  delay(NOTE_DELAY);
  noTone(buzzerPin);
}

void setup() {
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif

    // Initialize serial communication
  Serial.begin(115200);
  while (!Serial) continue;

  pinMode(gasPin, INPUT);

  ledring.begin();
  ledring.setBrightness(RING_BRIGHTNESS);
  ledring.setPixelColor(0,255,128,50);
  ledring.setPixelColor(2,255,128,50);
  ledring.setPixelColor(5,255,128,50);
  ledring.show();

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
  gasVal = analogRead(gasPin);
  dist = ultrasonic.readDistance();
  status = AM2320.read();
  hum = AM2320.getHumidity();
  temp = C2F(AM2320.getTemperature());

  Serial.print((!status ? "ok, ": "not ok, "));
  Serial.print(hum);
  Serial.print(" %, ");
  Serial.print(temp);
  Serial.print(" F, ");
  Serial.print("gas: ");
  Serial.print(gasVal);
  Serial.print(", dist: ");
  Serial.print(dist);
  Serial.println(" cm");
  
  publisher.store("humidity", hum);        // store value for temp
  publisher.store("temperature", temp);        // store value for temp
  publisher.store("gas", gasVal);        // store value for temp
  publisher.store("ultrasonic", dist); // store value for ultrasonic sensor
  // publisher.store("meow", "woof");      // store value for meow

  publisher.send();                     // send stored data to website
  delay(2000);
}
