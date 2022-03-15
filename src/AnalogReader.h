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
    AnalogReader(int pin, int center, int lower, int upper);
    AnalogReader(int pin, int center);

    bool readValue(int *pValue);
    int  getMiddle(void);
    int  getCurrent(void);

  private:
    int _pin;
    int _center;
    int _lower;
    int _upper;
    int _middle;
    int _midmin;
    int _midmax;
    int _oldval;
    int _curr;
    int _prev;
    bool _startup;
};

#endif
