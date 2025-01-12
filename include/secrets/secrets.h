#include <pgmspace.h>
 
#define SECRET
 
const char WIFI_SSID[] =  "Totalplay-FEAD";
const char WIFI_PASSWORD[] = "FEAD2615BsXgYd6y";
 
#define THINGNAME "ESP8266"
 
int8_t TIME_ZONE = -5;
 
const char MQTT_HOST[] = "a2322ms7oczm3t-ats.iot.us-east-1.amazonaws.com";
 
static const char cacert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";
 
static const char client_cert[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUOfLCTPItQ3nW4FNPF+ZLNxvfCzowDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI0MTExMjE5MTEx
N1oXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALxhJl+7ZvIAdA7x14br
q7YLon0ptphKTrw7sZQ8mm939NgV0jKrqSDzGUWHPMjly3qr71Nai6zJq4jb2U2b
hB3n4W2ZTjetoOgSQTPuDTZw340JO4jVbm/LWNWgD5Y4EuS6Fz0hKbFPpmauuQ9k
52YPaTfr0jDHCTNusHk5ON71wCEscPujVLl6s8CrEnx/MUReDYepO6iwPtzA6ad6
BAZrHSSxg4spLh1m6lWIhimpgvgruY2JT/X2d1HFhGj2IYxSRXrCGsCFUaoqNhgY
hsjeaYrMd+H512hgCPpkXU85Naq45/w2MklTYNJoACTS5gim4Chi724odn1FgGgh
TKkCAwEAAaNgMF4wHwYDVR0jBBgwFoAULRSHHlgvwNld1W22snuJvoJHrA8wHQYD
VR0OBBYEFAl2yFcLvFL73MPMpEUvwWtNU4gNMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQDQUoBD6tte9T+MNP8QSLjfiPQg
diOUnrqkps0Y8c8CmWAy+vayDa7ym3d+zWnCmfLbrxDy/0Fwrm0sE32VBH5f0QCG
UI/FA2E8Cn3aRhs0sFldX4zn5K+M0sQ2NVf4u2oPjoiaSyYoqTjZEBPASxRMT/G+
W4iiAzzY6ev3SH654VX06wzfwCnBjmHXZNWG+H6Ordz6i2dEBQNUDH0xIHMRD7r4
WT3VCK7jBYHTczbZwW10Vj7tUPtoc2GzNQFFcKaobcnrovkP4m3v20Agbvl39CjO
ZAFHiNgRfd+GRLo7IV4QUCOL/V/gBQRtfR3F6gSw+YNFyDD4gJYcQg733VGH
-----END CERTIFICATE-----
)KEY";
 
static const char privkey[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpAIBAAKCAQEAvGEmX7tm8gB0DvHXhuurtguifSm2mEpOvDuxlDyab3f02BXS
MqupIPMZRYc8yOXLeqvvU1qLrMmriNvZTZuEHefhbZlON62g6BJBM+4NNnDfjQk7
iNVub8tY1aAPljgS5LoXPSEpsU+mZq65D2TnZg9pN+vSMMcJM26weTk43vXAISxw
+6NUuXqzwKsSfH8xRF4Nh6k7qLA+3MDpp3oEBmsdJLGDiykuHWbqVYiGKamC+Cu5
jYlP9fZ3UcWEaPYhjFJFesIawIVRqio2GBiGyN5pisx34fnXaGAI+mRdTzk1qrjn
/DYySVNg0mgAJNLmCKbgKGLvbih2fUWAaCFMqQIDAQABAoIBAErM7Lbgq/z2Dx+M
Cj/JvrIXppq6gIWyI9d8gIPTGKOgZzmSWJfEL/Ekdml0TL+c95IrSWm4r3OZ1KIQ
YhX95ZUWaR3i3Psg156u+PMM2HRAl5PiEaDA1wxPG2QgHXBRrbbi6a1dSLfeX72w
LU2ejH+rKOWKnzi9H7srfal0/k8RaSodBnkLzXqDqmrb/sNntWJMHnjSS0GmaekL
J3tX21KnHSzGzXVhGHNPQ1BOuq9xvVXcsoVUWasvZnHpMBTend8eodTC6pH/GHm6
nxlktRisdyZudK662qzWLOplZSEnS0MUfdolnWdSTjVEw7XTz4agXqlnsGwXpOiW
v1Lhpp0CgYEA7JJKwDCBjNGuugFHP/qnqs9cvmJN+pWUFD3VK0BXkRJ0PDz95rOy
4dweV7PDDUZfza7w9wAqO2v2NWxee3Ksblp/EVqZjQBgAAb8kKKKWA2OBSzBIj56
VZu5HGxDeZiS/6wr1UIpsZZ81fQvivX2c3VqclHn5xxSaGwYxAcAJGsCgYEAy9mp
/rmeW3HGhDbkJ9LPL2VCn01UDWsyo7mjhZi2RRX1U28LpUzRRDa9lUhMoQhj/vj0
ooVvEOxng9LaR+RExiJilb+lShHb4zQzeMcAZn8X7UQvfG0IXJZe1m9al0BcDVeh
sXAbICeK6CuuT4T7nnSpixEtXhWwd05MWC3EuDsCgYEAxYDU+2MDpUchcpTCoT1o
YYhBS4jSxVO/jq6Ym0VaVflsJSZeaw63VyzoABxJyXlpXlShQ/VVTMqzgKJ6tuFj
57WRxDE5ZKhdfWhXz4CDs0ONv/A/RZGXnIUno/0W0Bt7Dgz1g1N7b5HNoun8Dy2N
lZL/TXXn/+B7REaK3o1hpwUCgYEAoH/waK6dEEK0msTdPr2sgxSnL+Yil64fYOl4
5mcmm55+WgLEmJGy8pJnEnKqYt/IW6iIdK26lQiNOC17z77ap2XLWTxbV8ZX6rvf
CukkV48Zt6ZH/R+bxcpfQVbLbOsvjxHALYSm1tpLdCFwTQvXURtpoiUUI0/QcR8k
3QisKqECgYAzydXBNy0F2/zzGWGW60sMYnhgbWnuRH9mzg901aKd/fkJQUGN0ATs
MC39GZcGP+aVgJykC3o9626SRATAgBCXhGnwWQ/fx29V6oEd+P79CJyzdMNU2h6Y
Qc4jCEHm0te1tlHV1I/JM+wvdZE+BBQJpOp4IpIQGmPdAKaubrJaFQ==
-----END RSA PRIVATE KEY-----
)KEY";