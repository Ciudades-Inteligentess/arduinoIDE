# Función `main`

Este programa implementa la funcionalidad principal de un dispositivo IoT basado en el ESP8266, que utiliza un sensor ultrasónico para medir distancias y envía los datos a AWS IoT Core a través de MQTT.

## Descripción General

1. **Configuración de Librerías y Variables**  
   Se importan varias librerías de Arduino para manejar la conexión WiFi, procesar JSON, obtener la hora y gestionar conexiones seguras, además de un cliente MQTT para comunicarse con AWS IoT.  
   También se configuran credenciales de WiFi, datos de autenticación para AWS y se definen los temas de publicación y suscripción para MQTT.

2. **Funciones Principales**  
   - **`NTPConnect()`**: Conecta a un servidor NTP para sincronizar la hora del dispositivo.
   - **`connectAWS()`**: Establece una conexión segura con AWS IoT Core usando certificados SSL.
   - **`publishMessage()`**: Publica un mensaje JSON en el tema de MQTT de AWS si la conexión está activa.

3. **Ciclo de Ejecución `setup()` y `loop()`**  
   - **`setup()`**: Inicializa la comunicación serial y llama a `connectAWS()` para establecer la conexión inicial a AWS.
   - **`loop()`**:  
      En cada iteración, verifica y mantiene la conexión con AWS IoT. Luego:
      - Lee la distancia en centímetros desde el sensor ultrasónico.
      - Crea un mensaje JSON con los datos de la distancia, el ID del dispositivo y la fecha y hora actuales.
      - Publica el mensaje en el tema MQTT cada 5 segundos si la conexión está activa.

## Ejemplo de Datos JSON Enviados

Cada mensaje JSON enviado tiene la siguiente estructura:
```json
{
  "distance_cm": <valor de la distancia en cm>,
  "trafficligh_id": "1",
  "timestamp": "<fecha y hora actuales>"
}
