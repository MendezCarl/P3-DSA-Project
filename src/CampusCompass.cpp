#include "CampusCompass.h"

#include <random>

using namespace std;

CampusCompass::CampusCompass() {
    // initialize your object

}
//make sure to skip the headerline
bool CampusCompass::ParseCSV(const string &edges_filepath, const string &classes_filepath) {
    // return boolean based on whether parsing was successful or not
    std::ifstream file(edges_filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << edges_filepath << std::endl;
        return false;
    }

    //edge file
    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string word;

        while (std::getline(ss, word, ',')) {
            if (!word.empty()) {
                row.push_back(word);
            }
        }

        //populate the adj list
        //LocationID_1, LocationID_2, Name_1, Name_2, Time

        Edge newEdge(std::stoi(row[0]),std::stoi(row[1]),std::stoi(row[4]));
        if (adjList.count(std::stoi(row[0]))) {
            adjList[std::stoi(row[0])].push_back(newEdge);
        } else {
            std::vector<Edge> list;
            list.push_back(newEdge);
            adjList[std::stoi(row[0])] = list;
        }


    }
    file.close();

    //classes file
    file.open(classes_filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << classes_filepath << std::endl;
        return false;
    }

    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string word;

        while (std::getline(ss, word, ',')) {
            if (!word.empty()) {
                row.push_back(word);
            }
        }

        //[classCode, LocationID, startTime, endTime]
        UniClass newClass(row[0], std::stoi(row[2]), std::stoi(row[3]), std::stoi(row[1]));
        classByCode[row[0]] = newClass;
    }
    file.close();

    return true;
}

bool CampusCompass::ParseLocationsCSV(const std::string &locationsFilepath) {

    std::ifstream file(locationsFilepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << locationsFilepath << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string word;

        while (std::getline(ss, word, ',')) {
            if (!word.empty()) {
                row.push_back(word);
            }
        }

        //[name, LocationID, lat, lon]
        if (locationByID.count(std::stoi(row[1])) == 0) {
            Location newLocation(std::stoi(row[1]), row[0], std::stof(row[2]), std::stof(row[3]));
            locationByID[std::stoi(row[1])] = newLocation;
        }
    }
    file.close();
    return true;
}

template<typename... Classes>
void CampusCompass::insert(std::string studentName, int studentId, int origin, int numOfClasses, Classes... classes) {

    try {
        Student newStudent(studentId, studentName, numOfClasses, classes, origin);
        students[newStudent.getID()] = newStudent;

        std::cout << "successful" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "unsuccessful" << std::endl;
    }

}

void CampusCompass::remove(int studentID) {
    try {
        if (students.count(studentID) == 1) {
            students.erase(studentID);
            std::cout << "successful" << std::endl;
        }
        std::cout << "unsuccessful" << std::endl;
    } catch (const std::exception& e ){
        std::cout << "unsuccessful" << std::endl;
    }
}

void CampusCompass::dropClass(int studentID, std::string classCode) {
    try {
        //check if class exists
        if (classByCode.count(classCode) == 1) {

            //checks if student exists
            int index = 0;
            for (int i = 0; i < students.size(); i++) {
                if (students[i].getID() == studentID)
                {
                    index = i;
                    std::cout << "student exists" << std::endl;
                }
            }

            if (students[index].getNumOfClasses() > 1) {
                //check classes
                std::vector<std::string>& classes = students[index].getClasses();
                for (int i = 0; i < classes.size(); i++) {
                    if (classes[i] == classCode) {
                        //remove class from student then check again their total class
                        classes.erase(std::remove(classes.begin(), classes.end(), classCode), classes.end());
                        students[index].getNumOfClasses()--;
                    }

                    std::cout << "successful: dropped class for student" << std::endl;
                }
            } else {
                remove(students[index].getID());
                std::cout << "removed student for have 0 classes" << std::endl;
            }
        } else {
            std::cout << "unsuccessful: class DNE" << std::endl;
        }


    } catch (const std::exception& e ) {
        std::cout << "unsuccessful" << std::endl;
    }
}

