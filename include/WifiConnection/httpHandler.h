#ifndef HTTP_HANDLER_H
#define HTTP_HANDLER_H

#include <ESP8266WiFi.h>
#include <WiFiClient.h>

class HTTPHandler {
public:
    HTTPHandler(const char *ssid, const char *password, const char *host, int port);
    void connectToWiFi();
    String makeHTTPRequest(std::string macAddress);
private:
    const char *ssid;
    const char *password;
    const char *host;
    int port;
    WiFiClient client;
};

#endif
