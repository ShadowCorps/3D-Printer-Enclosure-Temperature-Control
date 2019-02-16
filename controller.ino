/////////////////////////////////////////////
// TEMPERATURE CONTROL SCRIPT FOR ENCLOSURE//
/////////////////////////////////////////////

///////This is a simple controller script used to incorporate
//an Arduino Uno, MAX6675 breakout board, type-K thermocouple,
//two servos, and two 120mm fans. This is used to monitor the 
//interior temperature of an enclosure, and if the heat rises
//too far, the servos will actuate a cover, and the fans will
//turn on in short order. The temperatures are all in Celsius,
//and can be adjusted manually in this file to make the system
//either more sensitive or more forgiving. A simple shakedown
//operation can also be added. You will need the Servo and MAX
//6675 libraries for this to work. Something to consider may
//also be allowing the Arduino intergration to an SSR to 
//deactivate the printer in the even that thermals read high
//at an unsafe level (this default will act up to 100C, which
//is 212F - your printer might be on fire by that point).

//Created by Craig Easter of Easterworks.
//https://easterworks.blogspot.com/

#include <Servo.h> // Servo library access.
#include <max6675.h> // Thermocouple library access.

// Assigning servos.
Servo leftServo; 
Servo rightServo;

// Assigning pins for servos and fans.
int leftServoPin = 0; // Servos can be assigned to a digital pin for output and still send degrees instead of just "HIGH" and "LOW".
int rightServoPin = 1;
int leftFanPin = A0; // Fans are assigned to analog pins to allow them to receive different speed values.
int rightFanPin = A1;
int val = 0;

// Thermocouple pin assignments.
int thermoDO = 4; 
int thermoCS = 5;
int thermoCLK = 6;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

int vccPin = 3;
int gndPin = 2;

// Variables for the fans.
int leftFan = 0;
int rightFan = 0;

void setup() { // Defines the servos, fans, and operation modes for all pins.
  leftServo.attach(0);
  rightServo.attach(1);
  pinMode(leftServoPin, OUTPUT);
  pinMode(rightServoPin, OUTPUT);
  pinMode(leftFanPin, OUTPUT);
  pinMode(rightFanPin, OUTPUT);
  pinMode(vccPin, OUTPUT); 
  digitalWrite(vccPin, HIGH);
  pinMode(gndPin, OUTPUT);
  digitalWrite(gndPin, LOW);

// By default, nothing happens at startup, but these values can be edited for a "shakedown" run at startup, which may be a good idea to clear dust/debris if present. Delays should be added in that case.
  leftServo.write(0); 
  rightServo.write(0);
  analogWrite(leftFanPin, 0);
  analogWrite(rightFanPin, 0);
  delay(1000); // Gives everything a second to start up.
}

void loop() { // The loop polls the thermocouple, translates it into Celsius, and determines what fanspeed of the existing 5 settings is best. This will need to be tested and ought to be replaced with a float.

// Thermocouple takes a reading at the beginning of every loop.
  thermocouple.readCelsius(); 

// This method determines if the shutters should be held open or remain closed based on if the ambient temperature is above or below 37.8C.
    
  if (thermocouple.readCelsius() >= 37.8)  
  {
    leftServo.write(180); // Servo is "open".
    delay(15); 
    rightServo.write(180); 
    delay(15); 
  }
  else 
  {
    leftServo.write(0); // Servo is "closed".
    delay(15);
    rightServo.write(0);
    delay(15);
  } 

// This method polls the thermocouple every second to determine which fan speed to pick. analogWrite will use PWM to control the fans and will shift over the delay if assigned to pins that support it, otherwise the voltage will just change sharply.

  if (thermocouple.readCelsius() >= 100) 
  {
    analogWrite(leftFanPin, 255); // MAX-SPEED
    analogWrite(rightFanPin, 255);
    return; // will skip the rest of the checks if this is true, otherwise it will continue checking.
  } else if (thermocouple.readCelsius() >= 82.2)
  {
    analogWrite(leftFanPin, 200); // upper-mid speed
    analogWrite(rightFanPin, 200);
    return;
  } else if (thermocouple.readCelsius() >= 65.6)
  {
    analogWrite(leftFanPin, 150); // mid-speed
    analogWrite(rightFanPin, 150);
    return;
  } else if (thermocouple.readCelsius() >= 48.9)
  {
    analogWrite(leftFanPin, 100); // lower-mid speed
    analogWrite(rightFanPin, 100);
    return;
  } else if (thermocouple.readCelsius() >= 37.8)
  {
    analogWrite(leftFanPin, 50); // MIN-SPEED
    analogWrite(rightFanPin, 50);
    return;
  } else
  {
    analogWrite(leftFanPin, 0); // OFF
    analogWrite(rightFanPin, 0);
  }

}
