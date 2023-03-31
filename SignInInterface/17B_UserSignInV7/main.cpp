/*
 * File:   main.cpp
 * Author: Josh Carlito
 *
 * Created on March 20, 2023, 8:14 PM
 * Purpose: Create a SignIn Class
 * Version: 7, Create a SignIn Class
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

int main(int argc, char **argv) {
    // Set random number seed
    srand(static_cast<unsigned int> (time(0)));
    SignIn user;
    
    cout << endl;
    cout << "Username: " << user.getUsername() << endl;
    return 0;
}
