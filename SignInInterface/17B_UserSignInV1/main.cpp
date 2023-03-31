/* 
 * File:   main.cpp
 * Author: Josh Carlito
 *
 * Created on March 13, 2023, 6:34 PM
 * Purpose: Create a userInfo struct to store user information for the future
 *          projects.
 * Version: 1, implement the UserInfo struct and take user input and make
 *              sure the output is correct.
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstring>

using namespace std;

const unsigned char USERNAME_LEN = 13;
const unsigned char PASSWORD_LEN = 13;

struct UserInfo{
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
};

void getUser(UserInfo&);
void getPwd(UserInfo&);
void displayUserInfo(UserInfo);

int main(int argc, char** argv) {
    // Set random number seed
    srand(static_cast<unsigned int>(time(0)));
    UserInfo test;
    displayUserInfo(test);
    
    return 0;
}

void getUser(UserInfo& user){
    cout << "Enter your username (12 characters max): ";
    cin.getline(user.username, USERNAME_LEN-1);
    user.username[USERNAME_LEN-1] = '\0';
}

void getPwd(UserInfo& user){
    cout << "Enter your password (12 characters max): ";
    cin.getline(user.password, PASSWORD_LEN-1);
    user.password[PASSWORD_LEN-1] = '\0';
}
    
void displayUserInfo(UserInfo user){
    cout << endl;
    cout << "User Information Records:" << endl;
    cout << endl;
    cout << "Username" << setw(25) << "Password" << endl;
    cout << user.username << setw(25) << user.password;

}