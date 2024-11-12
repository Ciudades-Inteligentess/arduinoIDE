#ifndef MacAddressProvider_h
#define MacAddressProvider_h

#include <Arduino.h>
#include <ESP8266WiFi.h>

class MacAddressProvider{
    public:
        MacAddressProvider();
        String getMacAddress();

    private:
        String macAddress;
        void retrieveMacAddress();
};

#endif