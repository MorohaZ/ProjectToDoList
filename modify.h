#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;

// Function prototypes
void modifyTodo(vector<map<string, string>>& data, const vector<string>& keys);
string selectIDToModify(const vector<map<string, string>>& data);

void modifyTodo(vector<map<string, string>>& data, const vector<string>& keys) {
    string inputId = selectIDToModify(data);
    string input;
    // Find the entry with the given ID
    auto entryToUpdate = find_if(data.begin(), data.end(), [&inputId](const map<string, string>& entry) {
        return entry.at("ID") == inputId;
    });

    if (entryToUpdate != data.end()) {
        // Get user input for each field
        map<string, string> newEntry;
        std::cout << "\033[1;32mEnter ID: ";
        getline(cin, newEntry["ID"]);

        cout << "\033[1;32mEnter Todo: ";
        getline(cin, newEntry["Todo"]);

        cout << "\033[1;32mStatus is done? (y/n): ";
        getline(cin, input);
        newEntry["Status"] = (input == "y" || input == "Y") ? "done" : "undone";

        cout << "\033[1;32mAdd a Category? (y/n): ";
        getline(cin, input);
        if (input == "y" || input == "Y") {
            cout << "\033[1;32mEnter Category: ";
            getline(cin, newEntry["Category"]);
        } else {
            newEntry["Category"] = "No category";
        }

        cout << "\033[1;32mAdd a Due Date? (y/n): ";
        getline(cin, input);
        if (input == "y" || input == "Y") {
            cout << "\033[1;32mEnter Due Date (y/m/d): ";
            getline(cin, newEntry["Due Date"]);
        } else {
            newEntry["Due Date"] = "No date";
        }

        cout << "\033[1;32mAdd Remarks? (y/n): ";
        getline(cin, input);
        if (input == "y" || input == "Y") {
            cout << "\033[1;32mEnter Remarks: ";
            getline(cin, newEntry["Remarks"]);
        } else {
            newEntry["Remarks"] = "None";
        }

        cout << "\033[1;32mMark as important? (y/n): ";
        getline(cin, input);
        newEntry["Important"] = (input == "y" || input == "Y") ? "!" : " ";

        // Replace old entry with new entry
        *entryToUpdate = newEntry;

        // Write updated data to data.csv file
        ofstream file("data.csv");
        if (file.is_open()) {
            // Write column headers
            for (size_t i = 0; i < keys.size(); ++i) {
                file << keys[i];
                if (i != keys.size() - 1) file << ",";
                else file << "\n";
            }
            // Write each row of data
            for (const auto& row : data) {
                for (size_t i = 0; i < keys.size(); ++i) {
                    file << row.at(keys[i]);
                    if (i != keys.size() - 1) file << ",";
                    else file << "\n";
                }
            }
            file.close();
            cout << "\033[1;32mData edited successfully and saved to data.csv!" << endl;
        } else {
            cout << "\033[1;31mUnable to open file for writing!" << endl;
        }
    } else {
        cout << "\033[1;31mNo entry found with ID " << inputId << endl;
    }
}

string selectIDToModify(const vector<map<string, string>>& data) {
    string findIDTomodify;
    bool idFound = false;
    do {
        cout << "\033[1;32mEnter ID of the To-Do entry you want to modify: ";
        getline(cin, findIDTomodify);
         if (findIDTomodify.empty()) {
            cout << "\033[1;32mPlease enter an exist ID." << endl;
            continue;
        }
        idFound = false;
        for (const auto& todo : data) {
            if (todo.at("ID") == findIDTomodify) {
                idFound = true;
                break;
            }
        }
        if (!idFound) {
            cout << "\033[1;31mThis ID was not found: " << findIDTomodify << endl;
        }
    } while (!idFound);


    return findIDTomodify;
}