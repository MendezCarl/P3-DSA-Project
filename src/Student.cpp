//
// Created by Carlos Mendez on 11/18/25.
//

#include "Student.h"

void Student::createStudent(int id, std::string& firstName, int amount, std::vector<std::string>& inputClasses, int origin) {
    ID = id;
    name = firstName;
    numOfClasses = amount;
    classes = inputClasses;
    residence = origin;
}

int Student::getID() {
    return ID;
}

// std::string Student::getFirstName() {
//     return name;
// }

std::string Student::getName() {
    return name;
}

int Student::getNumOfClasses() {
    return numOfClasses;
}


std::vector<std::string> Student::getClasses() {
    return classes;
}

int Student::getResidence() {
    return residence;
}
