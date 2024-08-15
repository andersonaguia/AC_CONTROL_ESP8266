#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include "webserver.h"

const uint16_t WEBSERVER_PORT = 8080;      // Web Server port
const uint64_t AC_COMMAND_ON = 0xB2BF40;   // Turn on A/C command
const uint64_t AC_COMMAND_OFF = 0xB27BE0;  // Turn off A/C command

ESP8266WiFiMulti WiFiMulti;

WebServer webServer(WEBSERVER_PORT, AC_COMMAND_ON, AC_COMMAND_OFF);

const char *ssid = "Fibratell_Sala_2.4G";     // Wireless network ssid
const char *password = "044gomes";  // Wireless password

void setup() {
#if ESP8266
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
#else   // ESP8266
  Serial.begin(115200, SERIAL_8N1);
#endif  // ESP8266

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  Serial.printf("[SETUP] Starting...");

  Serial.printf("\n[SETUP] Connecting to the network %s", ssid);

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.printf(".");
  }

  String ipString = WiFi.localIP().toString();
  Serial.printf("\n[INFO] Connected! IP Address: %s\n", ipString.c_str());

  Serial.printf("\n[SETUP] Starting Web Server...");

  webServer.begin();

  Serial.printf("\n[INFO] WebServer Address: %s:%d\n", ipString.c_str(), WEBSERVER_PORT);
}

void loop() {
  webServer.handleClient();
}
