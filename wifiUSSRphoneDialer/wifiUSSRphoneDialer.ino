#include <ESP8266WiFi.h>
#include <EEPROM.h>
// Expose Espressif SDK functionality - wrapped in ifdef so that it still
// compiles on other platforms
#ifdef ESP8266
extern "C" {
#include "user_interface.h"
}
#endif

IPAddress serverTelnet(192, 168, 4, 1);
int port = 23;
WiFiClient client;

char* number = "";

void setup() {
  Serial.flush();
  Serial.begin(115200);
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.begin("ussrphone", "12345678");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("no wifi");
    delay(800);
  }
  if (client.connect(serverTelnet, port)) {
    Serial.println("connected to server");
    delay(50);
  }
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection to server failed");
  }
}

void loop() {

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("no wifi");
    delay(800);
  }
  if (client.connect(serverTelnet, port)) {
    delay(50);
  }
  if (Serial.available())
  {
    char strUART[5];
    int i = 0;
    while (Serial.available() > 0)
    {
      strUART[i] = Serial.read();
      i++;
    }
    Serial.println(strUART);
    if (client.connected())
    {
      client.print(strUART);
    }
  }
}











