//
// Created by Carlos Mendez on 12/1/25.
//

#include "Location.h"

Location::Location(int location, std::string name, float lat, float lon) {
    LocationID = location;
    Name = name;
    Lat = lat;
    Lon = lon;
}

float Location::getLat() {
    return Lat;
}

float Location::getLon() {
    return Lon;
}

int Location::getLocationID() {
    return LocationID;
}

std::string Location::getName() {
    return Name;
}


