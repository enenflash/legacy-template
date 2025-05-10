#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

#include <iostream>

using namespace std;

#include "pins.h"
#include "vector.hpp"
#include "motor_controller.hpp"
// #include "position_system.hpp"

// declarations here
void blinkLED();

// PositionSystem pos_sys;
MotorController motor_ctrl;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(DEBUG_LED, OUTPUT);

  pinMode(TL_PWM, OUTPUT);
  pinMode(TR_PWM, OUTPUT);
  pinMode(BL_PWM, OUTPUT);
  pinMode(BR_PWM, OUTPUT);

  analogWriteFrequency(TL_PWM, 20000);
  analogWriteFrequency(TR_PWM, 20000);
  analogWriteFrequency(BL_PWM, 20000);
  analogWriteFrequency(BR_PWM, 20000);

  pinMode(TL_DIR, OUTPUT);
  pinMode(TR_DIR, OUTPUT);
  pinMode(BL_DIR, OUTPUT);
  pinMode(BR_DIR, OUTPUT);

  // motor_ctrl.setup(); // pin definitions
  // pos_sys.setup(); // pin definitions and bno055
}

void loop() {
  // pos_sys.update();
  // Serial.println(pos_sys.get_tilt());
  motor_ctrl.run_motors(100, 0, 0);
  digitalWrite(DEBUG_LED, HIGH);
}

// function definitions here
void blinkLED() { 
  digitalWrite(DEBUG_LED, HIGH);
  delay(100);
  digitalWrite(DEBUG_LED, LOW);
  delay(100);
}