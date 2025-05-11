#ifndef _IR_SENSOR_HPP_
#define _IR_SENSOR_HPP_

#pragma once

#include <iostream>
#include <Arduino.h>

class IRSensor {
    public:
    float magnitude, angle;
    bool read_success;
    bool read_serial(float result[4], int num_floats);
    void update(); // call update every loop to read serial
    float get_magnitude();
    float get_angle();
};

#endif