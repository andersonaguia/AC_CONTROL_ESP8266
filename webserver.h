#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <ESP8266WebServer.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "index_html.h"
#include <unordered_map>
#include "current_sensor.h"

class WebServer
{
public:
    WebServer(const int port, const uint64_t acCommandOn, const uint64_t acCommandOff);
    void begin();
    void handleClient();

private:
    ESP8266WebServer server;
    CurrentSensor currentSensor;

    void handleRoot();
    void handleOn();
    void handleOff();
    void handleStatus();
    uint64_t powerOn;
    uint64_t powerOff;
    uint64_t generateCoolixCommand(int temperature);
    void handleTemperature();
};

#endif
