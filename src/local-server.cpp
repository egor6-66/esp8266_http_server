#include <config.h>
#include "local-server.h"

String LocalServer::GetEpSsid()
{
  String ssid;
  for (int i = 0; i < 32; ++i)
  {
    ssid += char(EEPROM.read(i));
  }
  return ssid;
}

String LocalServer::GetEpPass()
{
  String pass;
  for (int i = 32; i < 96; ++i)
  {
    pass += char(EEPROM.read(i));
  }
  return pass;
}

bool LocalServer::TestWifi(void)
{
  int c = 0;
  while (c < 20)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("connect");
      return true;
    }
    delay(500);
    Serial.print("*");
    c++;
  }
  Serial.println("");
  Serial.println("Connect timed out, opening AP");
  return false;
}

void LocalServer::LaunchWeb()
{
  Serial.println("");
  if (WiFi.status() == WL_CONNECTED)
  {
    this->CreateWebServer();
    Serial.println("Server started");
  }
}

void LocalServer::SetupAP(void)
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  st = "<ol>";
  for (int i = 0; i < n; ++i)
  {
    st += "<li>";
    st += WiFi.SSID(i);
    st += " (";
    st += WiFi.RSSI(i);
    st += ")";
    st += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*";
    st += "</li>";
  }
  st += "</ol>";
  delay(100);
  WiFi.softAP("The_IoT_Projects", "123456789");
  this->LaunchWeb();
}

void LocalServer::CreateWebServer()
{
  {
    server.on("/", []()
              {
      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      content = "<!DOCTYPE HTML>\r\n<html>Hello from ESP8266 at ";
      content += "<form action=\"/scan\" method=\"POST\"><input type=\"submit\" value=\"scan\"></form>";
      content += ipStr;
      content += "<p>";
      content += st;
      content += "</p><form method='get' action='setting'><label>SSID: </label><input name='ssid' length=32><input name='pass' length=64><input type='submit'></form>";
      content += "</html>";
      server.send(200, "text/html", content); });
    server.on("/scan", []()
              {
      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      content = "<!DOCTYPE HTML>\r\n<html>go back";
      server.send(200, "text/html", content); });
    server.on("/setting", []()
              {
                String qsid = server.arg("ssid");
                String qpass = server.arg("pass");
                if (qsid.length() > 0 && qpass.length() > 0)
                {
                  for (int i = 0; i < 96; ++i)
                  {
                    EEPROM.write(i, 0);
                  }
                  for (int i = 0; i < qsid.length(); ++i)
                  {
                    EEPROM.write(i, qsid[i]);
                  }
                  Serial.println("writing eeprom pass:");
                  for (int i = 0; i < qpass.length(); ++i)
                  {
                    EEPROM.write(32 + i, qpass[i]);
                  }
                  EEPROM.commit();
                  content = "{\"Success\":\"saved to eeprom... reset to boot into new wifi\"}";
                  statusCode = 200;
                  ESP.reset();
                }
                else
                {
                  content = "{\"Error\":\"404 not found\"}";
                  statusCode = 404;
                  Serial.println("Sending 404");
                }
                server.sendHeader("Access-Control-Allow-Origin", "*");
                server.send(statusCode, "application/json", content); });
  }
}

void LocalServer::Reconnect()
{
  if (!this->TestWifi())
  {
    this->LaunchWeb();
    this->SetupAP();
  }

  while ((WiFi.status() != WL_CONNECTED))
  {
    delay(100);
    server.handleClient();
  }
}
