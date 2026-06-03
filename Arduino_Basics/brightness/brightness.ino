int led1 = 9;
int brightness = 0;
int fadeAmount = 5;

void setup()
{
  pinMode(led1,OUTPUT);
}

void loop(){
  analogWrite(led1,brightness);
  brightness = brightness + fadeAmount;

  if(brightness <= 0 || brightness >= 255)
  {
    fadeAmount = -fadeAmount;
  }
  delay(30);
}
