#include "view.h"

// void View::MainPage()
// {
//       IPAddress ip = WiFi.softAPIP();
//       String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
//       content = "<!DOCTYPE HTML>\r\n<html>Hello from ESP8266 at ";
//       content += "<form action=\"/scan\" method=\"POST\"><input type=\"submit\" value=\"scan\"></form>";
//       content += ipStr;
//       content += "<p>";
//       content += st;
//       content += "</p><form method='get' action='setting'><label>SSID: </label><input name='ssid' length=32><input name='pass' length=64><input type='submit'></form>";
//       content += "</html>";
//       server.send(200, "text/html", content);
// }

void View::MainPage()
{
    IPAddress ip = WiFi.softAPIP();
    String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
    int n = WiFi.scanNetworks();

    st = "<ol>";
    for (int i = 0; i < n; ++i)
    {
        st += "<li>";
        st += WiFi.SSID(i);
        st += "</li>";
    }
    st += "</ol>";
    content = "<html><head><title>JetSpace</title>";
    content += "<meta http-equiv='Content-Type' content='text/html; charset=utf-8'>";
    content += "<style>";
    content += "body{display: flex; flex; justify-content: center; align-items: center; background-color: #888;}";
    content += ".modal{display: flex; flex-direction: column; gap: 20px; justify-content: center; align-items: center; width: 400px; height: auto; background-color: #fff;}";
    content += "</style></head>";
    content += "<body>";
    content += "<div class=\"modal\">";
    content += ipStr;
    content += "<p>";
    content += st;
    content += "</p>";
    content += "</div>";
    content += "</body></html>";
    server.send(200, "text/html", content);
}
