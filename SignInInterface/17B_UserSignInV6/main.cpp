/*
 * File:   main.cpp
 * Author: Josh Carlito
 *
 * Created on March 16, 2023, 4:36 PM
 * Purpose: Create a userInfo struct to store user information for the future
 *          projects.
 * Version: 6, Don't allow user name duplicates
 */

// C++ Libraries
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

const unsigned char USERNAME_LENGTH = 13;
const unsigned char PASSWORD_LENGTH = 13;

struct UserInfo {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
};

void getUsername(UserInfo &user);
void getPassword(UserInfo &user);
void getAdminKey(const int &adminKey);

void writeText(ofstream &textOutputFile, UserInfo user, char &userInput);
void writeBinary(fstream &binaryOutputFile, UserInfo user);
void readBinary(fstream &binaryInputFile, UserInfo &user, int record);
bool searchBinary(fstream &binaryInputFile, UserInfo &user);
bool duplicateUsername(fstream &binaryInputFile, UserInfo &user);

void displayUserInfo(UserInfo user);
void displayMenu(char &userInput);
void displayError();
void displayOptions();
void toLowercase(char &userInput);

int main(int argc, char **argv) {
    // Set random number seed
    srand(static_cast<unsigned int> (time(0)));

    const int adminKey = 1234;

    UserInfo test;
    ofstream textUserOutputFile;
    ofstream textAdminOutputFile;
    fstream binaryUserFile;
    fstream binaryAdminFile;
    char userInput;
    bool exitSignIn;

    exitSignIn = false;

    textUserOutputFile.open("UserInfo.txt", ios::app);
    textAdminOutputFile.open("AdminInfo.txt", ios::app);
    binaryUserFile.open("UserInfo.bin", ios::in | ios::app | ios::binary);
    binaryAdminFile.open("AdminInfo.bin", ios::in | ios::app | ios::binary);

    displayMenu(userInput);
    while (!exitSignIn) {
        if (userInput == 'u') {
            cout << "Register for a Normal User account" << endl << endl;
            getUsername(test);
            while (duplicateUsername(binaryUserFile, test) ||
                    duplicateUsername(binaryAdminFile, test)) {
                cout << endl;
                cout << "Username already in use!" << endl;
                getUsername(test);
            }
            getPassword(test);
            writeText(textUserOutputFile, test, userInput);
            writeBinary(binaryUserFile, test);
            exitSignIn = true;
        } else if (userInput == 'a') {
            cout << "Register for Admin account" << endl << endl;
            getAdminKey(adminKey);
            getUsername(test);
            while (duplicateUsername(binaryAdminFile, test) ||
                    duplicateUsername(binaryUserFile, test)) {
                cout << endl;
                cout << "Username already in use!" << endl;
                getUsername(test);
            }
            getPassword(test);
            writeText(textAdminOutputFile, test, userInput);
            writeBinary(binaryAdminFile, test);
            exitSignIn = true;
        } else {
            cout << "Sign-In" << endl << endl;
            getUsername(test);
            getPassword(test);
            exitSignIn = searchBinary(binaryUserFile, test);
            if (exitSignIn == false)
                exitSignIn = searchBinary(binaryAdminFile, test);

            if (exitSignIn == false) {
                displayError();
                cin.get(userInput);
                cin.ignore();
                cout << endl;
                if (userInput == 'y' || userInput == 'Y') 
                    userInput = 'x';
                else {
                    displayOptions();
                    cin.get(userInput);
                    cin.ignore();
                    cout << endl;
                }
            }
        }
    }

    displayUserInfo(test);

    textUserOutputFile.close();
    textAdminOutputFile.close();
    binaryUserFile.close();
    binaryAdminFile.close();

    return 0;
}

void getUsername(UserInfo &user) {
    cout << "Enter your username (12 characters max): ";
    cin.getline(user.username, USERNAME_LENGTH);

    while (cin.fail()) {
        cin.clear();
        cin.ignore(USERNAME_LENGTH, '\n');
        cout << endl;
        cout << "Invalid username (too many characters)!" << endl;
        cout << "Enter your username (12 characters max): ";
        cin.getline(user.username, USERNAME_LENGTH);
    }
    user.username[USERNAME_LENGTH - 1] = '\0';
}

void getPassword(UserInfo &user) {
    cout << "Enter your password (12 characters max): ";
    cin.getline(user.password, PASSWORD_LENGTH);

    while (cin.fail()) {
        cin.clear();
        cin.ignore(PASSWORD_LENGTH, '\n');
        cout << endl;
        cout << "Invalid password (too many characters)!" << endl;
        cout << "Enter your password (12 characters max): ";
        cin.getline(user.password, PASSWORD_LENGTH);
    }
    user.password[PASSWORD_LENGTH - 1] = '\0';
}

void displayUserInfo(UserInfo user) {
    cout << "Username: " << user.username << endl;
    cout << "Password: " << user.password << endl;
}

