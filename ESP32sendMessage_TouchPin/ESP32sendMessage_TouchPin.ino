/*---------------------------------------------------------------------------------------------

  Open Sound Control (OSC) library for the ESP8266/ESP32

  Example for sending messages from the ESP8266/ESP32 to a remote computer
  The example is sending "hello, osc." to the address "/test".

  This example code is in the public domain.

--------------------------------------------------------------------------------------------- */
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
#include <WiFiUdp.h>
#include <OSCMessage.h>

#define touchPin T8

char ssid[] = "TP-Link_9118";     // your network SSID (name)
char pass[] = "nihaonordhavn93";  // your network password

WiFiUDP Udp;                              // A UDP instance to let us send and receive packets over UDP
const IPAddress outIp(192, 168, 0, 103);  // remote IP of your computer
const unsigned int outPort = 5000;        // remote port to receive OSC
const unsigned int localPort = 8888;      // local port to listen for OSC packets (actually not used for sending)

float newMappedVal = 0;

void setup() {
  Serial.begin(115200);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
#ifdef ESP32
  Serial.println(localPort);
#else
  Serial.println(Udp.localPort());
#endif
}

void loop() {

  readTouch();

  OSCMessage msg("/Amplitude");
  msg.add(newMappedVal);
  Udp.beginPacket(outIp, outPort);
  msg.send(Udp);
  Udp.endPacket();
  msg.empty();
  delay(100);
}

void readTouch() {

float tVal = touchRead(touchPin);
int mappedVal = map(tVal, 110, 10, 1, 40);
newMappedVal = float(mappedVal)*.1;

  Serial.println(touchRead(touchPin)); // get value using T0
  Serial.println(newMappedVal);  

}