//
// Created by Carlos Mendez on 12/1/25.
//

#ifndef UNICLASS_H
#define UNICLASS_H
#include <string>

class UniClass {
    std::string ClassCode;
    std::pair<int, int> Time;
    int LocationID;
    bool Active = true;

public:
    UniClass(std::string classCode, int hour, int minute, int locationID);
    // void createClass(std::string code, std::string className, int hour, int minute, int location);

    void updateTime(int hour, int minute);
    void updateLocation(int location);
    void updateActivity(bool active);

    std::string getClassCode();

    int getHour();
    int getMinute();
    int getLocationID();
    bool getActivity();

};

#endif //UNICLASS_H


