/* 
 * File:   Admin.cpp
 * Author: Josh Carlito
 * 
 * Created on April 13, 2023, 1:02 PM
 */

#include "Admin.h"

Admin::Admin(string u) {
    username = u;
}

void Admin::readSurveys() {
    surveys.clear();
    Survey tempSurvey;
    Question tempQuestion;
    int tempSurveyNameLength = 0;
    int tempQuestionLength = 0;
    int tempAnswerLength = 0;
    fstream binarySurveyFile;

    binarySurveyFile.open("Surveys.bin", ios::in | ios::binary);
    binarySurveyFile.seekg(0, ios::end);
    streampos fileSize = binarySurveyFile.tellg();

    // Check if the file is open
    if (!binarySurveyFile.is_open() && fileSize == 0) {
        cout << "Error: Unable to open the file 'Surveys.bin'." << endl;
        return;
    }

    // If file isn't empty
    if (fileSize != 0) {
        binarySurveyFile.seekg(0, ios::beg);
        // Read and process the binary file
        while (binarySurveyFile.read(reinterpret_cast<char*> (&tempSurveyNameLength), sizeof (int))) {
            tempSurvey.name.resize(tempSurveyNameLength);
            binarySurveyFile.read(&tempSurvey.name[0], tempSurveyNameLength);

            binarySurveyFile.read(reinterpret_cast<char*> (&tempSurvey.totalQuestions), sizeof (int));
            binarySurveyFile.read(reinterpret_cast<char*> (&tempSurvey.status), sizeof (bool));

            for (int i = 0; i < tempSurvey.totalQuestions; i++) {
                binarySurveyFile.read(reinterpret_cast<char*> (&tempQuestionLength), sizeof (int));
                tempQuestion.question.resize(tempQuestionLength);
                binarySurveyFile.read(&tempQuestion.question[0], tempQuestionLength);
                binarySurveyFile.read(reinterpret_cast<char*> (&tempQuestion.questionNumber), sizeof (int));

                int numOfAnswers;
                binarySurveyFile.read(reinterpret_cast<char*> (&numOfAnswers), sizeof (int));

                for (int j = 0; j < numOfAnswers; j++) {
                    binarySurveyFile.read(reinterpret_cast<char*> (&tempAnswerLength), sizeof (int));
                    string tempAnswer;
                    tempAnswer.resize(tempAnswerLength);
                    binarySurveyFile.read(&tempAnswer[0], tempAnswerLength);
                    tempQuestion.answers.push_back(tempAnswer);
                }
                binarySurveyFile.read(reinterpret_cast<char*> (&tempQuestion.singleAnswer), sizeof (bool));
                tempSurvey.questions.push_back(tempQuestion);
                tempQuestion.answers.clear();
            }
            surveys.push_back(tempSurvey);
            tempSurvey.questions.clear();
        }
        binarySurveyFile.close();
    }
}

void Admin::displayAllSurveys() {
    int optionNumber;

    if (surveys.empty()) {
        cout << "No surveys available." << endl;
        return;
    }

    for (const auto& survey : surveys) {
        // Display survey name
        cout << "Survey name: " << survey.name << endl;
        cout << "Total number of questions: " << survey.totalQuestions << endl;

        // Iterate through the questions in the survey
        for (const auto& question : survey.questions) {
            optionNumber = 1;
            cout << "Question #" << question.questionNumber << ": " << question.question << endl;
            cout << "Answer options:" << endl;

            // Display answer options for each question
            for (const auto& answer : question.answers) {
                cout << "  " << optionNumber << ") " << answer << endl;
                optionNumber++;
            }

            // Display question type (single or multiple response)
            if (question.singleAnswer) {
                cout << "Type: Single response" << endl;
            } else {
                cout << "Type: Multiple response" << endl;
            }
            cout << endl;
        }

        if (survey.status) {
            cout << "Status: Active" << endl;
        } else {
            cout << "Status: Inactive" << endl;
        }
        cout << endl;
    }
}

int Admin::findSurveyName(string surveyName) {
    int index = 0;
    for (const auto& survey : surveys) {
        if (survey.name == surveyName) {
            return index;
        }
        index++;
    }
    return -1;
}

void Admin::displaySurveyInformation() {
    cout << endl << "SURVEY INFORMATION" << endl << endl;
    cout << left << setw(30);
    cout << "NAME";
    cout << setw(25) << "# QUESTIONS";
    cout << setw(25) << "STATUS" << endl;
    for (const auto& survey : surveys) {
        cout << setw(30) << survey.name;
        cout << setw(25) << survey.totalQuestions;
        cout << setw(25) << (survey.status ? "ACTIVE" : "INACTIVE");
        cout << endl;
    }
}

void Admin::displayActiveSurveyInformation() {
    cout << endl << "SURVEYS" << endl << endl;
    cout << left << setw(30);
    cout << "NAME";
    cout << setw(25) << "# QUESTIONS" << endl;
    ;
    for (const auto& survey : surveys) {
        if (survey.status) {
            cout << setw(30) << survey.name;
            cout << setw(25) << survey.totalQuestions;
            cout << endl;
        }
    }
}

