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
 * The constructor has four arguments:
 * - pin     - Analog input pin
 * - center  - Flag for joystick type (middle position)
 * - lower   - lower bound after mapping
 * - upper   - upper bound after mapping
 */

AnalogReader::AnalogReader(int pin, bool center, int lower, int upper)
{
  _pin = pin;
  pinMode(_pin, INPUT);
  _center = center;
  _lower = lower;
  _upper = upper;
}

/*
 * There is a shortcut if the lower and upper bounds are 0 and 1023
 */

AnalogReader::AnalogReader(int pin, bool center): AnalogReader(pin, center, DEFAULT_LOWER, DEFAULT_UPPER)
{
}

/*
 * The begin() function must be called within Arduino's setup().
 * It records the initial state and calibrates the axis.
 *
 * Calibrating is necessary for e.g. joysticks having a
 * center (or middle) position and a range from 0 to 1023.
 * In most cases the center position is not exactly at 511
 * (which is half of the maximum at 10 bit resolution).
 */

void AnalogReader::begin(void)
{
  if (_center) {
    _middle = readValue();
  } else {
    _middle = 0;
  }

  update();
  _prev = _curr;
}

/*
 * The update() function has to be called in every loop() function.
 * Only then the analog value is current and valid.
 *
 * The funny mapping with multiplying and dividing helps
 * to distribute values evenly and stays within 16 bit.
 */

void AnalogReader::update(void)
{
  int value = readValue();

  if (_center) {
    if (value < _middle - 1) {
      value = map(value*16, 0, _middle*16, 0, 511*16) / 16;
    } else if (value > _middle + 1) {
      value = map(value*16, _middle*16, 1023*16, 512*16, 1023*16) / 16;
    } else {
      value = 511;
    }
  }

  _prev = _curr;
  _curr = map(value, 0, 1023, _lower, _upper);
}

/*
 * Read the analog input. The reading is repeated until
 * the previous and current values are identical.
 */

int AnalogReader::readValue(void)
{
  int value, proof;

  value = analogRead(_pin);
  while ((proof = analogRead(_pin)) != value) {
    value = proof;
  }

  return value;
}

/*
 * The getMiddle() function serves more or less a diagnostic
 * purpose. It delivers the unmapped reading that is being
 * used for calibration, assuming the axis is in the middle
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
