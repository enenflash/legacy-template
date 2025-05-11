#include "ir_sensor.hpp"

bool IRSensor::read_serial(float result[4], int num_floats) {
    const size_t total_bytes = num_floats * sizeof(float);

    // Wait until all float bytes are available
    unsigned long start = millis();
    while (Serial6.read() != 'e' && Serial6.available() < total_bytes) {
        if (millis() - start > 100) return false;
    }
    byte* byte_ptr = (byte*)result;
    for (size_t i = 0; i < total_bytes; i++) {
        byte_ptr[i] = Serial6.read();
    }
    return true;
}

void IRSensor::update() {
    float result[4];
    this->read_success = false;
    if (Serial6.available()) {
        this->read_success = this->read_serial(result, 4);
    }
    if (this->read_success) {
        this->angle = result[0];
        this->magnitude = result[1];
    }
}

float IRSensor::get_magnitude() {
    return this->magnitude;
}

float IRSensor::get_angle() {
    return this->angle;
}