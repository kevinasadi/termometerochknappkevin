#include "U8glib.h"
#include <RTClib.h>
#include <Wire.h>
#include "Servo.h"


// av kevin asadi
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);


// unsigned long myTime;
#define DS3231_I2C_ADDR             0x68
#define DS3231_TEMPERATURE_ADDR     0x11

Servo myservo;
#define servoPin 9


DateTime now;

RTC_DS3231 rtc;
char t[32];
byte control_reg, temperature_lsb;
char temperature_msb;

const int buttonPin = 8;
int buttonPresses = 0;

void setup() {
  for(int i= 4; i <= 6; i++){
    pinMode(i, OUTPUT);
  }
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
  //rtc.adjust(DateTime(2019, 1, 21, 5, 0, 0));

  myservo.attach(servoPin);
 // myservo.write(0);

}
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0; 
const unsigned long debounceDelay = 0; 

void loop() {
  now = rtc.now();
  
  oledWrite(getTime(), getTemp());
  servoWrite(getTemp());

  // Read the button state
  int reading = digitalRead(buttonPin);
  
  // Debounce Logic
  

  // If the button state has been stable for longer than debounceDelay

    if (reading != lastButtonState) {
      lastButtonState = reading;

      if (reading != LOW) {
        buttonPresses += 1;
      }
    }

}



/*
* This function reads the temperature output from the ds3231 module
*Parameters: Void
*Returns: temprature as float
*/
float getTemp(){ //getTemp function, when called returns the current Temperature(float)
  float tempC = rtc.getTemperature();
  return tempC;
}

// void alarm(){
//   for (int i=4; i<= 6; i++) {
//   digitalWrite(i, HIGH);
//   delay(100);
//   digitalWrite(i, LOW);
//   }
//   for (int i=6; i>= 4; i--) {
//   digitalWrite(i, HIGH);
//   delay(100);
//   digitalWrite(i, LOW);
// }
// }


/*
* This function takes a string and a float and draws them on the oled display(Time and Temp)
*Parameters: - time: String to write to display, temp: float to write to display as temp
*Returns: void
*/
void oledWrite(String time, float temp){//When called with and inputted with time and a temp, writes the values on oled
  String temp_str = String(temp,2);
    String button_str = "Presses: " + String(buttonPresses); 

  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_unifont);
    u8g.drawStr(10, 20, time.c_str());
    u8g.drawStr(10, 40, "Temp: ");

    u8g.drawStr(50, 40, temp_str.c_str());
    u8g.drawStr(10, 60, button_str.c_str()); 



  } while (u8g.nextPage());
}

/*
*This function reads time from an ds3231 module and package the time as a String
*Parameters: Void
*Returns: time in hh:mm:ss as String
*/

String getTime(){ 
  DateTime now = rtc.now();
  // sprintf(t, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());  
  return (String(now.hour()) + ":" + String(now.minute()) +  ":" +  String(now.second()));
}

float DS3231_get_treg()//Reades the temperature from the ds3231 module
{
    float rv;  // Reads the temperature as an int, to save memory
//  float rv;
    
    uint8_t temp_msb, temp_lsb;
    int8_t nint;

    Wire.beginTransmission(DS3231_I2C_ADDR);
    Wire.write(DS3231_TEMPERATURE_ADDR);
    Wire.endTransmission();

    Wire.requestFrom(DS3231_I2C_ADDR, 2);
    temp_msb = Wire.read();
    temp_lsb = Wire.read() >> 6;

    if ((temp_msb & 0x80) != 0)
        nint = temp_msb | ~((1 << 8) - 1);      // if negative get two's complement
    else
        nint = temp_msb;

    rv = 0.25 * temp_lsb + nint;

    return rv;
}

/*
* takes a temprature value and maps it to corresppnding degree on a servo
*Parameters: - value: temprature
*Returns: void
*/
void servoWrite(float temperature){
  myservo.write(temperature);
}