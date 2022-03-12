/*
 * Test program for a dual axis joystick
 */

#include <AnalogReader.h>

// The (horizontal) X axis ranges from 0 to 1023 and starts in the middle
AnalogReader joyX(A0, true);

// The (vertical) Y axis is additonally mapped to a single byte value
AnalogReader joyY(A1, true, 0, 255);

// Output buffer for debugging
char buffer[32];

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  delay(1000);

  joyX.readValue(NULL);
  joyY.readValue(NULL);

  sprintf(buffer, "midX=%d midY=%d", joyX.getMiddle(), joyY.getMiddle());
  Serial.println(buffer);
}

// the loop function runs over and over again forever
void loop() {
  int value;

  if (joyX.readValue(&value)) {
    Serial.print("X Value: ");
    Serial.println(value);
  }

  if (joyY.readValue(&value)) {
    Serial.print("Y Value: ");
    Serial.println(value);
  }
}
