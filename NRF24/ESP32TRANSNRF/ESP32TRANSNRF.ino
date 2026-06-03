#include <SPI.h>
#include <RF24.h>

RF24 radio(4, 5);

const byte address[6] = "00001";

#define TRIG 26
#define ECHO 27
#define TOUCH_PIN 32
#define LDR_PIN 35

struct Data
{
  int32_t distance;
  int32_t light;
  int32_t touch;
};

Data d;

void setup()
{
  Serial.begin(115200);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(TOUCH_PIN, INPUT);

  radio.begin();
  radio.setChannel(108);
  radio.openWritingPipe(address);
  radio.stopListening();

  Serial.println("TX READY");
}

void loop()
{
  // Ultrasonic
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 50000);

  Serial.print("Duration = ");
  Serial.println(duration);

  d.distance = duration;
  if (duration == 0)
  {
    d.distance = -1;
  }
  else
  {
    d.distance = (duration * 343) / 20000;
  }

  // LDR
  d.light = analogRead(LDR_PIN);

  // Touch
  d.touch = digitalRead(TOUCH_PIN);

  Serial.print("Distance: ");
  Serial.println(d.distance);

  Serial.print("Light: ");
  Serial.println(d.light);

  Serial.print("Touch: ");
  Serial.println(d.touch);

  Serial.println("----------------");

  radio.write(&d, sizeof(d));

  delay(500);
}