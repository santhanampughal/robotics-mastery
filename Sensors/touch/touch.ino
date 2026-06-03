int l = 12;
int f = 9;

void setup(){
  pinMode(l,OUTPUT);
  pinMode(f,INPUT);
  Serial.begin(9600);
}

void loop(){
  int fin = digitalRead(f);

  if (fin == LOW)
  {
    Serial.println("TOUCH DETECTED");
    digitalWrite(l,LOW);
  }
  else{
    Serial.println("not detected");
    digitalWrite(l,HIGH);
  }
  delay(100);
}
