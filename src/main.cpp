#include <Arduino.h>
#include <ArduinoJson.h>
#include <time.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

#include "sensorManager/ultrasonicSensorManager.h"
#include "getCurrentDate/getCurrentDate.cpp"
#include "secrets/secrets.h"
#include "wifiConnection/macAddressProvider.h"
#include "wifiConnection/httpHandler.h"

#define TIME_ZONE -5

WiFiClientSecure net;

BearSSL::X509List cert(cacert);
BearSSL::X509List client_crt(client_cert);
BearSSL::PrivateKey key(privkey);

PubSubClient client(net);

time_t now;
time_t nowish = 1510592825;

#define AWS_IOT_PUBLISH_TOPIC "esp8266/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp8266/sub"

const char* ssid = "Totalplay-FEAD";
const char* password = "FEAD2615BsXgYd6y";
const char* host = "api.trafficligh-iot.com";

unsigned long lastMillis = 0;

GetCurrentDate currentDate;
MacAddressProvider macProvider;
HTTPHandler httpHandler(ssid, password, host, 8000);

UltrasonicSensorManager ultrasonicSensorManager(12, 14); 

void NTPConnect(void) {
    Serial.print("Setting time using SNTP");
    configTime(TIME_ZONE * 3600, 0 * 3600, "pool.ntp.org", "time.nist.gov");
    now = time(nullptr);
    while (now < nowish) {
        delay(500);
        Serial.print(".");
        now = time(nullptr);
    }
    Serial.println("done!");
    struct tm timeinfo;
    gmtime_r(&now, &timeinfo);
    Serial.print("Current time: ");
    Serial.print(asctime(&timeinfo));
}

void connectAWS() {
    delay(3000);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.println(String("Attempting to connect to SSID: ") + String(WIFI_SSID));

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
    }

    NTPConnect();

    net.setTrustAnchors(&cert);
    net.setClientRSACert(&client_crt, &key);

    client.setServer(MQTT_HOST, 8883);

    Serial.println("Connecting to AWS IOT");

    while (!client.connect(THINGNAME)) {
        Serial.print(".");
        delay(1000);
    }

    if (!client.connected()) {
        Serial.println("AWS IoT Timeout!");
        return;
    }
    client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);

    Serial.println("AWS IoT Connected!");
}

void publishMessage(const String& jsonString) {
    if (client.connected()) {
        client.publish(AWS_IOT_PUBLISH_TOPIC, jsonString.c_str());
    } else {
        Serial.println("Error: MQTT client not connected");
    }
}

void setup() {
    Serial.begin(9600);
    connectAWS();
}

void loop() {
    now = time(nullptr);
    String macAddress = macProvider.getMacAddress();

    // Leer la distancia desde el sensor ultrasónico
    float distanceCm = ultrasonicSensorManager.getDistanceCm();

    // Crear el documento JSON con los datos de distancia
    DynamicJsonDocument jsonDocument(200);
    jsonDocument["distance_cm"] = distanceCm;
    jsonDocument["trafficligh_id"] = "1";
    jsonDocument["timestamp"] = currentDate.getCurrentDate();
    
    String jsonString;
    serializeJson(jsonDocument, jsonString);

    if (!client.connected()) {
        connectAWS();
    } else {
        client.loop();
        if (millis() - lastMillis > 5000) {
            lastMillis = millis();
            publishMessage(jsonString);
        }
    }
}
