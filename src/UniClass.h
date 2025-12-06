//
// Created by Carlos Mendez on 12/1/25.
//

#ifndef UNICLASS_H
#define UNICLASS_H
#include <string>

class UniClass {
    std::string ClassCode;
    std::pair<int, int> StartTime;
    std::pair<int, int> EndTime;
    int LocationID;
    bool Active = true;

public:
    UniClass(std::string classCode, int hour, int minute, int endHour, int endMinute,  int locationID);
    // void createClass(std::string code, std::string className, int hour, int minute, int location);

    void updateTime(int startHour, int startMinute, int endHour, int endMinute);
    void updateLocation(int location);
    void updateActivity(bool active);

    std::string getClassCode();

    int getStartHour();
    int getStartMinute();

    int getEndHour();
    int getEndMinute();

    int getLocationID();
    bool getActivity();

};

#endif //UNICLASS_H


