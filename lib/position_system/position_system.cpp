#include "position_system.hpp"

PositionSystem::PositionSystem(bool use_otos, bool use_ult) {
    this->bno = Adafruit_BNO055(55);
    this->bno_ok = false;

    this->use_otos = use_otos;
    this->use_ult = use_ult;
    
    this->opp_goal_posv = Vector(0, 91.5);
    this->own_goal_posv = Vector(0, -91.5);
    this->posv = Vector(0, 0);
    this->tilt = 0;
}

bool PositionSystem::check_bno_ok() {
    return this->bno_ok;
}

Vector PositionSystem::get_posv() {
    return this->posv;
}
float PositionSystem::get_tilt() {
    return this->tilt;
}

Vector PositionSystem::get_relative_to(Vector other_posv) {
    return Vector(other_posv.i-this->posv.i, other_posv.j-this->posv.j);
}

Vector PositionSystem::get_opp_goal_vec() {
    return this->get_relative_to(this->opp_goal_posv);
}
Vector PositionSystem::get_own_goal_vec() {
    return this->get_relative_to(this->own_goal_posv);
}

void PositionSystem::setup() {
    this->bno_ok = this->bno.begin();
    this->bno.setExtCrystalUse(true);
    
    pinMode(UL_TRIG, OUTPUT);
    pinMode(UR_TRIG, OUTPUT);
    pinMode(UB_TRIG, OUTPUT);
    pinMode(UL_ECHO, INPUT);
    pinMode(UR_ECHO, INPUT);
    pinMode(UB_ECHO, INPUT);
}

void PositionSystem::update() {
    // get tilt from BNO or get tilt from parameter
    sensors_event_t event;
    this->bno.getEvent(&event);
    this->tilt = event.orientation.x;

    // could potentially implement a method that uses both ultrasonics and otos
    if (use_ult) {
        this->ult_ps.update(this->tilt);
        this->posv = this->ult_ps.get_posv();
    }
    if (use_otos) {
        this->posv = this->otos.get_posv();
    }
}