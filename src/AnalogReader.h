/*
 * AnalogReader - Reliably get analog input
 *
 * Copyright (c) 2022 Volker Wiegand <volker@railduino.de>
 * Distributed under MIT license - see LICENSE for details
 *
 */

#ifndef AnalogReader_h
#define AnalogReader_h

#include "Arduino.h"

#define DEFAULT_LOWER 0
#define DEFAULT_UPPER 1023

/*
 * For a detailed description of the interface see the .cpp file
 */

class AnalogReader {
  public:
    AnalogReader(int pin, bool center, int lower, int upper);
    AnalogReader(int pin, bool center);

    bool readValue(int *pValue);
    int  getMiddle(void);
    int  getCurrent(void);

  private:
    bool _startup;
    int  _pin;
    bool _center;
    int  _lower;
    int  _upper;
    int  _middle;
    int  _curr;
    int  _prev;
};

#endif
