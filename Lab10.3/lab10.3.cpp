#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <iomanip>
#include <sstream>

using namespace std;

struct FriendInfo {
    string name;
    string phone;
    int birthday[3];
};

void AddFriend(const string& filename);
void SearchFriend(const string& filename, const string& searchName);
void ShowAllFriends(const string& filename);
bool ValidateDate(int day, int month, int year);

int main() {
    string filename;
    cout << "Enter filename: ";
    getline(cin, filename);

    int choice;
    do {
        cout << "Choose an action:" << endl;
        cout << "[1] Add a person" << endl;
        cout << "[2] Search for a person" << endl;
        cout << "[3] Show all friends" << endl;
        cout << "[0] Exit the program" << endl;
        cout << "Enter: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
        }


        switch (choice) {
        case 1:
            AddFriend(filename);
            break;
        case 2: {
            string searchName;
            cout << "Enter the surname for search: ";
            cin.ignore();
            getline(cin, searchName);
            SearchFriend(filename, searchName);
            break;
        }
        case 3:
            ShowAllFriends(filename);
            break;
        case 0:
            cout << "Exiting the program...\n";
            break;
        default:
            cout << "Invalid selection, please try again.\n";
        }
    } while (choice != 0);

    return 0;
}

void AddFriend(const string& filename) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return;
    }

    FriendInfo friendInfo;
    cout << "Enter name and surname: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, friendInfo.name);
    cout << "Enter phone number: ";
    getline(cin, friendInfo.phone);
    cout << "Enter birth date (day month year): ";
    cin >> friendInfo.birthday[0] >> friendInfo.birthday[1] >> friendInfo.birthday[2];

    if (!ValidateDate(friendInfo.birthday[0], friendInfo.birthday[1], friendInfo.birthday[2])) {
        cerr << "Error: invalid birth date." << endl;
        return;
    }

    file << friendInfo.name << ',' << friendInfo.phone << ','
        << friendInfo.birthday[0] << ' ' << friendInfo.birthday[1] << ' ' << friendInfo.birthday[2] << '\n';

    file.close();
    cout << "Data added." << endl;
}

void SearchFriend(const string& filename, const string& surname) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        size_t commaPos1 = line.find(',');
        string fullName = line.substr(0, commaPos1);
        string nameSurname = fullName.substr(0, fullName.find(' '));
        if (nameSurname == surname) {
            string phone = line.substr(commaPos1 + 1, line.find(',', commaPos1 + 1) - commaPos1 - 1);
            string birthdayStr = line.substr(line.rfind(',') + 1);
            cout << "Full Name: " << fullName << ", Phone: " << phone << ", Birthday: " << birthdayStr << endl;
            found = true;
            break;
        }
    }
    file.close();

    if (!found) {
        cout << "Friend with the surname '" << surname << "' not found." << endl;
    }
}

void ShowAllFriends(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return;
    }

    cout << "============================================================================" << endl;
    cout << "| ¹   | Surname and Name |     Phone     |  Day  | Month |  Year  |" << endl;
    cout << "============================================================================" << endl;

    string line;
    int lineNumber = 0;
    while (getline(file, line)) {
        size_t commaPos1 = line.find(',');
        size_t commaPos2 = line.find(',', commaPos1 + 1);
        string name = line.substr(0, commaPos1);
        string phone = line.substr(commaPos1 + 1, commaPos2 - commaPos1 - 1);
        string birthdayStr = line.substr(commaPos2 + 1);

        stringstream birthdaySS(birthdayStr);
        int day, month, year;
        birthdaySS >> day >> month >> year;

        cout << "|" << setw(4) << right << ++lineNumber << " ";
        cout << "|" << setw(20) << left << name;
        cout << "|" << setw(15) << left << phone;
        cout << "|" << setw(7) << right << day;
        cout << "|" << setw(7) << right << month;
        cout << "|" << setw(8) << right << year << "|" << endl;
    }

    cout << "============================================================================" << endl << endl;
    file.close();
}

bool ValidateDate(int day, int month, int year) {
    if (year < 1900 || year > 2023) return false;
    if (month < 1 || month > 12) return false;

    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
        daysInMonth[1] = 29;

    if (day < 1 || day > daysInMonth[month - 1]) return false;

    return true;
}