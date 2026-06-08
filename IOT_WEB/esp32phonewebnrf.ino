#include<WiFi.h>
#include<WebServer.h>
#include<RF24.h>
#include<SPI.h>

RF24 radio(4,5);
const byte address[6] = "00001";

const char * ssid = "iqoo";
const char* password = "12345678";

WebServer server(80);

int command = 0;

void relayon()
{
  command = 1;
  radio.write(&command, sizeof(command));
  server.send(200, "text/html","<h1>relay on</h1><a href='/off'>OFF</a>");
}
void relayoff()
{
  command = 0;
  radio.write(&command,sizeof(command));
  server.send(200, "text/html","<h1>relay off</h1><a href='/on'>ON</a>");
}

void home()
{
  server.send(
    200,
    "text/html",
    "<h1>ESP32 Control</h1>"
    "<a href='/on'>RELAY ON</a><br><br>"
    "<a href='/off'>RELAY OFF</a>"
  );
}
void setup()
{
  server.on("/", home);
  Serial.begin(115200);
  WiFi.begin(ssid,password);
  while(WiFi.status()!= WL_CONNECTED)
  {
    delay(500);
    Serial.println(".");
  }
  Serial.println();
  Serial.println(WiFi.localIP());
  radio.begin();
  radio.setChannel(108);
  radio.openWritingPipe(address);
  radio.stopListening();
  server.on("/on",relayon);
  server.on("/off",relayoff);
  server.begin();
}
void loop()
{
  server.handleClient();
}