void writeText(ofstream &textOutputFile, UserInfo user, char &userInput) {
    if (textOutputFile.tellp() == 0 && userInput == 'u') {
        textOutputFile << endl;
        textOutputFile << "User Information Records:" << endl;
        textOutputFile << endl;
        textOutputFile << left << setw(25);
        textOutputFile << "Username";
        textOutputFile << "Password" << endl;
    } else if (textOutputFile.tellp() == 0 && userInput == 'a') {
        textOutputFile << endl;
        textOutputFile << "Admin Information Records:" << endl;
        textOutputFile << endl;
        textOutputFile << left << setw(25);
        textOutputFile << "Username";
        textOutputFile << "Password" << endl;
    }
    textOutputFile << left << setw(25);
    textOutputFile << user.username << user.password << endl;
    textOutputFile.clear();
}

void writeBinary(fstream &binaryOutputFile, UserInfo user) {
    binaryOutputFile.write(&user.username[0], USERNAME_LENGTH);
    binaryOutputFile.write(&user.password[0], PASSWORD_LENGTH);
    binaryOutputFile.clear();
}

void readBinary(fstream &binaryInputFile, UserInfo &user, int record) {
    binaryInputFile.seekg(record * sizeof (UserInfo), ios::beg);

    binaryInputFile.read(&user.username[0], USERNAME_LENGTH);
    binaryInputFile.read(&user.password[0], PASSWORD_LENGTH);
}

void displayMenu(char &userInput) {
    cout << "--------------------[PROGRAM TITLE]--------------------";
    cout << endl << endl;
    cout << setw(31) << "Welcome to [PROGRAM TITLE]!" << endl;
    cout << setw(39) << "To create an admin login, press (a)" << endl;
    cout << setw(43) << "To create a normal user login, press(u)" << endl;
    cout << setw(44) << "If you have already registered press (x)" << endl;
    cout << setw(17) << "Enter input: ";
    cin >> userInput;
    cin.ignore();

    if (userInput == 'U' || userInput == 'A' || userInput == 'X')
        toLowercase(userInput);

    while (userInput != 'u' && userInput != 'a' && userInput != 'x') {
        cout << endl;
        cout << setw(25) << "Invalid input, try again: ";
        cin >> userInput;
        cin.ignore();
        if (userInput == 'U' || userInput == 'A' || userInput == 'X')
            toLowercase(userInput);
    }
    cout << endl;
}

bool searchBinary(fstream &binaryInputFile, UserInfo &user) {
    int count = 0;
    UserInfo temp;

    while (!binaryInputFile.eof()) {
        binaryInputFile.seekg(count * sizeof (UserInfo), ios::beg);
        binaryInputFile.read(reinterpret_cast<char *> (&temp.username[0]),
                USERNAME_LENGTH);
        binaryInputFile.read(reinterpret_cast<char *> (&temp.password[0]),
                PASSWORD_LENGTH);
        count++;

        if (strcmp(temp.username, user.username) == 0 &&
                strcmp(temp.password, user.password) == 0) {
            return true;
            binaryInputFile.clear();
        }
    }
    binaryInputFile.clear();

    // Return false if the desired data is not found in the file
    return false;
}

void getAdminKey(const int &adminKey) {
    static int maxAttempts = 3;
    int userKey = 0;

    cout << "Enter the Admin Key (you have " << maxAttempts << " attempts): ";
    cin >> userKey;
    cin.ignore();
    while (!(userKey == adminKey)) {
        maxAttempts--;
        if (maxAttempts == 0) {
            cout << "Too many attempts. Shutting down..." << endl;
            exit(0);
        }
        cout << "Invalid Key! (you have " << maxAttempts << " attempt(s) left): ";
        cin >> userKey;
        cin.ignore();
    }
}

bool duplicateUsername(fstream &binaryInputFile, UserInfo &user) {
    int count = 0;
    UserInfo temp;

    while (!binaryInputFile.eof()) {
        binaryInputFile.seekg(count * sizeof (UserInfo), ios::beg);
        binaryInputFile.read(reinterpret_cast<char *> (&temp.username[0]),
                USERNAME_LENGTH);
        binaryInputFile.read(reinterpret_cast<char *> (&temp.password[0]),
                PASSWORD_LENGTH);
        count++;

        if (strcmp(temp.username, user.username) == 0) {
            return true;
            binaryInputFile.clear();
        }
    }
    binaryInputFile.clear();

    // Return false if the desired data is not found in the file
    return false;
}

void displayError() {
    cout << endl;
    cout << "Invalid username/password!" << endl;
    cout << "Would you like to try again or create a new ";
    cout << "account?\nEnter (y) to try again or (c) to create";
    cout << " a new account: ";
}

void displayOptions() {
    cout << "To create an admin login, press (a)" << endl;
    cout << "To create a normal user login, press (u)" << endl;
    cout << "Enter input: ";
}

void toLowercase(char &userInput){
    userInput += 32;
}