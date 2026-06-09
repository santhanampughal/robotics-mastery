#include<WiFi.h>
#include<WiFiServer.h>      // ✅ Was Webserver.h
#include<SPI.h>
#include<RF24.h>

#define TOUCH 34
#define LIGHT 35           // ❌ Was LIGHt 32
#define ECHO 27            // ❌ Was 32 (same as LIGHT)
#define TRIG 26            // ❌ Was 35 (35 is input only)

WiFiServer server(80);      // ❌ Was WiFiServer

const byte address[6] = "00001";

struct data
{
  int32_t distance;
  int32_t light;
  int32_t touch;
};

data d;

String systemState = "safe";
int command = 0;

RF24 radio(4,5);

const char *ssid = "iqoo";
const char *password = "12345678";

void setup()
{
  Serial.begin(115200);    // ❌ Must come before Serial.println()

  WiFi.begin(ssid,password);

  while(WiFi.status() != WL_CONNECTED)
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

  pinMode(ECHO,INPUT);
  pinMode(TRIG,OUTPUT);

  pinMode(TOUCH,INPUT);    // ❌ Was TOUCH_PIN
  pinMode(LIGHT,INPUT);    // ❌ Was LIGHT not defined

  Serial.println("TX READY");
}

void loop()
{
  d.touch = digitalRead(TOUCH);

  d.light = analogRead(LIGHT);      // ❌ Missing ;

  digitalWrite(TRIG,LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG,HIGH);          // ❌ Missing ;

  delayMicroseconds(10);

  digitalWrite(TRIG,LOW);

  long duration = pulseIn(ECHO,HIGH,50000);

  if(duration == 0)
  {
    d.distance = -1;
  }
  else
  {
    d.distance = duration * 0.034 / 2;
  }

  Serial.println("Duration:");
  Serial.println(duration);

  Serial.println("Distance:");      // ❌ Missing ;
  Serial.println(d.distance);

  Serial.println("Light:");
  Serial.println(d.light);          // ❌ Missing ;

  Serial.println("Touch:");
  Serial.println(d.touch);

  Serial.println("__________________");   // ❌ Was printl

  if(systemState != "safe")         // ❌ Was systemstate
  {
    command = 0;
  }
  else
  {
    command = 1;
  }

  radio.write(&command,sizeof(command));

  delay(500);
}