void Admin::readUserInfo() {
    userInfo.clear();
    fstream information;
    char tempUsernameLength = 0; // User's username length 
    char tempPasswordLength = 0; // User's password length
    UserInfo temp;

    information.open("UserInfo.bin", ios::in | ios::binary);

    information.seekg(0, ios::beg);

    while (information.read(&tempUsernameLength, sizeof (char))) {
        temp.username.resize(tempUsernameLength);
        information.read(&temp.username[0], tempUsernameLength);

        information.read(&tempPasswordLength, sizeof (char));
        temp.password.resize(tempPasswordLength);
        information.read(&temp.password[0], tempPasswordLength);
        information.read(reinterpret_cast<char*>
                (&temp.adminFlag), sizeof (bool));
        information.read(reinterpret_cast<char*>
                (&temp.status), sizeof (bool));
        userInfo.push_back(temp);
    }
    information.close();
}

void Admin::printAllUserInfo() {
    cout << endl << "USER INFORMATION" << endl << endl;
    cout << left << setw(25);
    cout << "USERNAME";
    cout << setw(25) << "PASSWORD";
    cout << setw(25) << "ADMIN STATUS";
    cout << setw(25) << "ACCOUNT STATUS" << endl;
    for (int i = 0; i < userInfo.size(); i++) {
        cout << setw(25) << userInfo[i].username;
        cout << setw(25) << userInfo[i].password;
        cout << setw(25) << (userInfo[i].adminFlag ? "True" : "False");
        cout << setw(25) << (userInfo[i].status ? "Active" : "Inactive");
        cout << endl;
    }
}

void Admin::changeUserStatus(string username, bool status) {
    bool found = false;
    for (auto& user : userInfo) {
        if (user.username == username) {
            // User found
            found = true;
            user.status = status;
            break;
        }
    }

    if (!found) {
        cout << "User " << username << " not found" << endl;
    }
}

void Admin::changeUserPassword(string username, string password) {
    bool found = false;
    for (auto& user : userInfo) {
        if (user.username == username) {
            // User found
            found = true;
            user.password = password;
            break;
        }
    }

    if (!found) {
        cout << "User " << username << " not found" << endl;
    }
}

void Admin::writeUserInfoChanges() {
    char tempUsernameLength = 0;
    char tempPasswordLength = 0;
    fstream binarySignInFile;

    binarySignInFile.open("UserInfo.bin", ios::out | ios::binary);
    if (!binarySignInFile.is_open()) {
        // Handle the error here
        cout << "Failed to open UserInfo.bin in \"writeUserInfoChanges\" ";
        cout << endl;
        exit(1);
    }

    binarySignInFile.seekp(0, ios::beg);

    for (int i = 0; i < userInfo.size(); i++) {
        tempUsernameLength = userInfo[i].username.size();
        tempPasswordLength = userInfo[i].password.size();

        binarySignInFile.write(&tempUsernameLength, sizeof (char));
        binarySignInFile.write(&userInfo[i].username[0], tempUsernameLength);
        binarySignInFile.write(&tempPasswordLength, sizeof (char));
        binarySignInFile.write(&userInfo[i].password[0], tempPasswordLength);
        binarySignInFile.write(reinterpret_cast<char*> (&userInfo[i].adminFlag),
                sizeof (bool));
        binarySignInFile.write(reinterpret_cast<char*> (&userInfo[i].status),
                sizeof (bool));
    }
    binarySignInFile.close();
}

void Admin::displayUsersInfo(string usernameSearch) {
    findUsername(usernameSearch);
    cout << endl << "USER INFORMATION" << endl << endl;
    cout << left << setw(25);
    cout << "USERNAME";
    cout << setw(25) << "PASSWORD";
    cout << setw(25) << "ADMIN STATUS";
    cout << setw(25) << "ACCOUNT STATUS" << endl;
    cout << setw(25) << userInfo[userInfoIndex].username;
    cout << setw(25) << userInfo[userInfoIndex].password;
    cout << setw(25) << (userInfo[userInfoIndex].adminFlag ? "True" : "False");
    cout << setw(25) << (userInfo[userInfoIndex].status ? "Active" : "Inactive");
    cout << endl;
}

void Admin::findUsername(string usernameSearch) {
    bool found = false;
    int index = 0;
    for (const auto& user : userInfo) {
        if (user.username == usernameSearch) {
            // User found
            found = true;
            userInfoIndex = index;
            break;
        }
        index++;
    }


    if (!found) {
        cout << "User " << usernameSearch << " not found" << endl;
    }
}

void Admin::displayUserInfoMenu() {
    cout << "USER SIGN-IN INFORMATION OPTIONS:" << endl;
    cout << "To display all user Sign-in Information, press (1)" << endl;
    cout << "To search for a user's Sign-In information, press (2)" << endl;
    cout << "To change a user's password, press (3) " << endl;
    cout << "To change a user's account status, press (4)" << endl;
    cout << "To write changes, press (5)" << endl;
    cout << "To go back to the previous menu, press (-1)" << endl;
}

Survey Admin::getSurvey() {
    string tempSurvey;
    cout << endl << "Enter the name of the survey you'd like to take: ";
    getline(cin, tempSurvey);
    int index = findSurveyName(tempSurvey);
    return surveys[index];
}