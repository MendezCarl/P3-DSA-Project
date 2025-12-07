#include "CampusCompass.h"

using namespace std;

CampusCompass::CampusCompass() {
    // initialize your object
}

std::pair<int, int> parseTime(const std::string& timeStr) {
    std::stringstream ss(timeStr);
    int hour, minute;
    char colon;

    if (ss >> hour >> colon >> minute) {
        return {hour, minute};
    }
    return {0, 0};
}

//make sure to skip the headerline
bool CampusCompass::ParseCSV(const string &edges_filepath, const string &classes_filepath) {
    // return boolean based on whether parsing was successful or not
    std::ifstream edgesFiles(edges_filepath);
    if (!edgesFiles.is_open()) {
        std::cerr << "Failed to open file: " << edges_filepath << std::endl;
        return false;
    }

    std::string line;

    if (!std::getline(edgesFiles,line)) {
        return false;
    }

    while (std::getline(edgesFiles, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string word;

        while (std::getline(ss, word, ',')) {
            size_t start = word.find_first_not_of(" \t\r\n");
            size_t end = word.find_last_not_of(" \t\r\n");

            //removes whitespace
            //https://cplusplus.com/reference/string/string/find_first_not_of/
            if (start != std::string::npos && end != std::string::npos) {
                row.push_back(word.substr(start, end - start + 1));
            } else if (!word.empty()) {
                row.push_back(word);
            } else {
                row.push_back("");
            }
        }

        if (row.size() < 5) {
            continue;
        }

        
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
    edgesFiles.close();

    std::ifstream classesFile(classes_filepath);

    if (!classesFile.is_open()) {
        std::cerr << "Failed to open file: " << classes_filepath << std::endl;
        return false;
    }

    if (!std::getline(classesFile,line)) {
        return false;
    }

    while (std::getline(classesFile, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string word;

        while (std::getline(ss, word, ',')) {
            size_t start = word.find_first_not_of(" \t\r\n");
            size_t end = word.find_last_not_of(" \t\r\n");

            //removes whitespace
            //https://cplusplus.com/reference/string/string/find_first_not_of/
            if (start != std::string::npos && end != std::string::npos) {
                row.push_back(word.substr(start, end - start + 1));
            } else if (!word.empty()) {
                row.push_back(word);
            } else {
                row.push_back("");
            }
        }

        if (row.size() < 4) {
            continue;
        }

        //StartTime = (int hour, int minute)
        //EndTime = (int hour, int minute)
        std::pair<int, int> startTime = parseTime(row[2]);
        std::pair<int, int> endTime   = parseTime(row[3]);

        UniClass newClass(row[0], startTime.first, startTime.second, endTime.first, endTime.second, std::stoi(row[1]));
        classByCode.insert({row[0], newClass});
    }
    classesFile.close();

    return true;
}

bool CampusCompass::ParseLocationsCSV(const std::string &locationsFilepath) {

    std::ifstream file(locationsFilepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << locationsFilepath << std::endl;
        return false;
    }

    std::string line;

    if (!std::getline(file,line)) {
        return false;
    }

    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string word;

        while (std::getline(ss, word, ',')) {
            size_t start = word.find_first_not_of(" \t\r\n");
            size_t end = word.find_last_not_of(" \t\r\n");

            if (start != std::string::npos && end != std::string::npos) {
                row.push_back(word.substr(start, end - start + 1));
            } else if (!word.empty()) {
                row.push_back(word);
            } else {
                row.push_back("");
            }
        }

        if (row.size() < 4) {
            continue;
        }

        //LocationID,Name,Latitude,Longitude
        if (locationByID.count(std::stoi(row[0])) == 0) {
            Location newLocation(std::stoi(row[0]), row[1], std::stof(row[2]), std::stof(row[3]));
            locationByID.insert({std::stoi(row[0]), newLocation});
        }
    }
    file.close();
    return true;
}

void CampusCompass::insert(std::string studentName, int studentId, int origin, int numOfClasses, std::vector<std::string>& classes) {

    try {
        Student newStudent(studentId, studentName, origin, classes);
        students.emplace(newStudent.getID(), newStudent);

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
        } else {
            std::cout << "unsuccessful" << std::endl;
        }
    } catch (const std::exception& e ){
        std::cout << "unsuccessful" << std::endl;
    }
}

void CampusCompass::dropClass(int studentID, std::string classCode) {
    try {
        //check if class exists
        if (classByCode.count(classCode) == 0) {
            std::cout << "unsuccessful: class does not exist" << std::endl;
            return;
        }

        //check if student exists
        auto it = students.find(studentID);
        if (students.end() == it) {
            std::cout << "unsuccessful: student does not exist" << std::endl;
            return;
        }

        Student& student = it->second;
        std::vector<std::string>& studentClass = student.getClasses();

        auto classIt = std::find(studentClass.begin(), studentClass.end(), classCode);
        if (classIt == studentClass.end()) {
            std::cout << "unsuccessful: student not enrolled in class" << std::endl;
            return;
        }
        studentClass.erase(classIt);
        student.getNumOfClasses()--;

        if (studentClass.size() == 0) {
            students.erase(it);
            return;
        }

        std::cout << "successful" << std::endl;
    } catch (const std::exception& e ) {
        std::cout << "unsuccessful" << std::endl;
    }
}

void CampusCompass::replaceClass(int studentID, std::string classCode1, std::string classCode2) {
    try {
        auto it = students.find(studentID);
        if (it == students.end()) {
            std::cout << "unsuccessful: student does not exist" << std::endl;
            return;
        }

        bool replaced = false;
        Student& student = it->second;

        //see if class exists
        std::vector<std::string>& classCodes = student.getClasses();
        for (std::string& classCode : classCodes) {
            if (classCode == classCode1) {
                classCode = classCode2;
                replaced = true;
                break;
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

void CampusCompass::removeClass(const std::string& classCode) {
    try {
        int adjustedCounter = 0;

        //first check if it exists
        auto it = classByCode.find(classCode);
        if (it == classByCode.end()) {
            std::cout << "unsuccessful: does not exist" << std::endl;
            return;
        }

        //access the class to deactivate
        UniClass& c = it->second;
        c.updateActivity(false);

        for (auto& [id, student] : students) {
            std::vector<std::string>& studentClasses = student.getClasses();
            auto it = std::find(studentClasses.begin(), studentClasses.end(), classCode);

            if (it != studentClasses.end()) {
                studentClasses.erase(it);
                student.getNumOfClasses()--;
                adjustedCounter++;
            }
        }

        std::cout << "removed: " << classCode << " # of students: " << adjustedCounter << std::endl;

    } catch (const std::exception& e ) {
        std::cout << "error removing class: " << e.what() << std::endl;
    }
}

void CampusCompass::toggleEdgesClosures(int numberOfClosures, std::vector<int>& edges) {
    try {
        if (edges.size() != static_cast<size_t>(numberOfClosures *2)) {
            for (size_t i = 0; i < edges.size();) {
                int from = edges[i];
                int to = edges[i + 1];
                i+=2;

                auto it = adjList.find(from);
                if (it == adjList.end()) {
                    continue;
                }
                for (auto& edge: it->second) {
                    if (edge.getTo() == to) {
                        if (edge.isEdgeOpen()) {
                            edge.closeEdge();
                        } else {
                            edge.openEdge();
                        }
                        break;
                    }
                }
            }
        }
        std::cout << "successful" << std::endl;
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
                } else{
                    std::cout << "edge is closed" << std::endl;
                }
                return;
            }
        }
    }
    std::cout << "edge DNE" << std::endl;
}

void CampusCompass::isConnected(int origin, int end) {
    if (!adjList.count(origin)) {
        std::cout << "origin does not exist" << std::endl;
        return;
    }

    std::queue<int> q;
    std::set<int> visited;

    q.push(origin);
    visited.insert(origin);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (current == end) {
            std::cout << "successful" << std::endl;
            return;
        }

        if (!adjList.count(current)) {
            std::cout << "unsuccessful" << std::endl;
            return;
        }

        for (auto& edge: adjList[current]) {
            if (!edge.isEdgeOpen()) {
                continue;
            }

            int next = edge.getTo();
            if (!visited.count(next)) {
                visited.insert(next);
                q.push(next);
            }
        }
    }

    std::cout << "unsuccessful" << std::endl;
}

void CampusCompass::printShortestEdges(int id) {
    //shortest walking time from a students residence to each of their classes in the list
    std::map<int, int> distance; //key: locationID, value: how long to reach location

    //check if studentID exists
    auto it = students.find(id);
    if (it == students.end()) {
        std::cout << "unsuccessful" << std::endl;
        return;
    }

    Student& s = it->second;
    int origin = s.getResidence();
    const int inf = 1e9;

    //set default values for distances
    for (auto& [locID, loc]: locationByID) {
        distance[locID] = inf;
    }

    distance[origin] = 0; //sets distance to 0

    std::priority_queue<std::pair<int, int>,std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq; // distance(time), node
    pq.push({0, origin});

    while (!pq.empty()) {
        auto [dist, node] = pq.top();
        pq.pop();

        if (distance[node] < dist) {
            continue;
        }

        if (!adjList.count(node)) {
            continue;
        }
        for (auto& edge: adjList[node]) {
            if (!edge.isEdgeOpen()) {
                continue;
            }

            int to = edge.getTo();
            int weight = edge.getTime();

            if (distance[node] + weight < distance[to]) {
                distance[to] = distance[node] + weight;
                pq.push({distance[to], to});
            }
        }
    }

    std::vector<std::string> classList = s.getClasses();

    if(classList.empty()) {
        std::cout << "no classes enrolled" << std::endl;
        return;
    }

    std::sort(classList.begin(), classList.end());

    for (auto& code: classList) {
        auto it = classByCode.find(code);
        if (it == classByCode.end()) {
            continue;
        }

        UniClass& c = it->second;
        int locID = c.getLocationID();
        int travelTime = -1;

        if (distance.count(locID) && distance[locID] != inf) {
            travelTime = distance[locID];
        }

        std::cout << code << " | Total Time: " << travelTime << std::endl;
    }
}

bool isInteger(std::string& input) {
    if (input.empty()) {
        return false;
    }

    for (char character: input) {
        if (!std::isdigit(character)) {
            return false;
        }
    }

    return true;
}

//classcode will always be 7 characters long
auto isClassCode = [](const std::string& s) -> bool {
    if (s.size() != 7) return false;
    for (int i = 0; i < 3; ++i) {

        //checks if the first three characters are letters
        //From cpp reference https://cplusplus.com/reference/cctype/isalpha/
        if (!std::isalpha(static_cast<unsigned char>(s[i]))) {
            return false;
        }
    }
    for (int i = 3; i < 7; ++i) {
        if (!std::isdigit(static_cast<unsigned char>(s[i]))) {
            return false;
        }
    }
    return true;
};

bool isStudentID(std::string& input) {
    if (input.size() != 8) {
        return false;
    }

    for (size_t i = 0; i < input.size(); i++) {
        if (!std::isdigit(input[i])) {
            return false;
        }
    }

    return true;
}

bool CampusCompass::ParseCommand(const std::string &command) {
    std::stringstream ss(command);
    std::vector<std::string> input;
    std::string word;

    while (ss >> word) {
        input.push_back(word);
    }

    if (input.empty()) {
        return false;
    }

    const std::string& cmd = input[0];

    if (cmd == "insert") {
        if (input.size() < 5) {
            return false;
        }

        std::string name = input[1];

        if (!isInteger(input[2]) || !isInteger(input[3]) || !isInteger(input[4])) {
            return false;
        }

        int studentId   = std::stoi(input[2]);
        int origin      = std::stoi(input[3]);
        int numOfClasses = std::stoi(input[4]);

        if (numOfClasses < 0) {
            return false;
        }

        if (static_cast<int>(input.size()) != 5 + numOfClasses) {
            return false;
        }

        std::vector<std::string> classCodes;
        for (std::size_t i = 5; i < input.size(); ++i) {
            if (!isClassCode(input[i])) {
                return false;
            }
            classCodes.push_back(input[i]);
        }

        insert(name, studentId, origin, numOfClasses, classCodes);
        return true;
    }

    if (cmd == "remove") {
        if (input.size() != 2) {
            return false;
        }
        if (!isInteger(input[1])) {
            return false;
        }
        int studentId = std::stoi(input[1]);
        remove(studentId);
        return true;
    }

    if (cmd == "dropClass") {
        if (input.size() != 3) {
            return false;
        }
        if (!isInteger(input[1]) || !isClassCode(input[2])) {
            return false;
        }
        int studentId = std::stoi(input[1]);
        const std::string& classCode = input[2];
        dropClass(studentId, classCode);
        return true;
    }

    if (cmd == "replaceClass") {
        if (input.size() != 4) {
            return false;
        }
        if (!isInteger(input[1]) ||
            !isClassCode(input[2]) ||
            !isClassCode(input[3])) {
            return false;
        }

        int studentId = std::stoi(input[1]);
        const std::string& oldCode = input[2];
        const std::string& newCode = input[3];

        replaceClass(studentId, oldCode, newCode);
        return true;
    }

    if (cmd == "removeClass") {
        if (input.size() != 2) {
            return false;
        }
        if (!isClassCode(input[1])) {
            return false;
        }
        removeClass(input[1]);
        return true;
    }

    //for every 1 closure there requires 2 nodes
    if (cmd == "toggleEdgesClosures") {
        if (input.size() < 2) {
            return false;
        }

        if (!isInteger(input[1])) {
            return false;
        }

        int numberOfClosures = std::stoi(input[1]);
        if (numberOfClosures <= 0) {
            return false;
        }

        int expectedSize = 2 + numberOfClosures * 2;
        if (static_cast<int>(input.size()) != expectedSize) {
            return false;
        }

        std::vector<int> edges;
        edges.reserve(numberOfClosures * 2);

        for (int i = 2; i < static_cast<int>(input.size()); ++i) {
            if (!isInteger(input[i])) {
                return false;
            }
            edges.push_back(std::stoi(input[i]));
        }

        toggleEdgesClosures(numberOfClosures, edges);
        return true;
    }

    if (cmd == "checkEdgeStatus") {
        if (input.size() != 3) {
            return false;
        }
        if (!isInteger(input[1]) || !isInteger(input[2])) {
            return false;
        }
        int origin = std::stoi(input[1]);
        int end    = std::stoi(input[2]);
        checkEdgeStatus(origin, end);
        return true;
    }

    if (cmd == "isConnected") {
        if (input.size() != 3) {
            return false;
        }
        if (!isInteger(input[1]) || !isInteger(input[2])) {
            return false;
        }
        int origin = std::stoi(input[1]);
        int end    = std::stoi(input[2]);
        isConnected(origin, end);
        return true;
    }


    if (cmd == "printShortestEdges") {
        if (input.size() != 2) {
            return false;
        }
        if (!isInteger(input[1])) {
            return false;
        }
        int studentId = std::stoi(input[1]);
        printShortestEdges(studentId);
        return true;
    }

    return false;
}

//made to check if parsing classes was correct
void CampusCompass::printAllClasses() {
    std::cout << "\nList of classes" << std::endl;
    std::cout << "Total classes: " << classByCode.size() << std::endl;
    
    for (auto& [code, uniClass] : classByCode) {
        std::cout << "Class Code: " << code 
                  << " | LocationID: " << uniClass.getLocationID() 
                  << std::endl;
    }
    std::cout << "============================\n" << std::endl;
}
