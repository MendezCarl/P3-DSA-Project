//
// Created by Carlos Mendez on 12/1/25.
//

#include "UniClass.h"

UniClass::UniClass(std::string classCode, int hour, int minute,int endHour, int endMinute, int locationID) {
    ClassCode = classCode;
    StartTime = std::make_pair(hour, minute);
    EndTime = std::make_pair(endHour, endMinute);
    LocationID = locationID;
}

void UniClass::updateLocation(int location) {
    LocationID = location;
}

void UniClass::updateTime(int startHour, int startMinute, int endHour, int endMinute) {
    StartTime = std::make_pair(startHour, startMinute);
    EndTime = std::make_pair(endHour, endMinute);
}


void UniClass::updateActivity(bool active) {
    Active = active;
}

std::string UniClass::getClassCode() {
    return ClassCode;
}

int UniClass::getStartHour() {
    return StartTime.first;
}

int UniClass::getStartMinute() {
    return StartTime.second;
}

int UniClass::getEndHour() {
    return EndTime.first;
}

int UniClass::getEndMinute() {
    return EndTime.second;
}

int UniClass::getLocationID() {
    return LocationID;
}

bool UniClass::getActivity() {
    return Active;
}

