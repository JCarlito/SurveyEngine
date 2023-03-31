#include "SignIn.h"
using namespace std;

/*
 * SignIn() is a constructor that houses the whole program currently
 * It prompts the user to either create an account or sign in
 * and then stores information or validates the user's sign-in.
 * 
 * However this constructor will most likely be changed because this
 * class will be used in aggregate with the players and admins and 
 * it currently wouldn't work with that context. Suggestions would 
 * help!
 */

SignIn::SignIn() {
    // Open file
    binarySignInFile.open("UserInfo.bin", ios::in | ios::app | ios::binary);
    displayMenu();
    while (!getExitSignIn()) {
        if (getUserInput() == 'u') {
            // Create a normal user account
            cout << "Register for a Normal User account" << endl << endl;
            setUsername();
            setPassword();
            // Store information to file
            writeBinary();
            setExitSignIn(true);
        } else if (getUserInput() == 'a') {
            // Create an admin account
            cout << "Register for Admin account" << endl << endl;
            validateAdminKey();
            setUsername();
            setPassword();
            // Store information to file
            writeBinary();
            setExitSignIn(true);
        } else {
            // Sign-in to an existing account
            cout << "Sign-In" << endl << endl;
            setUsername();
            setPassword();
            validateUser();
            // If no account is found display an error and prompt user
            // to create an account or try again
            if (!getExitSignIn()) {
                // The user only gets 5 attempts
                displayError();
            }
        }
    }
    // This displays the user info but it is commented out
    // so info isn't shown. Uncomment to see how it works.
//    displayUserInfo();
}

/*
 * ~SignIn() is a destructor that closes the binary file
 */

SignIn::~SignIn() {
    // Close the file
    binarySignInFile.close();
}

/*
 * setUsername() is a mutator function that sets the 
 * user's username
 */

void SignIn::setUsername() {
    cout << "Enter your username (12 characters max): ";
    cin.getline(information.username, USERNAME_LENGTH);
    // Input validation if the username is greater than 12
    // characters
    while (cin.fail()) {
        cin.clear();
        cin.ignore(USERNAME_LENGTH, '\n');
        cout << endl;
        cout << "Invalid username (too many characters)!" << endl;
        cout << "Enter your username (12 characters max): ";
        cin.getline(information.username, USERNAME_LENGTH);
    }
    information.username[USERNAME_LENGTH - 1] = '\0';

    while (duplicateUsername() && userInput != 'x') {
        cout << endl << "Duplicate Username!" << endl;
        setUsername();
    }
}

/*
 * setPassword() is a mutator function that sets
 * the user's password
 */

void SignIn::setPassword() {
    cout << "Enter your password (12 characters max): ";
    cin.getline(information.password, PASSWORD_LENGTH);
    // Input validation if the password is greater than 12
    // characters
    while (cin.fail()) {
        cin.clear();
        cin.ignore(PASSWORD_LENGTH, '\n');
        cout << endl;
        cout << "Invalid password (too many characters)!" << endl;
        cout << "Enter your password (12 characters max): ";
        cin.getline(information.password, PASSWORD_LENGTH);
    }
    information.password[PASSWORD_LENGTH - 1] = '\0';
}

/*
 * displayUserInfo() displays the User's information
 * with their username, password, and admin flag 
 */

void SignIn::displayUserInfo() {
    // Display username, password, and admin status.
    cout << "Username: " << information.username << endl;
    cout << "Password: " << information.password << endl;
    cout << "Admin Flag: " << information.adminFlag << endl;
}

/*
 * writeBinary() writes the data to a binary file. The username
 * is written first, then the password and adminFlag
 */

void SignIn::writeBinary() {
    // Set the user's admin status
    setAdminFlag();
    // Write username, password, and admin status to the binary file
    binarySignInFile.write(&information.username[0], USERNAME_LENGTH);
    binarySignInFile.write(&information.password[0], PASSWORD_LENGTH);
    binarySignInFile.write(reinterpret_cast<char*> (&information.adminFlag),
            sizeof (bool));
    binarySignInFile.clear();
}

/*
 * setAdminFlag() flips the adminFlag on or off
 * in the information member
 */

void SignIn::setAdminFlag() {
    if (userInput == 'a') information.adminFlag = true;
    else information.adminFlag = false;
}

/*
 * readBinary() takes in a record number and reads back the
 * information and stores it in the UserInfo information
 * member
 */

void SignIn::readBinary(int record) {
    // Jump to specific record
    binarySignInFile.seekg(record * sizeof (UserInfo), ios::beg);
    // read back username, password, and admin status
    binarySignInFile.read(&information.username[0], USERNAME_LENGTH);
    binarySignInFile.read(&information.password[0], PASSWORD_LENGTH);
    binarySignInFile.read(reinterpret_cast<char*> (&information.adminFlag),
            sizeof (bool));
}

