#include <WiFi.h>

const char* ssid = "iqoo";
const char* password = "12345678";

WiFiServer server(80);

int led = 23;

void setup()
{
  Serial.begin(115200);

  pinMode(led, OUTPUT);

  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  Serial.println(WiFi.localIP());

  server.begin();
}

void loop()
{
  WiFiClient client = server.available();

  if (client)
  {
    String request = client.readStringUntil('\r');

    if (request.indexOf("/ON") != -1)
    {
      digitalWrite(led, HIGH);
    }

    if (request.indexOf("/OFF") != -1)
    {
      digitalWrite(led, LOW);
    }

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");

    client.println("<h1>ESP32 Control</h1>");
    client.println("<a href=\"/ON\">LED ON</a><br>");
    client.println("<a href=\"/OFF\">LED OFF</a>");

    delay(1);
    client.stop();
  }
}
