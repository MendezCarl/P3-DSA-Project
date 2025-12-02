#include "CampusCompass.h"

#include <string>

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

        //iterating through edges file line
        //[from, to, fromName, toName, time]
        edges[std::stoi(row[0])][std::stoi(row[1])] = std::stoi(row[4]);
        // locations[std::stoi(row[0])] = row[2];
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
        classes[row[0]] = {row[1], row[2], row[3]};
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

        //[classCode, LocationID, startTime, endTime]
        classes[row[0]] = {row[1], row[2], row[3]};
    }
    file.close();
    return true;
}

template<typename... Classes>
void CampusCompass::insert(std::string studentName, int studentId, int origin, int numOfClasses, Classes... classes) {

    try {
        Student student;
        student.createStudent(studentId, studentName, numOfClasses, classes, origin);
        students.push_back(student);

        std::cout << "successful" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "unsuccessful" << std::endl;
    }

}

void CampusCompass::remove(int studentID) {
    try {
        std::vector<Student>::iterator it = students.begin();
        while (it != students.end()) {
            if ((*it).getID() == studentID){
                it = students.erase(it);
            }
        }
        std::cout << "successful" << std::endl;
    } catch (const std::exception& e ){
        std::cout << "unsuccessful" << std::endl;
    }
}

void CampusCompass::dropClass(int studentID, std::string classCode) {
    try {
        //get student
        Student student;
        for (int i = 0; i < students.size(); i++) {
            if (students[i].getID() == studentID)
            {
                student = students[i];
                std::cout << "student exists" << std::endl;
            }
        }

        if (student.getNumOfClasses() > 1) {
            //check classes
            std::vector<std::string> classes = student.getClasses();
            for (int i = 0; i < classes.size(); i++) {

            }
        } else {
            remove(student.getID());
        }

    } catch (const std::exception& e ) {
        std::cout << "unsuccessful" << std::endl;
    }
}

void CampusCompass::replaceClass(int studentID, std::string classCode1, std::string classCode2) {
    try {
        bool replaced = false;

        //find student
        Student student;
        for (Student& i : students) {
            if (i.getID() == studentID) {
                student = i;
                std::cout << "student exists" << std::endl;
            } else {
                std::cout << "unsuccessful" << std::endl;
                return;
            }
        }

        //see if class exists
        std::vector<std::string> classCodes = student.getClasses();
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
void CampusCompass::removeClass(std::string classCode) {
    try {
        int adjustedCounter = 0;

        for (Student& student : students) {
            std::vector<std::string> classCodes = student.getClasses();
            for (auto& callCode : classCodes) {
                if (classCode.empty()) {
                    std::cout << "Student has no classes :" << student.getName() << std::endl;
                } else {
                    if (callCode == classCode) {
                        classCodes.erase(classCodes.begin());
                        int numOfClasses = student.getNumOfClasses();
                        numOfClasses--;

                        adjustedCounter++;
                    }
                }
            }
        }

        std::cout << "removed class: " << classCode << "from "<< adjustedCounter << "Students." <<std::endl;
    } catch (const std::exception& e ) {
        std::cout << "error removing class: " << e.what() << std::endl;
    }
}


bool CampusCompass::ParseCommand(const string &command) {
    // do whatever regex you need to parse validity
    // hint: return a boolean for validation when testing. For example:
    bool is_valid = true; // replace with your actual validity checking

    return is_valid;
}
