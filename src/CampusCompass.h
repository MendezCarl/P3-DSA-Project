#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>

#include "Student.h"
#include "Location.h"
#include "UniClass.h"
#include "Edge.h"

using namespace std;

class CampusCompass {
private:
    // Think about what member variables you need to initialize
    // perhaps some graph representation?

    //adjancey list approach
    std::map<int, Location> locationByID; // key: id, value: location
    std::map<std::string, UniClass> classByCode; // key: class name, value: UniClass object
    std::map<int, Student> students;
    std::map<int, std::vector<Edge>> adjList; // key: locationID, value: vector<edges>

public:
    // Think about what helper functions you will need in the algorithm
    CampusCompass(); // constructor

    bool ParseCSV(const string &edges_filepath, const string &classes_filepath);
    bool ParseLocationsCSV(const std::string &locationsFilepath);
    bool ParseCommand(const string &command);

    template<typename... Classes>
    void insert(std::string studentName, int studentId, int origin, int numOfClasses,Classes... classes); //returns successful or unsuccessful
    void remove(int studentID); //returns successful or unsuccessful

    void dropClass(int studentID, std::string classCode); //if student has 0 classes drop them as well
    void replaceClass(int studentID, std::string classCode1, std::string classCode2);
    void removeClass(const std::string& classCode); //removes class and prints how many students were removed from the class

    template<typename... Edges>
    void toggleEdgesClosures(int numberOfClosures, Edges... edges); //don't remove edges just turns them off
    void checkEdgeStatus(int origin, int end); //open, close, DNE
    void isConnected(int origin, int end); //checks if travel is possible, does not matter if it's open or not

    void printShortestEdges(int id); //print shortest time for student to walk from origin to all their classes
};
