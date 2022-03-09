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
    AnalogReader(int pin, int lower, int upper);
    AnalogReader(int pin);

    void begin(void);        // must be called in setup()
    void update(void);       // must be called in loop()

    int getMiddle(void);
    int getValue(void);
    bool isChanged(void);

  private:
    int _pin;
    int _lower;
    int _middle;
    int _upper;
    int _curr;
    int _prev;

    // Internal function to reliably read analog values
    int readValue(int middle);
};

#endif
