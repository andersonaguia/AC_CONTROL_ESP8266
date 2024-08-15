#include "webserver.h"

// Mapeamento das temperaturas para seus respectivos códigos LSB
std::unordered_map<int, uint8_t> tempToCode = {
  { 17, 0x00 },
  { 18, 0x10 },
  { 19, 0x30 },
  { 20, 0x20 },
  { 21, 0x60 },
  { 22, 0x70 },
  { 23, 0x50 },
  { 24, 0x40 },
  { 25, 0xC0 },
  { 26, 0xD0 },
  { 27, 0x90 },
  { 28, 0x80 },
  { 29, 0xA0 },
  { 30, 0xB0 }
};

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

WebServer::WebServer(const int port, const uint64_t acCommandOn, const uint64_t acCommandOff)
  : server(port), powerOn(acCommandOn), powerOff(acCommandOff) {
  irsend.begin();
}

void WebServer::begin() {
  server.on("/", HTTP_GET, std::bind(&WebServer::handleRoot, this));
  server.on("/on", HTTP_GET, std::bind(&WebServer::handleOn, this));
  server.on("/off", HTTP_GET, std::bind(&WebServer::handleOff, this));
  server.on("/status", HTTP_GET, std::bind(&WebServer::handleStatus, this));
  server.on("/temperature", HTTP_GET, std::bind(&WebServer::handleTemperature, this));
  server.onNotFound(std::bind(&WebServer::handleRoot, this));
  server.begin();
}

void WebServer::handleClient() {
  server.handleClient();
}

void WebServer::handleRoot() {
  server.send(200, "text/html", index_html);
}

void WebServer::handleStatus() {
  double currentRms = currentSensor.getCurrentRms();
 
  String jsonResponse = "{\"status\": ";

  if (currentRms > 1) {
    jsonResponse += "true";
    Serial.println("Estado da máquina: ON");
  } else {
    jsonResponse += "false";
     Serial.println("Estado da máquina: OFF");
  }

  jsonResponse += "}";

  server.send(200, "application/json", jsonResponse);
}

void WebServer::handleOn() {
  Serial.printf("\nLIGANDO AR CONDICIONADO...");
  irsend.sendCOOLIX(powerOn);
  server.send(200, "text/html", index_html);
}

void WebServer::handleOff() {
  Serial.printf("\nDESLIGANDO AR CONDICIONADO...");
  irsend.sendCOOLIX(powerOff);
  server.send(200, "text/html", index_html);
}

void WebServer::handleTemperature() {
  if (server.hasArg("temp")) {
    int temperature = server.arg("temp").toInt();

    String response = "Temperatura recebida: " + String(temperature) + "°C";
    uint64_t command = generateCoolixCommand(temperature);
    irsend.sendCOOLIX(command);
    Serial.printf("\nLigando máquina com temperatura em %d °C.", temperature);
    server.send(200, "text/html", response);
  } else {
    server.send(400, "text/html", "Parâmetro de temperatura ausente");
  }
}

uint64_t WebServer::generateCoolixCommand(int temperature) {
  uint64_t baseCode = 0xB2BF00;

  if (tempToCode.find(temperature) != tempToCode.end()) {
    return baseCode | tempToCode[temperature];
  } else {
    Serial.println("Temperatura fora do intervalo suportado!");
    return 0;
  }
}
