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


## Pasos para Ejecutar el Proyecto desde PlatformIO

Sigue los pasos a continuación para configurar y ejecutar el proyecto en PlatformIO, utilizando un ESP8266:

### Requisitos Previos

1. **Instalar PlatformIO**:
   - Si no tienes PlatformIO instalado, puedes hacerlo mediante [Visual Studio Code](https://code.visualstudio.com/) siguiendo estos pasos:
     - Descarga e instala Visual Studio Code.
     - Abre Visual Studio Code y ve a la pestaña de **Extensiones** (icono de cuadrado en la barra lateral izquierda).
     - Busca **PlatformIO IDE** e instálalo.

2. **Instalar las Librerías Necesarias**:
   - El proyecto usa varias librerías de Arduino, incluidas `PubSubClient`, `ArduinoJson`, y `ESP8266WiFi`, entre otras. PlatformIO generalmente las gestionará automáticamente si las defines en el archivo `platformio.ini`, pero asegúrate de tenerlas disponibles.
   
3. **Certificados y Claves de AWS IoT**:
   - Asegúrate de haber descargado y configurado correctamente los certificados de AWS IoT (certificados de cliente y clave privada). Estos deben estar en los archivos de tu proyecto como `cacert`, `client_cert`, y `privkey`, o puedes ajustarlos según tu configuración.

### Pasos para Correr el Proyecto

1. **Clonar o Descargar el Proyecto**:
   - Si aún no tienes el proyecto en tu máquina local, clónalo usando Git o descárgalo como un archivo ZIP desde tu repositorio de GitHub.
     ```bash
     git clone https://github.com/Ciudades-Inteligentess/arduinoIDE
     ```
     O simplemente descarga el ZIP desde GitHub y extráelo en tu máquina.

2. **Abrir el Proyecto en PlatformIO**:
   - Abre Visual Studio Code con PlatformIO instalado.
   - Desde el menú de PlatformIO, selecciona **Open Project** y navega hasta la carpeta del proyecto que acabas de clonar o descargar.

3. **Configurar `platformio.ini`**:
   - Asegúrate de que tu archivo `platformio.ini` esté configurado correctamente con los parámetros del ESP8266. A continuación, un ejemplo básico de configuración:
     ```ini
     [env:esp8266]
     platform = espressif8266
     board = esp01_1m
     framework = arduino
     monitor_speed = 115200
     upload_speed = 115200
     lib_deps = 
        PubSubClient
        ArduinoJson
     ```

4. **Subir el Código al ESP8266**:
   - Conecta tu ESP8266 al puerto USB de tu computadora.
   - En PlatformIO, haz clic en el ícono de **Subir** (ícono de la flecha hacia arriba) para compilar y cargar el código en el ESP8266.
   - Asegúrate de seleccionar el puerto correcto si PlatformIO no lo detecta automáticamente.

5. **Monitorear la Salida Serial**:
   - Después de que el código se cargue correctamente en el ESP8266, abre el **Monitor Serial** desde PlatformIO haciendo clic en el ícono del monitor (un rectángulo con una onda de señal) en la barra de tareas de PlatformIO.
   - Deberías ver el proceso de conexión a la red Wi-Fi, la sincronización con el servidor NTP y la conexión a AWS IoT. Si todo está configurado correctamente, el dispositivo comenzará a enviar datos del sensor ultrasónico.

### Solución de Problemas

- **Conexión Wi-Fi**: Si el ESP8266 no se conecta a la red Wi-Fi, verifica las credenciales de la red (`WIFI_SSID` y `WIFI_PASSWORD`) en el código.
- **Certificados de AWS IoT**: Si el ESP8266 no puede conectarse a AWS IoT, asegúrate de que los certificados estén correctamente configurados y accesibles en el proyecto.

¡Listo! Ahora deberías estar recibiendo datos de distancia del sensor ultrasónico en AWS IoT Core.