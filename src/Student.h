//
// Created by Carlos Mendez on 11/18/25.
//

#ifndef STUDENT_H
#define STUDENT_H

#endif //STUDENT_H
#include <utility>
#include <vector>
#include <string>

class Student {
    int ID;
    std::string Name;
    int NumOfClasses;
    std::vector<std::string> Classes;
    int Residence;

public:
    Student(int id, std::string name, std::vector<std::string> classes, int residence);
    // void createStudent(int id, std::string& firstName, int numOfClasses, std::vector<std::string>& classes, int origin);

    int getID();

    std::string getName();

    int& getNumOfClasses();
    std::vector<std::string>& getClasses();

    int getResidence();
};