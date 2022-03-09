/*
 * Test program for a dual axis joystick
 */

#include <AnalogReader.h>

AnalogReader joyX(A0);
AnalogReader joyY(A1, 0, 255);

char buffer[32];

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  delay(1000);

  joyX.begin();
  joyY.begin();

  sprintf(buffer, "midX=%d midY=%d", joyX.getMiddle(), joyY.getMiddle());
  Serial.println(buffer);
}

// the loop function runs over and over again forever
void loop() {
  joyX.update();
  if (joyX.isChanged()) {
    sprintf(buffer, "newX=%d", joyX.getValue());
    Serial.println(buffer);
  }

  joyY.update();
  if (joyY.isChanged()) {
    sprintf(buffer, "newY=%d", joyY.getValue());
    Serial.println(buffer);
  }
}
