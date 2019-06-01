#include <ESP8266WiFi.h>

//how many clients should be able to telnet to this ESP8266
#define MAX_SRV_CLIENTS 2
char* phoneNumber = "27874";

WiFiServer server(23);
WiFiClient serverClients[MAX_SRV_CLIENTS];

void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP("ussrphone", "12345678");
  //start UART and the server
  Serial.begin(115200);
  server.begin();
  server.setNoDelay(true);
}

void loop() {
  uint8_t i;
  //check if there are any new clients
  if (server.hasClient()) {
    for (i = 0; i < MAX_SRV_CLIENTS; i++) {
      //find free/disconnected spot
      if (!serverClients[i] || !serverClients[i].connected()) {
        if (serverClients[i]) serverClients[i].stop();
        serverClients[i] = server.available();
        continue;
      }
    }
    //no free/disconnected spot so reject
    WiFiClient serverClient = server.available();
    serverClient.stop();
  }
  //check clients for data
  for (i = 0; i < MAX_SRV_CLIENTS; i++) {
    if (serverClients[i] && serverClients[i].connected()) {
      if (serverClients[i].available())
      {
        char strWiFi[5];
        int k = 0;
        while (serverClients[i].available() > 0)
        {
          strWiFi[k] = serverClients[i].read();
          k++;
        }
        
          //Serial.println(strWiFi);
        if (strstr(strWiFi,"27874"))
        {
          Serial.print("1");
        }
      }
    }
  }

}
