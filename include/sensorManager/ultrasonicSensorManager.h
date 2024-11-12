#ifndef ULTRASONIC_SENSOR_MANAGER_H
#define ULTRASONIC_SENSOR_MANAGER_H

#include <Arduino.h>

class UltrasonicSensorManager {
    public:
        UltrasonicSensorManager(int trigPin, int echoPin);
        float getDistanceCm();
    private:
        int _trigPin;
        int _echoPin;
};

#endif
