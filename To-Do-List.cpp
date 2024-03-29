#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "menu.h"
#include "viewtodo.h"
#include "addTodo.h"
#include "deleteTodo.h"
#include "table.h"
#include "mark_as_completed.h"
#include "modify.h"

using namespace std;
void delay(int sec);

int main() {
    map<string, string> myMap;
    vector<map<string, string>> data; //เก็บ myMap แต่ละแถวไว้ใน data
    string textline;
    ifstream read;

    read.open("data.csv");
    getline(read, textline); //บรรทัดแรก (หัวข้อประเภท)
    vector<string> keys = tokens(textline, ","); //แยกตามหัวข้อ ใช้delimiter = ","
    vector<string> row;
    while (getline(read, textline)) { //อ่านทีละแถวจนหมดไฟล์
        row = tokens(textline, ",");  //delimiter = ","
        myMap.clear(); //เคลียร์mapก่อนpair
        for (size_t i = 0; i < keys.size(); i++) { //ทำจนครบทุกคอลัมน์
            myMap[keys.at(i)] = row[i]; //ใส่ค่า row[i] ลงคู่กับ keys.at(i) ตามคอลัมน์
        }
        data.push_back(myMap); //ใส่ทุกคู่ลงใน data
    }
    int choice;
    bool continueExecution = true;
    do {
        SortByColumn5(data);
        stablePartitionByColumn7(data);
        displayMenu();
        if (continueExecution) {
            cin >> choice;
            cin.clear();
            cin.ignore();
        }
        int continueChoice;       
        switch(choice) {
            case 1:
                system("cls");
                cout << "\033[1;33mYou chose View all To-dos" << endl << "\033[1;33m" ;
                findTodoUndone(data, keys);
                   do{ cout << "\033[1;33mWould you like to:\n1. Go to Menu\n2. End\nYour choice: ";
                    cout << "\033[1;37m" ;
                    cin >> continueChoice;
                    cin.clear();
                    cin.ignore();
                    if (continueChoice == 1) {
                        continueExecution = true;
                        choice = 0; // Reset choice to force re-entry to the switch statement
                    }
                    else if (continueChoice == 2)
                        continueExecution = false;
                    else {
                        cout << "\033[1;31mInvalid choice. Again please..." << endl;
                        continueExecution = false;
                    }
                    }while (continueChoice != 1 && continueChoice != 2);
                break;
            
            case 2:
                system("cls");
                cout << "\033[1;33mYou chose View completed To-do" << endl;
                findTodoDone(data, keys);
                   do{
                    cout << "\033[1;33mWould you like to:\n1. Go to Menu\n2. End\nYour choice: ";
                    cout << "\033[1;37m" ;
                    cin >> continueChoice;
                    cin.clear();
                    cin.ignore();
                    if (continueChoice == 1) {
                        continueExecution = true;
                        choice = 0; // Reset choice to force re-entry to the switch statement
                    }
                    else if (continueChoice == 2)
                        continueExecution = false;
                    else {
                        cout << "\033[1;31mInvalid choice. Again please..." << endl;
                        continueExecution = false;
                    }
                    }while (continueChoice != 1 && continueChoice != 2);
                break;
            
            case 3:
                do{
                system("cls");
                cout << "\033[1;33mYou chose View all To-dos from category" << endl;
                displayAvailableCategories(data);
                findTodoByCategory(data, keys, selectCategory(data));
                    do{
                    cout << "\033[1;33mWould you like to:\n1. Go to Menu\n2. End\n3. Do Again\nYour choice: ";
                    cout << "\033[1;37m" ;
                    cin >> continueChoice;
                    cin.clear();
                    cin.ignore();
                    if (continueChoice == 1) {
                        continueExecution = true;
                        choice = 0; // Reset choice to force re-entry to the switch statement
                    }
                    else if (continueChoice == 2)
                        continueExecution = false;
                    else {
                        cout << "\033[1;31mInvalid choice. Again please..." << endl;
                        continueExecution = false;
                    }
                    }while (continueChoice != 1 && continueChoice != 2 && continueChoice != 3);
                }while (continueChoice == 3);
                break;

            case 4:
                do{
                system("cls");
                cout << "\033[1;33mYou chose Add a new To-do" << endl;
                getUserInput(data,keys);
                do{
                    cout << "\033[1;33mWould you like to:\n1. Go to Menu\n2. End\n3. Do Again\nYour choice: ";
                    cout << "\033[1;37m" ;
                    cin >> continueChoice;
                    cin.clear();
                    cin.ignore();
                    if (continueChoice == 1) {
                        continueExecution = true;
                        choice = 0; // Reset choice to force re-entry to the switch statement
                    }
                    else if (continueChoice == 2)
                        continueExecution = false;
                    else {
                        cout << "\033[1;31mInvalid choice. Again please..." << endl;
                        continueExecution = false;
                    }
                    }while (continueChoice != 1 && continueChoice != 2 && continueChoice != 3);
                }while (continueChoice == 3); 
                break;

            case 5:
                do{
                system("cls");
                cout << "\033[1;33mYou chose Delete a To-do" << endl;
                TodoList_table(data,keys);
                deleteTodo("data.csv", data, keys, selectIDToDelete(data));
                TodoList_table(data,keys);
                do {cout << "\033[1;33mWould you like to:\n1. Go to Menu\n2. End\n3. Do Again\nYour choice: ";
                    cout << "\033[1;37m" ;
                    cin >> continueChoice;
                    cin.clear();
                    cin.ignore();
                    if (continueChoice == 1) {
                        continueExecution = true;
                        choice = 0; // Reset choice to force re-entry to the switch statement
                    }
                    else if (continueChoice == 2)
                        continueExecution = false;
                    else {
                        cout << "\033[1;31mInvalid choice. Again please..." << endl;
                        continueExecution = false;
                    }
                }while (continueChoice != 1 && continueChoice != 2 && continueChoice != 3);
                }while (continueChoice == 3);
                break;

            case 6:
                do{
                system("cls");
                cout << "\033[1;33mYou chose Mark as completed" << endl;
                findTodoUndone(data, keys);
                updateStatus(data, selectIDToMark(data), keys);
                    do{cout << "\033[1;33mWould you like to:\n1. Go to Menu\n2. End\n3. Do Again\nYour choice: ";
                    cout << "\033[1;37m" ;
                    cin >> continueChoice;
                    cin.clear();
                    cin.ignore();
                    if (continueChoice == 1) {
                        continueExecution = true;
                        choice = 0; // Reset choice to force re-entry to the switch statement
                    }
                    else if (continueChoice == 2)
                        continueExecution = false;
                    else {
                        cout << "\033[1;31mInvalid choice. Again please..." << endl;
                        continueExecution = false;
                    }
                }while (continueChoice != 1 && continueChoice != 2 && continueChoice != 3);
                }while (continueChoice == 3);
                break;

            case 7:
                do{
                system("cls");
                std::cout << "\033[1;33mYou chose Modify a To-do" << endl;
                TodoList_table(data,keys);
                modifyTodo(data, keys);
                    do{cout << "\033[1;33mWould you like to:\n1. Go to Menu\n2. End\n3. Do Again\nYour choice: ";
                    cout << "\033[1;37m" ;
                    cin >> continueChoice;
                    cin.clear();
                    cin.ignore();
                    if (continueChoice == 1) {
                        continueExecution = true;
                        choice = 0; // Reset choice to force re-entry to the switch statement
                    }
                    else if (continueChoice == 2)
                        continueExecution = false;
                    else {
                        cout << "\033[1;31mInvalid choice. Again please..." << endl;
                        continueExecution = false;
                    }
                    }while (continueChoice != 1 && continueChoice != 2 && continueChoice != 3);
                  }while (continueChoice == 3);
                break;
                
            case 8:
                system("cls");
                std::cout << "\033[1;31mExiting..." << endl;
                delay(1);
                exit(EXIT_SUCCESS);
                break;
            default:
                cout << "\033[1;31mInvalid choice. Please try again." << endl;
                delay(1);
                continue;
        }
    } while(continueExecution);

    return 0;
}

void delay(int seconds) {
    clock_t start_time = clock(); // Get the initial clock time
    while (clock() < start_time + seconds * CLOCKS_PER_SEC) {
        // Loop until the current clock time exceeds the specified delay
    }
}