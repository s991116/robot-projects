#include "DistanceCheck.h"

DistanceCheck::DistanceCheck(Distance* distance) {
    _Distance = distance;
    this->SettingsInt["DISTANCE"] = &_DistanceToRun;
}

void DistanceCheck::Prepare() {
    _Distance->ResetDistance();
}

bool DistanceCheck::Test() {
    if (_DistanceToRun >= 0) {
        return (_DistanceToRun < _Distance->GetDistance());
    } else {
        return (_DistanceToRun > _Distance->GetDistance());
    }
}

DistanceCheck::~DistanceCheck() {
}

