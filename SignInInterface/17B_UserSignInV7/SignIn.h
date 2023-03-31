/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SignIn.h
 * Author: Josh Carlito
 *
 * Created on March 20, 2023, 8:15 PM
 */

#ifndef SIGNIN_H
#define SIGNIN_H

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "UserInfoStruct.h"

using namespace std;

class SignIn {
private:
    // Admin key necessary for creating an admin account
    const int adminKey = 1234;
    // Initialize Variables
    UserInfo information;       // UserInfo struct that stores
                                // the username and password
    fstream binarySignInFile;   // Binary file the SignIn info is being 
                                // written to
    char userInput;             // User input to navigate the sign-in class
    bool exitSignIn = false;    // Flag on when to end the sign-in process
   
    // Mutator functions
    void setUserInput();    // Set user input
    void setUsername();     // Set username
    void setPassword();     // Set password
    void setAdminFlag();    // Set admin flag to distinguish between accounts
    void setExitSignIn(bool flag) // Set exit sign-in flag
    { exitSignIn = flag; }

    // Accessor Functions
    bool getExitSignIn() const 
    { return exitSignIn; }
    char getUserInput() const 
    { return userInput; }
    
    // Misc functions
    
    // Validate user's admin key
    void validateAdminKey();
    // Write user information to a binary file
    void writeBinary();
    // Read information from the binary file (currently not in use)
    void readBinary(int record);
    // Validate user sign-in information
    void validateUser();
    // Check if user is trying to make a duplicate username
    bool duplicateUsername();
    void toLowercase();
    
    // Display functions
    
    // Display opening sign-in prompt 
    void displayMenu();
    // Display an error message if username/password are invalid
    void displayError();
    // Display options for a user after an error message
    void displayOptions();
    // Display user's information
    void displayUserInfo();
    
    
public:
    // Constructor
    SignIn();
    // Destructor
    ~SignIn();
    
    // Accessor function
    char* getUsername()
    { return information.username; }
};

#endif /* SIGNIN_H */