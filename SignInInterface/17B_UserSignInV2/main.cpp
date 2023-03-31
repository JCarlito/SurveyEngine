/* 
 * File:   main.cpp
 * Author: Josh Carlito
 *
 * Created on March 13, 2023, 7:02 PM
 * Purpose: Create a userInfo struct to store user information for the future
 *          projects.
 * Version: 2, read and write info to a binary file.
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>

using namespace std;

const unsigned char USERNAME_LENGTH = 13;
const unsigned char PASSWORD_LENGTH = 13;

struct UserInfo{
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
};

void getUsername(UserInfo& user);
void getPassword(UserInfo& user);
void writeText(fstream& textFile, UserInfo user);
void writeBinary(fstream& binaryFile, UserInfo user);
void readBinary(fstream& binaryFile, UserInfo& user, int record);
void displayUserInfo(UserInfo user);

int main(int argc, char** argv) {
    // Set random number seed
    srand(static_cast<unsigned int>(time(0)));
    UserInfo test;
    fstream textOutputFile;
    fstream binaryFile;
    textOutputFile.open("UserInfo.txt", ios::app);
    binaryFile.open("UserInfo.bin", ios::in | ios::app | ios::binary);
    
    
//    for(int i=0;i<2;i++){
//        getUser(test);
//        getPassword(test);
//        writeText(textFile, test);
//        writeBinary(binaryFile, test);
//    }
    cout << endl << endl;
    readBinary(binaryFile, test, 5);
    displayUserInfo(test);
    textOutputFile.close();
    binaryFile.close();
    return 0;
}

void getUsername(UserInfo& user){
    cout << "Enter your username (12 characters max): ";
    cin.getline(user.username, USERNAME_LENGTH-1);
    user.username[USERNAME_LENGTH-1] = '\0';
}

void getPassword(UserInfo& user){
    cout << "Enter your password (12 characters max): ";
    cin.getline(user.password, PASSWORD_LENGTH-1);
    user.password[PASSWORD_LENGTH-1] = '\0';
}
    
void displayUserInfo(UserInfo user){
    cout << "Username: " << user.username << endl;
    cout << "Password: " << user.password << endl;
}

void writeText(fstream& textOutputFile, UserInfo user){
    if(textOutputFile.tellp()==0){
        textOutputFile << endl;
        textOutputFile << "User Information Records:" << endl;
        textOutputFile << endl;
        textOutputFile << "Username" << setw(25) << "Password" << endl;
    }

    textOutputFile << user.username << setw(25) << user.password << endl;
    textOutputFile.clear();
}

void writeBinary(fstream& binaryOutputFile, UserInfo user){
    binaryOutputFile.write(&user.username[0], USERNAME_LENGTH);
    binaryOutputFile.write(&user.password[0], PASSWORD_LENGTH);
    binaryOutputFile.clear();
}

void readBinary(fstream& binaryInputFile, UserInfo& user, int record){
    binaryInputFile.seekg(record*sizeof(UserInfo), ios::beg);
    
    binaryInputFile.read(&user.username[0], USERNAME_LENGTH);
    binaryInputFile.read(&user.password[0], PASSWORD_LENGTH);
}