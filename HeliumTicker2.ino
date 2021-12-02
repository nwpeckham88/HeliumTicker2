// Basic ESP8266 wifi functions
#include <ESP8266WiFi.h>
#define ESP_RESET ESP.reset()
// DNS Server
#include <DNSServer.h>

//Async WebServer
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

//Async WebClient
#include <AsyncHTTPRequest_Generic.h>           // https://github.com/khoih-prog/AsyncHTTPRequest_Generic

// Event scheduling
#include <Ticker.h>

// WS2812 Libraries
#include <NeoPixelAnimator.h>
#include <NeoPixelBus.h>

typedef RowMajorLayout MyPanelLayout;

const uint8_t PanelWidth = 32;  // 32 pixel x 8 pixel matrix of leds
const uint8_t PanelHeight = 8;
const uint16_t PixelCount = PanelWidth * PanelHeight;

NeoTopology<MyPanelLayout> topo(PanelWidth, PanelHeight);

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

void setup() {
  Serial.begin(115200);
  while (!Serial); // wait for serial attach

  Serial.println();
  Serial.println("Initializing strip.");

  strip.Begin();
  strip.Show();

  Serial.println();
  Serial.println("Running...");

}

void loop() {
  // put your main code here, to run repeatedly:

}
