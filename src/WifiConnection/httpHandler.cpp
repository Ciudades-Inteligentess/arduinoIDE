// HTTPHandler.cpp
#include "wifiConnection/httpHandler.h"
#include <string>

HTTPHandler::HTTPHandler(const char *ssid, const char *password, const char *host, int port)
    : ssid(ssid), password(password), host(host), port(port) {}

void HTTPHandler::connectToWiFi() {
    Serial.print("Connecting Wifi: ");
    WiFi.begin(ssid, password);
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        Serial.print(".");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("");
        Serial.println("WiFi connected");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("");
        Serial.println("Failed to connect to WiFi");
        return;
    }
}

String HTTPHandler::makeHTTPRequest(std::string macAddress) {
    String url = "/api/trafficligh/?search=";
    url += macAddress.c_str();

    Serial.print("Connecting to ");
    Serial.println(url);

    String response;

    if (!client.connect(host, port)) {
        Serial.println(F("Connection failed"));
        return response;
    }
    
    client.print(F("GET "));
    client.print(url);
    client.print(F(" HTTP/1.1\r\n"));

    client.print(F("Host: "));
    client.print(host);
    client.print("\r\n");
    client.print(F("Connection: close\r\n\r\n"));

    while (client.connected()) {
        String line = client.readStringUntil('\n');
        if (line == "\r") {
            break;
        }
    }

    while (client.available()) {
        char c = client.read();
        response += c;
    }

    client.stop();

    return response;
}