/*
 * setUserInput() sets userInput member with one of the options
 * in the menu. Contain input validation
 */

void SignIn::setUserInput() {
    cin >> userInput;
    cin.ignore();
    // If the inputs are uppercase make them lowercase
    if (userInput == 'U' || userInput == 'A' || userInput == 'X')
        toLowercase();
    // Input validation for invalid characters
    while (userInput != 'u' && userInput != 'a' && userInput != 'x') {
        cout << endl;
        cout << setw(25) << "Invalid input, try again: ";
        cin >> userInput;
        cin.ignore();
        if (userInput == 'U' || userInput == 'A' || userInput == 'X')
            toLowercase();
    }
}

/*
 * displayMenu() display's the opening start up prompt
 */

void SignIn::displayMenu() {
    cout << "--------------------Sign-In--------------------";
    cout << endl << endl;
    cout << setw(32) << "Welcome to the Sign-In page!" << endl;
    cout << setw(39) << "To create an admin login, press (a)" << endl;
    cout << setw(43) << "To create a normal user login, press(u)" << endl;
    cout << setw(44) << "If you have already registered press (x)" << endl;
    cout << setw(17) << "Enter input: ";
    setUserInput();
    cout << endl;
}

/*
 * validateUser() validates the user's sign-in information
 */

void SignIn::validateUser() {
    int count = 0;
    UserInfo temp;
    exitSignIn = false; // Initialized as false if sign-in not found

    while (!binarySignInFile.eof()) {
        // Linear search through the file
        binarySignInFile.seekg(count * sizeof (UserInfo), ios::beg);
        binarySignInFile.read(&temp.username[0], USERNAME_LENGTH);
        binarySignInFile.read(&temp.password[0], PASSWORD_LENGTH);
        count++;
        // If temp.username/password equals the given username/password
        // sign the user in.
        if (strcmp(temp.username, information.username) == 0 &&
                strcmp(temp.password, information.password) == 0) {
            // Set the admin status in the UserInfo struct
            binarySignInFile.read(reinterpret_cast<char*>
                    (&information.adminFlag), sizeof (bool));
            // exit the sign in process
            exitSignIn = true;
        }
    }
    binarySignInFile.clear();
}

/*
 * validateAdminKey() validates whether or not the user
 * knows the admin key to create an admin account. They get
 * 3 attempts to enter the admin key
 */

void SignIn::validateAdminKey() {
    static int maxAttempts = 3;
    int userKey = 0;
    // Allow the user 3 attempts to enter in the proper admin key
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

/*
 * duplicateUsername() checks to see if the user is trying to create
 * a username that has already been created
 */

bool SignIn::duplicateUsername() {
    int count = 0;
    UserInfo temp;

    while (!binarySignInFile.eof()) {
        // Linear search through the file
        binarySignInFile.seekg(count * sizeof (UserInfo), ios::beg);
        binarySignInFile.read(&temp.username[0], USERNAME_LENGTH);
        binarySignInFile.read(&temp.password[0], PASSWORD_LENGTH);
        count++;
        // if the user's username equals a username in the database
        // a duplicate is found and return true
        if (strcmp(temp.username, information.username) == 0) {
            return true;
            binarySignInFile.clear();
        }
    }
    binarySignInFile.clear();

    // No duplicate return false
    return false;
}

/*
 * displayError() displays an error message and prompts the user
 * to try again or create a new account. If they try again
 * they will get 3 attempts to sign-in
 */

void SignIn::displayError() {
    static int maxAttempts = 3;
    char userChoice;
    // Give the user 3 attempts to sign-in to an account
    if (maxAttempts == 0) {
        cout << "Too many attempts. Shutting down..." << endl;
        exit(0);
    }

    cout << endl;
    cout << "Invalid username/password!" << endl;
    cout << "Would you like to try again or create a new ";
    cout << "account?\nEnter (y) to try again or (c) to create";
    cout << " a new account: ";
    cin.get(userChoice);
    cin.ignore();
    cout << endl;
    if (userChoice == 'y' || userChoice == 'Y') {
        cout << "You have " << maxAttempts << " more attempt(s): " << endl;
        maxAttempts--;
        userInput = 'x';
    } else {
        // Display options to create a user or admin account
        displayOptions();
        cin.get(userInput);
        cin.ignore();
        cout << endl;
    }

}

/*
 * displayOptions() displays options for creating an account type
 * when the user fails to sign into there account 
 */

void SignIn::displayOptions() {
    // Options for account creation
    cout << "To create an admin login, press (a)" << endl;
    cout << "To create a normal user login, press (u)" << endl;
    cout << "Enter input: ";
}

/* 
 * toLowercase() makes character lowercase. It is used for input
 * validation 
 */

void SignIn::toLowercase() {
    userInput += 32;
}