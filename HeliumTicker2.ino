// Basic ESP8266 wifi functions
#include <ESP8266WiFi.h>
#define ESP_RESET ESP.reset()

// Logging
#include <ArduinoLog.h>

// ASync WiFi Manager
#include <ESPAsync_WiFiManager.h>               //https://github.com/khoih-prog/ESPAsync_WiFiManager

/*
   DRD Include and config Defines
*/
#define USE_LITTLEFS            true
#define ESP_DRD_USE_LITTLEFS    true
#define DRD_TIMEOUT             10
#define DRD_ADDRESS             0
#include <ESP_DoubleResetDetector.h>            //https://github.com/khoih-prog/ESP_DoubleResetDetector

/*
   End DRD config defines
*/

// DNS Server
#include <DNSServer.h>

// WS2812 Libraries
#include <NeoPixelAnimator.h>
#include <NeoPixelBus.h>

// Sensitive information (ssid, password)
#include "sensitive.h"

/*
    Definition of the LED Panel
*/
const uint8_t PanelWidth = 32;  // 32 pixel x 8 pixel matrix of leds
const uint8_t PanelHeight = 8;
const uint16_t PixelCount = PanelWidth * PanelHeight;

const uint16_t PanelLeft = 0;
const uint16_t PanelRight = PanelWidth - 1;
const uint16_t PanelTop = 0;
const uint16_t PanelBottom = PanelHeight - 1;

typedef RowMajorLayout MyPanelLayout;
NeoTopology<MyPanelLayout> topo(PanelWidth, PanelHeight);

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);
/*
    End definition of the LED Panel
*/

/*
   DRD and DNS define and config variables
*/
DoubleResetDetector*    drd;
AsyncWebServer          webServer(80);
DNSServer               dnsServer;

bool initialConfig =    false;

/*
   End DRD and DNS define
*/

void setup() {
  Serial.begin(115200);
  // Pass log level, whether to show log level, and print interface.
  // Available levels are:
  // LOG_LEVEL_SILENT, LOG_LEVEL_FATAL, LOG_LEVEL_ERROR, LOG_LEVEL_WARNING, LOG_LEVEL_INFO, LOG_LEVEL_TRACE, LOG_LEVEL_VERBOSE
  // Note: if you want to fully remove all logging code, uncomment #define DISABLE_LOGGING in Logging.h
  //       this will significantly reduce your project size

  Log.begin(LOG_LEVEL_VERBOSE, &Serial);
  while (!Serial); // wait for serial attach

  if (WiFi.SSID() == "") {
    Log.infoln(F("No AP credentials"));
    initialConfig = true;
  }
  drd = new DoubleResetDetector(DRD_TIMEOUT, DRD_ADDRESS);
  if (drd->detectDoubleReset()) {
    Log.infoln(F("DRD"));
    initialConfig = true;
  }
  if (initialConfig) {
    Log.println(F("Starting Config Portal")); 

    ESPAsync_WiFiManager ESPAsync_wifiManager(&webServer, &dnsServer, "ConfigOnDoubleReset");
    //ESPAsync_wifiManager.setConfigPortalChannel(0);
    ESPAsync_wifiManager.setConfigPortalTimeout(0);
    if (!ESPAsync_wifiManager.startConfigPortal()) {
      Log.infoln(F("Not connected to WiFi"));
    }
    else {
      Log.infoln(F("connected"));
    }
  }
  int connRes = WiFi.waitForConnectResult();

  if (WiFi.status() != WL_CONNECTED) {
    Log.infoln(F("Failed to connect"));
  }
  else {
    Log.infoln(F("Local IP: "));
    Log.infoln(WiFi.localIP());
  }


  Log.infoln();
  Log.infoln("Initializing strip.");

  strip.Begin();
  strip.ClearTo(black); // Clear strip
  strip.Show();
}

void loop() {
  drd->loop();
  // put your main code here, to run repeatedly:
  strip.SetPixelColor(topo.Map(left, top), white);
  strip.SetPixelColor(topo.Map(right, top), red);
  strip.SetPixelColor(topo.Map(right, bottom), green);
  strip.SetPixelColor(topo.Map(left, bottom), blue);
  strip.Show();

}
