Arduino Temperature Display and Servo Control with OLED and DS3231 RTC
Description
This Arduino project reads temperature data from a DS3231 RTC module, displays the current time, temperature, and button presses on an SSD1306 OLED display, and controls a servo motor based on the temperature. It also counts the number of times a button is pressed.

Features
Real-Time Clock: Displays current time using the DS3231 RTC module.
Temperature Monitoring: Reads and displays ambient temperature from the DS3231.
OLED Display: Shows time, temperature, and button press count on a 128x64 OLED screen.
Servo Control: Adjusts servo motor position based on the temperature reading.
Button Press Counter: Counts and displays the number of times a button is pressed.
Components Required
Arduino Uno (or compatible board)
DS3231 Real-Time Clock (RTC) module
SSD1306 128x64 OLED display
Servo motor
Pushbutton
10kΩ Resistor (for button pull-down)
Connecting wires
Breadboard (optional)
Libraries Used
U8glib: For controlling the OLED display.
RTClib: For interacting with the DS3231 RTC module.
Wire.h: I2C communication (standard Arduino library).
Servo.h: Servo motor control (standard Arduino library).
Wiring Diagram
DS3231 RTC Module
VCC to 5V
GND to GND
SDA to A4 (Arduino Uno)
SCL to A5 (Arduino Uno)
SSD1306 OLED Display
VCC to 5V
GND to GND
SDA to A4 (Arduino Uno)
SCL to A5 (Arduino Uno)
Servo Motor
Signal Pin to Pin 9
Power to 5V (consider external power if necessary)
Ground to GND
Pushbutton
One side to Pin 8
Other side to GND
10kΩ Resistor from Pin 8 to 5V (pull-up resistor)
LEDs (Optional)
Pins 4 to 6 are set as outputs; you can connect LEDs with appropriate resistors to these pins.
Installation
Install Required Libraries

U8glib
Install via Arduino Library Manager: Sketch -> Include Library -> Manage Libraries... and search for U8glib.
RTClib
Install via Arduino Library Manager: Sketch -> Include Library -> Manage Libraries... and search for RTClib.
Set Up Hardware

Connect all components according to the wiring diagram above.
Upload the Code

Open the Arduino IDE.
Copy and paste the provided code into the IDE.
Select the correct board and port from Tools menu.
Click on the Upload button.

How It Works
Reading Time and Temperature

Uses the DS3231 RTC module to get the current time and temperature.
The getTime() function formats the time into a string.
The getTemp() function retrieves the temperature as a float.
Display on OLED

The oledWrite() function updates the OLED display with the current time, temperature, and button press count.
Uses the U8glib library to communicate with the SSD1306 OLED display.
Servo Control

The servoWrite() function maps the temperature to a servo angle and moves the servo accordingly.
Temperature values are directly written to the servo angle for simplicity.
Button Press Counting

Reads the state of a pushbutton connected to pin 8.
Increments the buttonPresses counter each time the button state changes to HIGH.
Debounce logic is mentioned but not fully implemented (debounce delay is set to 0).
Possible Improvements
Implement Proper Debouncing

Adjust the debounceDelay and debounce logic to prevent false triggering.
Temperature to Servo Angle Mapping

Map the temperature range to the servo's 0-180 degree range for more meaningful movement.
Input Pull-up Resistor

Use pinMode(buttonPin, INPUT_PULLUP); to enable the internal pull-up resistor and simplify wiring.
Power Considerations

Use an external power supply for the servo if it draws too much current from the Arduino.
Error Handling

Add error checks for sensor readings and handle exceptions.
Notes
Ensure all connections are secure to prevent intermittent behavior.
The code sets the RTC time to the time of compilation (rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));).
Commented-out code sections can be removed or uncommented as needed.
License
This project is licensed under the MIT License - see the LICENSE file for details.

Acknowledgments
Inspired by projects integrating RTC modules and OLED displays.



