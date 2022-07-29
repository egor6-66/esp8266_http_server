#include "config.h"

int localSerwerPort = 80;
extern int statusCode = 0;
extern String content = "";
extern String st = "";
int i = 0;

ESP8266WebServer server(80);
