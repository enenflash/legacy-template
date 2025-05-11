#include "line_sensor.hpp"

bool LineSensor::read_serial(float result[2], int num_floats) {
    const size_t total_bytes = num_floats * sizeof(float);

    // Wait until all float bytes are available
    unsigned long start = millis();
    while (Serial2.read() != 'e' && Serial2.available() < total_bytes) {
        if (millis() - start > 100) return false;
    }
    byte* byte_ptr = (byte*)result;
    for (size_t i = 0; i < total_bytes; i++) {
        byte_ptr[i] = Serial2.read();
    }
    return true;
}

void LineSensor::update() {
    float result[2];
    this->read_success = false;
    if (Serial2.available()) {
        this->read_success = this->read_serial(result, 4);
    }
    if (this->read_success) {
        this->angle = result[0];
        this->distance = result[1];
    }
}

float LineSensor::get_distance() {
    return std::round(this->distance*1000)/1000;
}

float LineSensor::get_angle() {
    return std::round(this->angle*1000)/1000;
}