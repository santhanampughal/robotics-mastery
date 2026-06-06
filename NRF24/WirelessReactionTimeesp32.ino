#include <SPI.h>
#include <RF24.h>

RF24 radio(4,5);

const byte address[6] = "00001";

int startSignal = 1;

void setup()
{
  Serial.begin(115200);

  radio.begin();

  radio.setChannel(108);

  radio.openWritingPipe(address);

  radio.stopListening();

  Serial.println("TX READY");
}

void loop()
{
  delay(5000);

  radio.write(&startSignal,sizeof(startSignal));

  Serial.println("START SENT");
}