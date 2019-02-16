# 3D-Printer-Enclosure-Temperature-Control
An Arduino-based environmental temperature controller for 3D printer enclosures.

This project integrates an Arduino Uno R3, MAX6675 breakout board, Type-K thermocouple, two 5v 120mm PC case fans, and two 5v 180deg servo motors.

Arduino Uno R3: Controls the entire machine.

MAX6675 Breakout Board: Allows easy integration of the Type-K thermocouple.

Type-K Thermocouple: Allows temperature readings.

2x 5v 120mm PC Case Fans: Handles cooling.

2x 5v 180deg Servo Motors: Opens louvers to retain enclosure heat when not beyond threshold.

The temperature thresholds, duty cycles, operation of the servos, and delays between all movements are easily changed, as the code has been thoroughly commented. It is quite easy to make it more sensitive to heat, less sensitive to heat, or have the louvers open as a stage 1 cooling method before the fans even activate. In addition, adding an LCD display to show the current temperature, fan mode, and target temperature would be a simple matter, and will be covered in a future release.
