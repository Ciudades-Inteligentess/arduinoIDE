// include/WifiConnection.h
#ifndef WIFI_CONNECTION_H
#define WIFI_CONNECTION_H

#include <ESP8266WiFi.h>

class WifiConnection {
    public:
        WifiConnection(const char *ssid, const char *password);
        void connect();
        bool isConnected();

    private:
        const char *ssid;
        const char *password;
};

#endif