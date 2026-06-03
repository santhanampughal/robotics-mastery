int t = 10;
int e = 11;

int distance;
long duration;

void setup(){
  pinMode(t,OUTPUT);
  pinMode(e,INPUT);
  Serial.begin(9600);
}
void loop(){
    digitalWrite(t,LOW);
    delayMicroseconds(2);

    digitalWrite(t,HIGH);
    delayMicroseconds(10);

    digitalWrite(t,LOW);

    duration = pulseIn(e,HIGH);
    distance = duration *0.034 / 2;
    
    Serial.print("distance: ");
    Serial.println(distance);
    delay(500);
}
