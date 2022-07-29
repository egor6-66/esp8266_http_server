#include "main.h"

void setup()
{
  Serial.begin(115200);
  WiFi.disconnect();

  EEPROM.begin(512);
  delay(10);

  String ssid = localServer.GetEpSsid();
  String pass = localServer.GetEpPass();

  WiFi.begin(ssid.c_str(), pass.c_str());

  localServer.Reconnect();
}

void loop()
{
  if ((WiFi.status() == WL_CONNECTED))
  {
    Serial.println("eeeee");
  }
  else
  {
    Serial.println("fuck");
  }
}
