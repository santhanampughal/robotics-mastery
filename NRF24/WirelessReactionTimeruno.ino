#include <SPI.h>
#include <RF24.h>

RF24 radio(7,8);

const byte address[6] = "00001";

int signal;

unsigned long starttime;
unsigned long reactiontime;

bool waitingforpress = false;

void setup()
{
  Serial.begin(9600);

  pinMode(3, OUTPUT);

  pinMode(2, INPUT_PULLUP);

  radio.begin();

  radio.setChannel(108);

  radio.openReadingPipe(0,address);

  radio.startListening();

  Serial.println("RX READY");
}

void loop()
{
  if(radio.available())
  {
    radio.read(&signal,sizeof(signal));

    if(signal == 1)
    {
      digitalWrite(3,HIGH);

      starttime = millis();

      waitingforpress = true;

      Serial.println("GO!");
    }
  }

  if(waitingforpress)
  {
    if(digitalRead(2) == LOW)
    {
      reactiontime = millis() - starttime;

      digitalWrite(3,LOW);

      Serial.print("Reaction Time = ");
      Serial.print(reactiontime);
      Serial.println(" ms");

      waitingforpress = false;

      delay(300);
    }
  }
}