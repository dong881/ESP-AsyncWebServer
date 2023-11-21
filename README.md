# README

This is a simple server implementation for controlling GPIO and serving static messages on an ESP32 or ESP8266 device. The server utilizes the [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer) library for asynchronous handling of web requests and [AsyncTCP](https://github.com/me-no-dev/AsyncTCP) for asynchronous TCP communication. Additionally, the [WiFi](https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFi) library is used for WiFi connectivity.

## Prerequisites
Before using this code, make sure to install the following libraries:
- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- [AsyncTCP](https://github.com/me-no-dev/AsyncTCP)
- [WiFi](https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFi)

## Functionality
1. **GPIO Control**: The server allows you to control a GPIO pin by sending a GET request to `/get?message=<message>`. The message can be "ON" or "OFF" to toggle the GPIO pin.

2. **Static Messages**: Accessing the root endpoint ("/") via a GET request returns a static message: "Hello, world".

3. **POST Request Handling**: Sending a POST request to `/post` with a form field message set to a specific value will result in a response with the message.

## Configuration
Before uploading the code to your ESP32/ESP8266 device, make the following modifications in the code:
- Set your WiFi SSID and password:
    ```cpp
    const char* ssid = "YourWiFiSSID";
    const char* password = "YourWiFiPassword";
    ```

- Set your desired static IP address, gateway, and subnet:
    ```cpp
    const IPAddress staticIP(192, 168, 50, 123);
    const IPAddress gateway(192, 168, 50, 1);
    const IPAddress subnet(255, 255, 255, 0);
    ```

## Note
Ensure that you have the necessary permissions to control GPIO pins on your device. Additionally, the default gateway IP address (`gateway`) should be set based on your local network configuration. You can use the `ipconfig` command in the command prompt to find the Default Gateway, typically in the format `192.168.1.1`.
