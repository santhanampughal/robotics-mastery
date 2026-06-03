int potPin = A0;
int led1 = 13;

int value = 0;
void setup(){
  pinMode(potPin, OUTPUT);
}

void loop()
{
  value = analogRead(potPin);
  int brightness = value/ 4;
  analogWrite(led1, brightness);
  delay(10);
}
