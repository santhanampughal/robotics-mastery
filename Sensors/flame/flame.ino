int g = 8;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(digitalRead(g));
  delay(500);
}
