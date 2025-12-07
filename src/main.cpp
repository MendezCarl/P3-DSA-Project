#include <iostream>

#include "CampusCompass.h"

using namespace std;

int main() {
    try {
        // initialize your main project object
        CampusCompass compass;

        // ingest CSV data
        cout << "Loading CSV files..." << endl;
        compass.ParseCSV("./data/edges.csv", "./data/classes.csv");
        compass.ParseLocationsCSV("./data/locations.csv");
        cout << "CSV files loaded successfully." << endl;

        // compass.printAllClasses();

        // the below is example code for parsing commandline input
        int no_of_lines;
        string input;
        
        cout << "Enter number of commands: ";
        getline(cin, input);
        cout << "Input received: '" << input << "'" << endl;
        
        no_of_lines = stoi(input);
        
        for (int i = 0; i < no_of_lines; i++) {
            string command;
            getline(cin, command);
            cout << "Command " << (i+1) << ": '" << command << "'" << endl;

            // parse your commands however you see fit
            compass.ParseCommand(command);
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}
