/*
 * File:   main.cpp
 * Author: Josh Carlito
 *
 * Created on March 24, 2023, 8:14 PM
 * Purpose: Create a SignIn Class
 * Version: 8, Changing character arrays in UserInfo struct to strings.
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

// User Libraries
#include "SignIn.h"

using namespace std;
void signInInterface(SignIn& interface);

int main(int argc, char **argv) {
    // Set random number seed
    srand(static_cast<unsigned int> (time(0)));
    SignIn interface;

    signInInterface(interface);

    if (interface.getAdminStatus()) {
        cout << "Admin User" << endl;
    } else {
        cout << "Normal User" << endl;
    }
    return 0;
}

void signInInterface(SignIn& interface) {
    interface.displayMenu();
    while (!interface.getExitSignIn()) {
        if (interface.getUserInput() == 'u') {
            // Create a normal user account
            cout << "Register for a Normal User account" << endl << endl;
            interface.setUsername();
            interface.setPassword();
            interface.setStatus();
            // Store information to file
            interface.writeBinary();
            interface.setExitSignIn(true);
        } else if (interface.getUserInput() == 'a') {
            // Create an admin account
            cout << "Register for Admin account" << endl << endl;
            interface.validateAdminKey();
            interface.setUsername();
            interface.setPassword();
            interface.setStatus();
            // Store information to file
            interface.writeBinary();
            interface.setExitSignIn(true);
        } else {
            // Sign-in to an existing account
            cout << "Sign-In" << endl << endl;
            interface.setUsername();
            interface.setPassword();
            interface.validateUser();
            // If no account is found display an error and prompt user
            // to create an account or try again
            if (!interface.getExitSignIn()) {
                // The user only gets 5 attempts
                interface.displayError();
            }
        }
    }
}