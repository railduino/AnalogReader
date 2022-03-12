/*
 * Test program for a minimal input (e.g. potentiometer)
 */

#include <AnalogReader.h>

// Instantiate the reader
AnalogReader pot(A0, false);

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  delay(1000);

  // Nothing more to do here
}

// the loop function runs over and over again forever
void loop() {
  int value;

  if (pot.readValue(&value)) {
    Serial.print("Value: ");
    Serial.println(value);
  }

  delay(50);
}
