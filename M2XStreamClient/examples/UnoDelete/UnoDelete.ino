#include <jsonlite.h>
#include <SPI.h>
#include <WiFi.h>

#include "M2XStreamClient.h"

char ssid[] = "<ssid>"; //  your network SSID (name)
char pass[] = "<WPA password>";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

char feedId[] = "<feed id>"; // Feed you want to post to
char streamName[] = "<stream name>"; // Stream you want to post to
char m2xKey[] = "<M2X access key>"; // Your M2X access key

char fromTime[] = "<from date/time>"; // yyyy-mm-ddTHH:MM:SS.SSSZ
char endTime[] = "<end date/time>"; // yyyy-mm-ddTHH:MM:SS.SSSZ

WiFiClient client;
M2XStreamClient m2xClient(&client, m2xKey);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while(true);
  }

  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
  printWifiStatus();
  
  // Delete values
  int response = m2xClient.deleteValues(feedId, 
                                        streamName,
                                        fromTime,
                                        endTime);
  Serial.print("M2x client response code: ");
  Serial.println(response);   
}

void loop() {
  // Do nothing
  delay(5000);
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}