#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

extern int localSerwerPort;
extern int statusCode;
extern String content;
extern String st;
extern int i;

extern const char *ssid;
extern const char *passphrase;

extern ESP8266WebServer server;
