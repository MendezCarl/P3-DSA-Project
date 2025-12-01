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
    std::string name;
    int numOfClasses;
    std::vector<std::string> classes;
    int residence;

public:
    Student();
    void createStudent(int id, std::string& firstName, int numOfClasses, std::vector<std::string>& classes, int origin);

    int getID();

    std::string getFirstName();
    std::string getLastName();

    int getNumOfClasses();
    std::vector<std::string> getClasses();

    int getResidence();
};