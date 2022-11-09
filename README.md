# PIC12F1822_EasySleepTimer
This code is for a PIC microcontroller that can set a sleep timer with only one switch.
Here is the schematic.

<img src="https://user-images.githubusercontent.com/117799191/200765787-d8826f70-fc15-4e05-a745-0c2710f002e4.png" style="width: 300px;">


Usage:
- Press the button to power on the device and the LED will light up for 3 seconds.
- After the LED turns off, press the button to power off the device.
- If you more press the button during LED lighting in power on, it will set sleep timer for 30 minutes by press numbers (Maximum 10 times, 5 hours).
- When the sleep timer is set, the LED blinks the number of times the button is pressed and starts counting time until the power is turned off.