void CampusCompass::replaceClass(int studentID, std::string classCode1, std::string classCode2) {
    try {
        bool replaced = false;

        //find student
        if (students.count(studentID)) {
            std::cout << "student found, replacing class" << std::endl;
        }

        //see if class exists
        std::vector<std::string> classCodes = students[studentID].getClasses();
        int index;
        for (std::string& classCode : classCodes) {
            if (classCode == classCode1) {
                classCode = classCode2;
                replaced = true;
            }
        }

        if (replaced == true) {
            std::cout << "successful" << std::endl;
        } else {
            std::cout << "unsuccessful" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "unsuccessful" << std::endl;
    }
}

//might be done but look over again
//remove from classByCode because it should remove from all students
void CampusCompass::removeClass(const std::string& classCode) {
    try {
        int adjustedCounter = 0;

        // for (Student& student : students) {
        //     std::vector<std::string> classCodes = student.getClasses();
        //     for (auto& callCode : classCodes) {
        //         if (classCode.empty()) {
        //             std::cout << "Student has no classes :" << student.getName() << std::endl;
        //         } else {
        //             if (callCode == classCode) {
        //                 classCodes.erase(classCodes.begin());
        //                 int numOfClasses = student.getNumOfClasses();
        //                 numOfClasses--;
        //
        //                 adjustedCounter++;
        //             }
        //         }
        //     }
        // }

        //first check if it exists
        if (classByCode.count(classCode) == 1) {
            //deactivate class
            classByCode[classCode].updateActivity(false);

            //search through each student removing deactivated class from their list
            for (auto& [key, value]: students) {
                std::vector<std::string>& studentClasses = value.getClasses();
                auto it = std::find(studentClasses.begin(), studentClasses.end(), classByCode[classCode].getClassCode());

                if (it != studentClasses.end()) {
                    studentClasses.erase(it);
                    value.getNumOfClasses()--;
                    adjustedCounter++;
                }
            }
            std::cout << "removed class: " << classCode << "from "<< adjustedCounter << "Students." <<std::endl;
        } else {
            std::cout << "unsuccessful" << std::endl;
        }

    } catch (const std::exception& e ) {
        std::cout << "error removing class: " << e.what() << std::endl;
    }
}

template<typename... Edges>
void CampusCompass::toggleEdgesClosures(int numberOfClosures, Edges... edges) {
    try {
        if (numberOfClosures % 2 == 0) {
            for (int i = 0; i < edges.size();) {
                int from = edges[i];
                int to = edges[i + 1];
                i+=2;

                for (auto& edge: adjList[from]) {
                    if (edge.getTo() == to) {
                       if (edge.isEdgeOpen()) {
                           edge.closeEdge();
                       } else {
                           edge.openEdge();
                       }
                    }
                }
            }
            std::cout << "successful" << std::endl;
        }

        std::cout << "unsuccessful: uneven amount of closures requested" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "unsuccessful" << std::endl;
    }
}

void CampusCompass::checkEdgeStatus(int origin, int end) {
    if (adjList.count(origin) == 1) {
        for (auto& edge: adjList[origin]) {
            if (edge.getTo() == end) {
                if (edge.isEdgeOpen()) {
                    std::cout << "edge is open" << std::endl;
                    return;
                }
            }
        }
        std::cout << "edge is closed" << std::endl;
        return;
    }
    std::cout << "edge DNE" << std::endl;
}

void CampusCompass::isConnected(int origin, int end) {
    if (adjList.count(origin) == 1) {
        for (auto& edge: adjList[origin]) {
            if (edge.getTo() == end) {
                std::cout << "successful" << std::endl;
                return;
            }
        }
    }

    std::cout << "unsuccessful" << std::endl;
}

void CampusCompass::printShortestEdges(int id) {
    //implement dikjasrtas
}

bool CampusCompass::ParseCommand(const string &command) {
    // do whatever regex you need to parse validity
    // hint: return a boolean for validation when testing. For example:
    bool is_valid = true; // replace with your actual validity checking

    return is_valid;
}
