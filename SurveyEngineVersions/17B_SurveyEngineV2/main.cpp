/* 
 * File:   main.cpp
 * Author: Josh Carlito
 *
 * Created on April 19, 2023, 5:12 PM
 * Purpose: Create a simple survey engine
 * Version: 2, create a UI.
 */

#include "SurveyEngine.h"
#include "Admin.h"
#include "Response.h"
#include "SignIn.h"

void signInInterface(SignIn& interface);
void displayUserInformation(Admin& admin);
void changePassword(Admin& admin);
void changeStatus(Admin& admin);

int main(int argc, char** argv) {
    SignIn interface;

    signInInterface(interface);
    if (interface.getAdminStatus()) {
        Admin admin(interface.getUsername());
        int adminInput;
        char adminMenuInput;
        admin.displayAdminMenu();
        cin.get(adminMenuInput);
        while (adminMenuInput != 'x' && adminMenuInput != 'X') {
            if (adminMenuInput == 'a' || adminMenuInput == 'A') {
                admin.readSurveys();
                admin.displaySurveyInfoMenu();
                cout << endl;
                cout << "Enter input: ";
                cin >> adminInput;
                cin.ignore();
                while (adminInput != -1) {
                    if (adminInput == 1) {
                        string tempSurveyName;
                        cout << "Enter the name you'd like to give the survey: ";
                        getline(cin, tempSurveyName);
                        admin.setSurveyName(tempSurveyName);
                        char questionFlag = ' ';
                        while (questionFlag != '$') {
                            admin.createQuestion();
                            cout << "To create another question press (1) or ";
                            cout << "stop creating questions press ($)" << endl;
                            cout << "Enter input: ";
                            cin >>questionFlag;
                            cin.ignore();
                        }
                        admin.setSurveyStatus();
                    } else if (adminInput == 2) {
                        admin.viewSurveyCreation();
                    } else if (adminInput == 3) {
                        admin.clearSurveyCreation();
                        cout << "Your survey has been cleared!" << endl;
                    } else if (adminInput == 4) {
                        admin.writeSurvey();
                        cout << "Survey has been saved!" << endl;
                        admin.readSurveys();
                    } else if (adminInput == 5) {
                        admin.displayActiveSurveyInformation();
                    } else if (adminInput == 6) {
                        admin.displaySurveyInformation();
                    } else if (adminInput == 7) {
                        admin.displayAllSurveys();
                    } else if (adminInput == 8) {
                        string tempSurveyName;
                        cout << "Enter the name of the survey you wish to";
                        cout << " display: ";
                        getline(cin, tempSurveyName);
                        admin.displayFoundSurvey(tempSurveyName);
                    } else if (adminInput == 9) {
                        admin.changeSurveyStatus();
                    } else if (adminInput == 10) {
                        admin.writeSurveyChanges();
                        cout << "Your status change has been written!" << endl;
                        admin.readSurveys();
                    }
                    cout << endl;
                    cout << "Enter input: ";
                    cin >> adminInput;
                    cin.ignore();
                }
            } else if (adminMenuInput == 'b' || adminMenuInput == 'B') {
                admin.readUserResponses();
                admin.readSurveys();
                admin.displaySurveyDataMenu();
                cout << "Enter input: ";
                cin >> adminInput;
                cin.ignore();
                while (adminInput != -1) {
                    if (adminInput == 1) {
                        admin.displayResponsesOverview();
                    } else if (adminInput == 2) {
                        admin.displayAllSurveyResponses();
                    } else if (adminInput == 3) {
                        string tempUsername;
                        cout << "Enter the user's username: ";
                        getline(cin, tempUsername);
                        admin.displayUsersResponses(tempUsername);
                    } else if (adminInput == 4) {
                        string tempUsername;
                        string tempSurveyName;
                        cout << "Enter the user's username: ";
                        getline(cin, tempUsername);
                        cout << "Enter the survey's name: ";
                        getline(cin, tempSurveyName);
                        admin.displaySpecificSurveyResponse(tempUsername, tempSurveyName);
                    } else {
                        string tempSurveyName;
                        cout << "Enter the name of the survey you want";
                        cout << " to see the results for: ";
                        getline(cin, tempSurveyName);
                        admin.displaySurveyData(tempSurveyName);
                    }
                    cout << endl;
                    cout << "Enter input: ";
                    cin >> adminInput;
                    cin.ignore();
                }
            } else {
                admin.readUserInfo();
                admin.displayUserInfoMenu();
                cout << "Enter input: ";
                cin >> adminInput;
                cin.ignore();
                while (adminInput != -1) {
                    if (adminInput == 1) {
                        admin.printAllUserInfo();
                    } else if (adminInput == 2) {
                        displayUserInformation(admin);
                    } else if (adminInput == 3) {
                        changePassword(admin);
                    } else if (adminInput == 4) {
                        changeStatus(admin);
                    } else {
                        admin.writeUserInfoChanges();
                        cout << "Changes have been written" << endl;
                        admin.readUserInfo();
                    }
                    cout << endl;
                    cout << "Enter input: ";
                    cin >> adminInput;
                    cin.ignore();
                }
            }
            admin.displayAdminMenu();
            cin.get(adminMenuInput);
        }
    } else {
        int submitFlag;
        ResponseClass user(interface.getUsername());
        user.displaySurveyInformation();
        while (submitFlag != 1 && submitFlag != 3) {
            user.getSurvey();
            while (user.surveyTaken()) {
                int breakout;
                cout << "You already took that survey!" << endl;
                cout << "To quit press (3) else press (0): ";
                cin >> breakout;
                cin.ignore();
                if (breakout == 3) {
                    submitFlag = 3;
                    exit(0);
                }
                user.getSurvey();
            }
            user.takeSurvey();
            user.displaySurveyResponse();
            cout << "To submit your survey, press (1):" << endl;
            cout << "To retract your survey and try again, press (2):" << endl;
            cout << "To retract your survey and quit (3):" << endl;

            cout << "Enter input: ";
            cin >> submitFlag;
            cin.ignore();
            if (submitFlag == 1) {
                user.writeUserResponse();
                cout << "Your response was submitted! Thank you for participating";
                cout << endl;
            } else {
                cout << "Your response was retracted." << endl;
            }
        }
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

void displayUserInformation(Admin& admin) {
    string tempUsername;
    cout << "Enter the username of the user you'd like to see: ";
    cin >> tempUsername;
    admin.displayUsersInfo(tempUsername);
}

void changePassword(Admin& admin) {
    string tempUsername;
    string tempPassword;
    cout << "Enter the username of the user's password you'd like";
    cout << " to change: ";
    cin >> tempUsername;
    cout << "Enter the new password: ";
    cin >> tempPassword;
    admin.changeUserPassword(tempUsername, tempPassword);
}

void changeStatus(Admin& admin) {
    string tempUsername;
    bool tempStatus;
    cout << "Enter the username of the user's status you'd like to change: ";
    cin >> tempUsername;
    cout << "Press (1) to activate or (0) to deactivate: ";
    cin >> tempStatus;
    admin.changeUserStatus(tempUsername, tempStatus);
}