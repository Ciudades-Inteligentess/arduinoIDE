#include "sensorManager/ultrasonicSensorManager.h"

#define SOUND_VELOCITY 0.034  // Velocidad del sonido en cm/μs

UltrasonicSensorManager::UltrasonicSensorManager(int trigPin, int echoPin) {
    _trigPin = trigPin;
    _echoPin = echoPin;
    pinMode(_trigPin, OUTPUT);
    pinMode(_echoPin, INPUT);
}

float UltrasonicSensorManager::getDistanceCm() {
    // Generar un pulso en el trigPin
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);

    // Medir el tiempo de viaje del pulso
    long duration = pulseIn(_echoPin, HIGH);

    // Calcular la distancia en cm
    float distanceCm = duration * SOUND_VELOCITY / 2;
    return distanceCm;
}
