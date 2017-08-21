What Is This?
=============

It's the software for running inside an Arduino project to control a refrigerator.

Building
========

Dependencies
------------

- gcc
- gcc-avr
- gcc-multilib
- g++-multilib
- arduino/Wire
- arduino/EEPROM

Also:
- https://github.com/marcoschwartz/LiquidCrystal_I2C
- https://github.com/z3t0/Arduino-IRremote

Remote Config
=============

<pre>
/--------------\
| ON |MODE|MUTE|
|----|----|----|
|PLAY|PREV|NEXT|
|----|----|----|
| EQ | -  | +  |
|----|----|----|
| 0  |Shuf|U/SD|
|----|----|----|
| 1  | 2  | 3  |
|----|----|----|
| 4  | 5  | 6  |
|----|----|----|
| 7  | 8  | 9  |
\--------------/
</pre>

Legend:
-------
- ON turn the display On / Off
- PLAY enter selection
- PREV previous item
- NEXT next menu
- \- store minimum value
- \+ store maximum value
- 1~9 direct access to item

