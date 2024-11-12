#include "WifiConnection/WifiConnection.h"

WifiConnection::WifiConnection(const char *ssid, const char *password)
    : ssid(ssid), password(password) {}

void WifiConnection::connect() {
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");
}

bool WifiConnection::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}
