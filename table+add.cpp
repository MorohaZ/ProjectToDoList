#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;

//prototype functions
void addTodo(const string& filename, const vector<string>& entry);
void getUserInput();
vector<string> tokens(string text,string delimiter);
void TodoList_table(vector<map<string,string>> data, vector<string> keys);

int main()
{
    map<string,string> myMap;
    vector<map<string,string>> data; //เก็บ myMap แต่ละแถวไว้ใน data
    string textline;
    ifstream read;

    read.open("data.csv");
    getline(read,textline); //บรรทัดแรก (หัวข้อประเภท)
    vector<string> keys = tokens(textline, ","); //delimiter = ","
    vector<string> row;
    while (getline(read, textline)) { //อ่านทีละแถวจนหมดไฟล์
        row = tokens(textline, ",");  //delimiter = ","
        myMap.clear(); //เคลียร์mapก่อนpair
        for (int i = 0; i < keys.size(); i++) { //ทำจนครบทุกคอลัมน์
            myMap.insert(pair<string, string>(keys.at(i),row[i])); //ใส่ค่า row[i] ลงคู่กับ keys.at(i) ตามคอลัมน์
        }
        data.push_back(myMap);
    }
    TodoList_table(data,keys);
    getUserInput();
    
}

void TodoList_table(vector<map<string, string>> data,vector<string> keys) { //data เก็บ myMap ทุกแถวไว้, keys เก็บหัวข้อของทุกประเภทไว้อยู่
    int data_count = data.size(); //จำนวนแถวข้อมูลทั้งหมด(จำนวนmyMap)
    int col_count = keys.size(); //จำนวนคอลัมน์ข้อมูล(จำนวนประเภทข้อมูล)
    vector<int> col_sizes(col_count);
    for (int i = 0; i < col_count; i++) { //หา column size ที่มากที่สุด ของแต่ละคอลัมน์
        col_sizes[i] = keys.at(i).length(); //ความยาวของข้อมูลที่ i
        for (int j = 0; j < data_count; j++) {
            if (col_sizes[i] < data[j][keys.at(i)].length()) {
                col_sizes[i] = data[j][keys.at(i)].length(); //ถ้ามากกว่าข้อมูลที่ i ให้แทนค่านั้นเป็น column size
            }
        }
    }
    //ขอบตารางบน----
    for (int i = 0; i < col_count; i++) {
            std::cout << setw(col_sizes[i]) << setfill('-') << "" << setfill(' ') << "-";
        } 
    std::cout << endl;
    //ประเภทข้อมูล(ข้อมูลแถวแรก)
    for (int i = 0; i < col_count; i++) {
        std::cout  << setw(col_sizes[i]) << left << keys.at(i)  << "|";
    }
    std::cout << endl;

    //ขอบตารางและข้อมูลในตาราง --|--
    for (int i = 0; i < data_count; i++) {
        for (int j = 0; j < col_count; j++) {
            std::cout << setw(col_sizes[j]) << setfill('-') << "" << setfill(' ') << "|";
        }
        std::cout << endl;
        for (int j = 0; j < col_count; j++) {
            std::cout << setw(col_sizes[j]) << left << data[i][keys.at(j)] << "|";
        }
        std::cout << endl; 
    }
    //ขอบตารางล่าง----
    for (int i = 0; i < col_count; i++) {
            std::cout << setw(col_sizes[i]) << setfill('-') << "" << setfill(' ') << "-";
        } 
    std::cout << endl;
}

//["ID", "All To Dos", "Status", "Category", "Due Date", "Remarks", "!"]
vector<string> tokens(string text,string delimiter) { //แยกข้อมูลตามตัวคั่น (delimiter)
    vector<string> key;
    size_t found;
    string token;
    while ((found = text.find(delimiter)) != string::npos) { //หาจนเจอ delimiter(",")
        token = text.substr(0,found); //ดึงtextตำแหน่ง0ถึงตำแหน่งที่พบ","
        key.push_back(token); //นำข้อมูลที่ดึงมาใส่ไปใน key
        text.erase(0,found + delimiter.length()); //ลบข้อมูลกับ,ที่เจอ
    }
    key.push_back(text); //ข้อมูลสุดท้าย
    return key;
}

void addTodo(const string& filename, const vector<string>& entry) {
    // Open the file in append mode
    ofstream file(filename, ios::app);
    // Write the entry to the file
    for (const auto& field : entry) {
        file << field << ",";
    }
    file << endl;
    file.close();

    std::cout << "New entry added to " << filename << " successfully." << endl;
}

void getUserInput() {  
    vector<string> newEntry;

    // Get user input for each field
    string input;
    std::cout << "Enter ID: ";
    getline(cin, input);
    newEntry.push_back(input);

    std::cout << "Enter Todo: ";
    getline(cin, input);
    newEntry.push_back(input);

    input = "undone"; //status default is "undone"
    newEntry.push_back(input);

    std::cout << "Add a Category? (y/n) : ";
    getline(cin, input);
    while(input!="y" && input!="Y" && input!="n" && input!="N"){
        cout << "Please enter only 'y' for yes or 'n' for no. (y/n) : ";
        getline(cin, input);
    }
    if(input=="y" || input == "Y"){
    std::cout << "Enter Category: ";
    getline(cin, input);
    newEntry.push_back(input);
    }else if(input=="n" || input == "N"){
        input = "No category";
        newEntry.push_back(input);
    }

    std::cout << "Add a Due Date? (y/n) : ";
    getline(cin, input);
    while(input!="y" && input!="Y" && input!="n" && input!="N"){
        cout << "Please enter only 'y' for yes or 'n' for no. (y/n) : ";
        getline(cin, input);
    }
    if(input=="y" || input == "Y"){
    std::cout << "Ender a Due Date : ";
    getline(cin, input);
    newEntry.push_back(input);
    }else if(input=="n" || input == "N"){
        input = "No date";
        newEntry.push_back(input);
    }

    std::cout << "Add a Remarks? (y/n) : ";
    getline(cin, input);
    while(input!="y" && input!="Y" && input!="n" && input!="N"){
        cout << "Please enter only 'y' for yes or 'n' for no. (y/n) : ";
        getline(cin, input);
    }
    if(input=="y" || input == "Y"){
    std::cout << "Enter Remarks: ";
    getline(cin, input);
    newEntry.push_back(input);
    }else if(input=="n" || input == "N"){
        input = "None";
        newEntry.push_back(input);
    }
    
    std::cout << "Mark as important? (y/n) : ";
    getline(cin, input);
    while(input!="y" && input!="Y" && input!="n" && input!="N"){
        cout << "Please enter only 'y' for yes or 'n' for no. (y/n) : ";
        getline(cin, input);
    }
    if(input=="y" || input == "Y"){
        input = "!";
        newEntry.push_back(input);
    }else if(input=="n" || input == "N"){
        input = " ";
        newEntry.push_back(input);
    }

    // Add the new entry to the data.csv file
    addTodo("data.csv", newEntry);

}