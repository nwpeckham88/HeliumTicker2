// Basic ESP8266 wifi functions
#include <ESP8266WiFi.h>
#define ESP_RESET ESP.reset()
// DNS Server
#include <DNSServer.h>

// WS2812 Libraries
#include <NeoPixelAnimator.h>
#include <NeoPixelBus.h>

/*
   Automaton State Machine library
*/
#include <Automaton.h>
#include <Atm_esp8266.h>

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
   State machines
*/
Atm_esp8266_httpc_simple heliumClient, binanceClient;

/*
   End state machines definition
*/

/*
   API Defines
*/
#define HELIUM_ACCOUNT 1
#define HELIUM_HOTSPOT 2
#define HELIUM_REWARDS 4
#define HELIUM_

/*
   End API Defines
*/

void setup() {
  Serial.begin(115200);
  while (!Serial); // wait for serial attach

  Serial.println();
  Serial.println("Initializing strip.");

  strip.Begin();
  strip.ClearTo(black); // Clear strip
  strip.Show();

  Serial.println();
  Serial.println("Running...");


  heliumClient.begin( "https://api.helium.io/v1/" )
  .onStart( []( int idx, int v, int ) {
    switch ( v ) {
      case 0:
        client.get( "/on" );
        return;
      case 1:
        client.get( "/off" );
        return;
    }
  });
}

void loop() {
  // put your main code here, to run repeatedly:
  strip.SetPixelColor(topo.Map(left, top), white);
  strip.SetPixelColor(topo.Map(right, top), red);
  strip.SetPixelColor(topo.Map(right, bottom), green);
  strip.SetPixelColor(topo.Map(left, bottom), blue);
  strip.Show();

}
