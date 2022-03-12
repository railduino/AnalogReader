# AnalogReader
This library is a wrapper around the Arduino **analogRead()** function.

### Features

- *Auto calibration*
  - Some joysticks do not provide a middle (or neutral) reading at exactly half of the maximum input voltage. For an AVR micro-controller this would be 511, but the range I have seen goes from 495 to 520. Therefore the **analogReader** can be configured to take the first reading as the middle value and to return 511. Values below and above are distributed evenly between 0 and 511, or 511 and 1023, accordingly.
- *Value mapping*
  - AVR controllers return analog values in the range between 0 and 1023, having a resolution of 10 bits. It may be desirable to map these values e.g. to 0 to 255 for returning byte values, or to -511 to +511. Therefore a call to the Arduino built-in **map()** function is included.

### Usage

TODO

