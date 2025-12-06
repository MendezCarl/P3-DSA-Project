//
// Created by Carlos Mendez on 11/18/25.
//

#include "Student.h"

Student::Student(int id, std::string name, int residence, std::vector<std::string> classes){
    ID = id;
    Name = name;
    Classes = classes;
    NumOfClasses = Classes.size();
    Residence = residence;
}

int Student::getID() {
    return ID;
}

std::string Student::getName() {
    return Name;
}

int& Student::getNumOfClasses() {
    return NumOfClasses;
}


std::vector<std::string>& Student::getClasses() {
    return Classes;
}

int Student::getResidence() {
    return Residence;
}
