#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

#include <iostream>

using namespace std;

#include "vector.hpp"
#include "motor_controller.hpp"
#include "position_system.hpp"

// declarations here
void blinkLED();

PositionSystem pos_sys;
MotorController motor_ctrl;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);

  motor_ctrl.setup(); // pin definitions
  pos_sys.setup(); // pin definitions and bno055
}

void loop() {
  pos_sys.update();
  Serial.println(pos_sys.get_tilt());
  motor_ctrl.run_motors(100, 0, -pos_sys.get_tilt());
}

// function definitions here
void blinkLED() {
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
}