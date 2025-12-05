//
// Created by Carlos Mendez on 12/1/25.
//

#ifndef LOCATION_H
#define LOCATION_H
#include <string>
#include <iostream>

class Location {
    int LocationID;
    std::string Name;
    float Lat;
    float Lon;

public:
    Location(int locationID, std::string name, float lat, float lon);

    int getLocationID();
    std::string getName();
    float getLat();
    float getLon();
};

#endif //LOCATION_H
