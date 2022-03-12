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
 * - center  - Dead zone for joystick type (middle position)
 * - lower   - lower bound after mapping
 * - upper   - upper bound after mapping
 */

AnalogReader::AnalogReader(int pin, int center, int lower, int upper)
{
  _pin = pin;
  pinMode(_pin, INPUT);

  _center = center;
  _lower = lower;
  _upper = upper;

  _startup = true;
}

/*
 * There is a shortcut if the lower and upper bounds are 0 and 1023
 */

AnalogReader::AnalogReader(int pin, int center): AnalogReader(pin, center, DEFAULT_LOWER, DEFAULT_UPPER)
{
}

/*
 * The readValue() function is the main workhorse.
 * During normal course of operation it is the only
 * function that needs to be called during loop().
 *
 * It returns both the state (changed or not) and the
 * current value (assuming an int pointer argument).
 *
 * Calibrating is necessary for e.g. joysticks having a
 * center (or middle) position and a range from 0 to 1023.
 * In most cases the center position is not exactly at 511
 * (which is half of the maximum at 10 bit resolution).
 */

bool AnalogReader::readValue(int *pValue)
{
  int value, proof;

  value = analogRead(_pin);
  while ((proof = analogRead(_pin)) != value) {
    value = proof;
  }

  if (_startup) {
    if (_center > 0) {
      _middle = value;
      _midmin = _middle - _center;
      _midmax = _middle + _center;
      _curr = _lower + ((_upper - _lower) / 2);
    } else {
      _curr = map(value, 0, 1023, _lower, _upper);
    }
    _prev = _curr;
    if (pValue != NULL) {
      *pValue = _curr;
    }
    _startup = false;
    return true;
  }

  if (_center > 0) {
    if (value <= _midmin) {
      value = map(value*16, 0, _midmin*16, 0, 511*16) / 16;
    } else if (value >= _midmax) {
      value = map(value*16, _midmax*16, 1023*16, 512*16, 1023*16) / 16;
    } else {
      value = 511;
    }
  }

  _prev = _curr;
  _curr = map(value, 0, 1023, _lower, _upper);

  if (pValue != NULL) {
    *pValue = _curr;
  }

  return (_curr != _prev);
}

/*
 * The getMiddle() function serves more or less a diagnostic
 * purpose. It delivers the unmapped reading that is being
 * used for calibration, assuming the stick is in the middle
 * position when the device is read for the first time.
 * It is valid only after a call to readValue().
 */

int AnalogReader::getMiddle(void)
{
  return _middle;
}

/*
 * The getValue() function returns the current axis reading.
 * It is valid only after a call to readValue().
 */

int AnalogReader::getCurrent(void)
{
  return _curr;
}
