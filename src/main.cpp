#include <Arduino.h>
/*********
Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-hc-sr04-ultrasonic-arduino/
*********/
const int trigPin = 12;
const int echoPin = 14;
//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034

long duration;
float distanceCm;
void setup() {
Serial.begin(9600); // Starts the serial communication
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}
void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculate the distance
distanceCm = duration * SOUND_VELOCITY/2;
// Convert to inches
// Print the distance to the terminal
if (distanceCm < 10) {
printf("1");
} else {
printf("0");
}
delay(1000);
}