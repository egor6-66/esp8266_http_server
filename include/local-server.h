#pragma once

#include "config.h"


class LocalServer
{
private:


public:
    String GetEpSsid();
    String GetEpPass();
    bool TestWifi();
    void LaunchWeb();
    void CreateWebServer();
    void SetupAP(void);
    void Reconnect();
};
