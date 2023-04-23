#include "SignIn.h"

/*
 * setUsername() is a mutator function that sets the 
 * user's username
 */

void SignIn::setUsername() {
    cout << "Enter your username (12 characters max): ";
    getline(cin, information.username);
    // Input validation if the username is greater than 12
    // characters
    while (information.username.size() > USERNAME_LENGTH) {
        cout << endl;
        cout << "Invalid username (too many characters)!" << endl;
        cout << "Enter your username (12 characters max): ";
        getline(cin, information.username);
    }

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
    getline(cin, information.password);
    // Input validation if the password is greater than 12
    // characters
    while (information.password.size() > PASSWORD_LENGTH) {
        cout << endl;
        cout << "Invalid password (too many characters)!" << endl;
        cout << "Enter your password (12 characters max): ";
        getline(cin, information.password);
    }
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
    cout << "Status: " << (information.status == true ? 'T' : 'F') << endl;
}

/*
 * writeBinary() writes the data to a binary file. The username
 * is written first, then the password and adminFlag
 */

void SignIn::writeBinary() {
    // Set the user's admin status
    setAdminFlag();
    char tempUsernameLength = 0; // User's username length 
    char tempPasswordLength = 0; // User's password length
    fstream binarySignInFile;

    binarySignInFile.open("UserInfo.bin", ios::app | ios::binary);

    tempUsernameLength = information.username.size();
    tempPasswordLength = information.password.size();

    // Write username, password, and admin status to the binary file
    binarySignInFile.write(&tempUsernameLength, sizeof (char));
    binarySignInFile.write(&information.username[0], tempUsernameLength);
    binarySignInFile.write(&tempPasswordLength, sizeof (char));
    binarySignInFile.write(&information.password[0], tempPasswordLength);
    binarySignInFile.write(reinterpret_cast<char*> (&information.adminFlag),
            sizeof (bool));
    binarySignInFile.write(reinterpret_cast<char*> (&information.status),
            sizeof (bool));
    binarySignInFile.close();
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
    cout << setw(44) << "To create a normal user login, press (u)" << endl;
    cout << setw(44) << "If you have already registered press (x)" << endl;
    cout << setw(17) << "Enter input: ";
    setUserInput();
    cout << endl;
}

/*
 * validateUser() validates the user's sign-in information
 */

void SignIn::validateUser() {
    char tempUsernameLength = 0; // User's username length 
    char tempPasswordLength = 0; // User's password length
    fstream binarySignInFile;
    UserInfo temp;
    exitSignIn = false; // Initialized as false if sign-in not found

    binarySignInFile.open("UserInfo.bin", ios::in | ios::binary);
    binarySignInFile.seekg(0, ios::beg);

    // Linear search through the file
    while (binarySignInFile.read(&tempUsernameLength, sizeof (char))) {
        temp.username.resize(tempUsernameLength);
        binarySignInFile.read(&temp.username[0], tempUsernameLength);

        binarySignInFile.read(&tempPasswordLength, sizeof (char));
        temp.password.resize(tempPasswordLength);
        binarySignInFile.read(&temp.password[0], tempPasswordLength);
        binarySignInFile.read(reinterpret_cast<char*>
                (&temp.adminFlag), sizeof (bool));
        binarySignInFile.read(reinterpret_cast<char*>
                (&information.status), sizeof (bool));

        // If temp.username/password equals the given username/password
        // sign the user in.
        if (temp.username == information.username &&
                temp.password == information.password) {

            if (information.status == true) {
                information.adminFlag = temp.adminFlag;
                // exit the sign in process
                exitSignIn = true;
                break;
            } else {
                cout << endl;
                cout << "INACTIVE ACCOUNT" << endl;
            }
        }
    }
    binarySignInFile.close();
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
    fstream binarySignInFile;
    char tempUsernameLength = 0; // User's username length 
    char tempPasswordLength = 0; // User's password length
    int count = 0;
    UserInfo temp;

    binarySignInFile.open("UserInfo.bin", ios::in | ios::binary);

    binarySignInFile.seekg(0, ios::beg);

    // Linear search through the file
    while (binarySignInFile.read(&tempUsernameLength, sizeof (char))) {
        temp.username.resize(tempUsernameLength);
        binarySignInFile.read(&temp.username[0], tempUsernameLength);

        binarySignInFile.read(&tempPasswordLength, sizeof (char));
        temp.password.resize(tempPasswordLength);
        binarySignInFile.read(&temp.password[0], tempPasswordLength);
        binarySignInFile.read(reinterpret_cast<char*>
                (&information.adminFlag), sizeof (bool));
        binarySignInFile.read(reinterpret_cast<char*>
                (&information.status), sizeof (bool));

        // if the user's username equals a username in the database
        // a duplicate is found and return true
        if (temp.username == information.username) {
            if (binarySignInFile.eof())
                binarySignInFile.clear();
            binarySignInFile.close();
            return true;
        }
    }
    if (binarySignInFile.eof())
        binarySignInFile.clear();
    binarySignInFile.close();

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