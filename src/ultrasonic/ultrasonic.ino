#include <Wire.h>
#include <NewPing.h>

const uint8_t trigPin1 = 4;
const uint8_t echoPin1 = 3;
const uint8_t trigPin2 = 6;
const uint8_t echoPin2 = 5;
const uint8_t trigPin3 = 8;
const uint8_t echoPin3 = 7;

#define SONAR_NUM 3      // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(4, 3, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(6, 5, MAX_DISTANCE),
  NewPing(8, 7, MAX_DISTANCE)
};

unsigned int dist[3];

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  Wire.begin(6);

  Wire.onRequest(requestEvent);
}

void requestEvent() {
  if(dist[0] < 15 && dist[0] > 0 || dist[1] < 15 && dist[1] > 0 || dist[2] < 15 && dist[2] > 0) {
    Serial.println(String(dist[0]) + "\t" + String(dist[1]) + "\t" + String(dist[2]));
    Wire.write('s');
  } else {
    Wire.write('g');
  }
}

void loop() {
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor and display results.
    delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    dist[i] = sonar[i].ping_cm();
  }
}
