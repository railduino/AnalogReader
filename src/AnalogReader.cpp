/*
 * AnalogReader - Reliably get analog input
 *
 * Copyright (c) 2022 Volker Wiegand <volker@railduino.de>
 * Distributed under MIT license - see LICENSE for details
 *
 */

#include "Arduino.h"
#include "AnalogReader.h"

/*
 * The constructor has three arguments:
 * - pin     - Analog input pin
 * - lower   - lower bound after mapping
 * - upper   - upper bound after mapping
 */

AnalogReader::AnalogReader(int pin): AnalogReader(pin, DEFAULT_LOWER, DEFAULT_UPPER)
{
}

AnalogReader::AnalogReader(int pin, int lower, int upper)
{
  _pin = pin;
  pinMode(_pin, INPUT);
  _lower = lower;
  _upper = upper;
}

/*
 * The begin() function must be called within the setup() function.
 * It records the initial state and calibrates the axis.
 * In most cases the neutral position will not be exactly at 511
 * (which is half of the maximum at 10 bit resolution).
 */

void AnalogReader::begin(void)
{
  _middle = readValue(0);
  update();
  _prev = _curr;
}

/*
 * The update() function has to be called in every loop() function.
 * Only then the analog value is current and valid.
 */

void AnalogReader::update(void)
{
  int value = readValue(_middle);

  _prev = _curr;
  _curr = map(value, 0, 1023, _lower, _upper);
}

/*
 * Read the analog input. The reading is repeated until
 * the last and current values are identical.
 * If the last and current reading are only one apart,
 * it is considered noise and will not update the value.
 * The funny mapping with multiplying and dividing helps
 * to distribute values evenly and stays within 16 bit.
 *
 * Arguments:
 * - middle  - zero for calibration ot the neutral position
 */

int AnalogReader::readValue(int middle)
{
  int value, proof;

  value = analogRead(_pin);
  while ((proof = analogRead(_pin)) != value) {
    value = proof;
  }

  if (middle == 0 || (middle >= 510 && middle <= 512)) {
    return value;
  }

  if (value < middle - 1) {
    value = map(value*16, 0, middle*16, 0, 511*16) / 16;
  } else if (value > middle + 1) {
    value = map(value*16, middle*16, 1023*16, 512*16, 1023*16) / 16;
  } else {
    value = 511;
  }

  return value;
}

/*
 * The getMiddle() function serves more or less a diagnostic
 * purpose. It delivers the unmapped reading that is being
 * used for calibration, assuming the axe is in a neutral
 * position when the device is read for the first time.
 */

int AnalogReader::getMiddle(void)
{
  return _middle;
}

/*
 * The getValue() function returns the current axis reading.
 */

int AnalogReader::getValue(void)
{
  return _curr;
}

/*
 * The isChanged() function indicates a changed reading and
 * is valid after calling update().
 */

bool AnalogReader::isChanged(void)
{
  return (_curr != _prev);
}
