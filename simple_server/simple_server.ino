//
// A simple server implementation showing how to:
//  * serve static messages
//  * read GET and POST parameters
//  * handle missing pages / 404s
//

#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

const char* ssid     = "Eprotocol"; // Change this to your WiFi SSID
const char* password = "53734312";  // Change this to your WiFi password

const IPAddress staticIP(192, 168, 50, 123);  // Set your desired static IP address
const IPAddress gateway(192, 168, 50, 1); //cmd ipconfid: Default Gateway
const IPAddress subnet(255, 255, 255, 0);

const char* PARAM_MESSAGE = "message";

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void setup() {

    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    while (!Serial) { delay(100); }

    Serial.println();
    Serial.println("******************************************************");
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    // Set static IP configuration
    if (!WiFi.config(staticIP, gateway, subnet)) {
      Serial.println("Failed to configure static IP");
    }
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("gatewayIP address: ");
    Serial.println(WiFi.gatewayIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "Hello, world");
    });

    // Send a GET request to <IP>/get?message=<message>
    server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
        String message;
        if (request->hasParam(PARAM_MESSAGE)) {
            message = request->getParam(PARAM_MESSAGE)->value();
        } else {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, GET: " + message);
        pinMode(21,OUTPUT);
        if(message=="ON"){
          Serial.println("GPIO ON");
          digitalWrite(21, HIGH);
        }else if(message=="OFF"){
          Serial.println("GPIO OFF");
          digitalWrite(21, LOW);
        }
    });

    // Send a POST request to <IP>/post with a form field message set to <message>
    server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request){
        String message;
        if (request->hasParam(PARAM_MESSAGE, true)) {
            message = request->getParam(PARAM_MESSAGE, true)->value();
        } else {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, POST: " + message);
    });

    server.onNotFound(notFound);

    server.begin();
}

void loop() {
}
