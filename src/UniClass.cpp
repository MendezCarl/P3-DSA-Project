//
// Created by Carlos Mendez on 12/1/25.
//

#include "UniClass.h"
UniClass::UniClass(std::string classCode, int hour, int minute, int locationID) {
    ClassCode = classCode;
    Time = std::make_pair(hour, minute);
    LocationID = locationID;
}

void UniClass::updateLocation(int location) {
    LocationID = location;
}

void UniClass::updateTime(int hour, int minute) {
    Time = std::make_pair(hour, minute);

}

void UniClass::updateActivity(bool active) {
    Active = active;
}

std::string UniClass::getClassCode() {
    return ClassCode;
}

int UniClass::getHour() {
    return Time.first;
}

int UniClass::getMinute() {
    return Time.second;
}

int UniClass::getLocationID() {
    return LocationID;
}

bool UniClass::getActivity() {
    return Active;
}

