#include "BalancingControl.h"

void BalancingControl::Initialize() {
    this->pid_p_gain = 15.0;                                       //Gain setting for the P-controller (15)
    this->pid_i_gain = 1.5;                                      //Gain setting for the I-controller (1.5)
    this->pid_d_gain = 10.0;                                       //Gain setting for the D-controller (30)
    this->turning_speed = 30;                                    //Turning speed (20)
    this->max_target_speed = 150;                                //Max target speed (100)
}

void BalancingControl::SetPidPLevel(byte data) {
  pid_p_gain = data/4.0;
}
void BalancingControl::SetPidILevel(byte data) {
  pid_i_gain = data/4.0;
}
void BalancingControl::SetPidDLevel(byte data) {
  pid_d_gain = data/4.0;
}

byte BalancingControl::GetPidPLevel() {
    return 4*pid_p_gain;
}

byte BalancingControl::GetPidILevel() {
    return 4*pid_i_gain;
}

byte BalancingControl::GetPidDLevel() {
    return 4*pid_d_gain;
}
