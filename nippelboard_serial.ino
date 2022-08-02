#include <SPI.h>
#include "RF24.h"
#include "printf.h"
#include "Bounce2.h"

const uint8_t BUTTON_PINS[] = {2, 3, 4, 5, 6, 7, 8};

RF24 radio(9,10);
Bounce2::Button buttons[7];

const byte address[13] = "NippelBoard1";

struct ButtonState {
  uint8_t pressed;
  uint8_t volume;
} buttonState;

void setup() {
  Serial.begin(115200);
  radio.begin(); // Start up the radio
  printf_begin();
  radio.setAutoAck(1); // Ensure autoACK is enabled
  radio.setRetries(15,15); // Max delay between retries & number of retries
  radio.openReadingPipe(1, address); // Write to device address '2Node'
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
  radio.printDetails();

}

void loop() {
  if(radio.available()){
    radio.read(&buttonState, sizeof(struct ButtonState));
    char buffer[32];
    sprintf(buffer, "%d;%d", buttonState.pressed, buttonState.volume);
    Serial.println(buffer);
  }
}
