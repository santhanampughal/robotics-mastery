#include <SPI.h>
#include <RF24.h>

RF24 radio(7, 8);

const byte address[6] = "00001";

void setup() {

  Serial.begin(9600);

  if (!radio.begin()) {
    Serial.println("NRF FAIL");
    while (1);
  }

  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(108);

  radio.openReadingPipe(0, address);

  radio.startListening();

  Serial.println("RX READY");
}

void loop() {

  if (radio.available()) {

    char text[32] = "";

    radio.read(&text, sizeof(text));

    Serial.print("Received: ");
    Serial.println(text);
  }
}