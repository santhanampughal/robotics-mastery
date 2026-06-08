#include<SPI.h>
#include<RF24.h>

RF24 radio(7,8);
const byte address[6] = "00001";
int command;


void setup()
{
  Serial.begin(9600);
  pinMode(3,OUTPUT);
  radio.begin();
  radio.setChannel(108);
  radio.openReadingPipe(0,address);
  radio.startListening();
}
void loop()
{
  if(radio.available())
  {
    radio.read(&command, sizeof(command));
    if(command ==1)
    {
      digitalWrite(3,HIGH);
      Serial.println("relay on");
    }
    if(command ==0)
    {
      digitalWrite(3,LOW);
      Serial.println("relay off");
    }
  }
}