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

void Admin::displayAllSurveyResponses() {
    for (const auto& response : responses) {
        cout << "Username: " << response.username << endl;
        cout << "Survey Name: " << response.name << endl << endl;

        for (const auto& singleResponse : response.responses) {
            cout << "Question #" << singleResponse.questionNumber << ": ";
            cout << singleResponse.question << endl;

            // Display user's answers for each question
            for (const auto& answer : singleResponse.answers) {
                cout << "  " << answer << endl;
            }
            cout << endl;
        }
        cout << "-----------------------------------------------------------";
        cout << endl;
    }
}

void Admin::fillSurveyData(const string& surveyName) {
    data.name = surveyName;
    data.data.clear();

    // Find the survey with the given name
    int surveyIndex = findSurveyName(surveyName);
    if (surveyIndex == -1) {
        cout << "Error: Survey not found!" << endl;
        return;
    }

    const Survey& targetSurvey = surveys[surveyIndex];

    // Initialize Data objects for each question
    for (const auto& question : targetSurvey.questions) {
        Data tempData;
        tempData.question = question.question;
        tempData.questionNumber = question.questionNumber;

        for (const auto& answer : question.answers) {
            tempData.answerData.push_back(make_pair(answer, 0));
        }

        data.data.push_back(tempData);
    }

    // Iterate through responses and update the data
    for (const auto& response : responses) {
        if (response.name == surveyName) {
            for (const auto& singleResponse : response.responses) {
                for (const auto& answer : singleResponse.answers) {
                    int questionNumber = singleResponse.questionNumber;
                    const vector<pair<string, int> > &answerData = data.data[questionNumber - 1].answerData;

                    // Find the index of the selected answer in the answerData vector
                    int answerIndex = findTargetData(answerData, answer);

                    // Update the count for the selected answer
                    if (answerIndex != -1) {
                        data.data[questionNumber - 1].answerData[answerIndex].second++;
                    }
                }
            }
        }
    }
}

int Admin::findTargetData(const vector<pair<string, int> > &answerData, const string& answer) {
    for (int i = 0; i < answerData.size(); i++) {
        if (answerData[i].first == answer) {
            return i;
        }
    }
    return -1;
}

void Admin::displaySurveyData(const string& surveyName) {
    fillSurveyData(surveyName);
    if (data.name.empty()) {
        return;
    }
    cout << data.name << " DATA" << endl << endl;

    for (const auto& questionData : data.data) {
        cout << "Question #" << questionData.questionNumber << ": " << questionData.question << endl;

        for (const auto& answerCount : questionData.answerData) {
            //            string tempQuestion = answerCount.first;
            int tempAnswerData = answerCount.second;
            if (tempAnswerData > 0)
                cout << "  " << setw(30) << left << answerCount.first;
            else cout << "  " << answerCount.first;
            for (int i = 0; i < tempAnswerData; i++) {
                cout << "#";
                //                if (i == 0) cout << setw(30 - answerCount.first.length()) << right;
            }
            cout << endl;
        }
        cout << endl;
    }
}

void Admin::displayResponsesOverview() {
    cout << "RESPONSES OVERVIEW" << endl << endl;
    cout << left << setw(25);
    cout << "USERNAME";
    cout << setw(25) << "SURVEYS TAKEN" << endl;

    // Store the count of surveys taken by each user
    map<string, int> userSurveys;

    for (const auto& response : responses) {
        // If user isn't in the map add them
        if (userSurveys.find(response.username) == userSurveys.end()) {
            userSurveys[response.username] = 1;
        } else {
            // else increment their count
            userSurveys[response.username]++;
        }
    }

    // Display the map's contents
    for (const auto& userSurvey : userSurveys) {

        cout << setw(25) << userSurvey.first;
        cout << setw(25) << userSurvey.second << endl;
    }
}

void Admin::displaySpecificSurveyResponse(string u, string tempSurveyName) {
    bool found = false;
    for (const auto& response : responses) {
        if (response.username == u && response.name == tempSurveyName) {
            cout << "Username: " << response.username << endl;
            cout << "Survey Name: " << response.name << endl << endl;

            for (const auto& singleResponse : response.responses) {
                cout << "Question #" << singleResponse.questionNumber << ": ";
                cout << singleResponse.question << endl;

                // Display user's answers for each question
                for (const auto& answer : singleResponse.answers) {

                    cout << "  " << answer << endl;
                }
                cout << endl;
            }
            cout << "-----------------------------------------------------------";
            cout << endl;
            found = true;
        } 
    }
    if (!found){
        cout << "Response not found!" << endl;
    }
}

void Admin::displayUsersResponses(string u) {
    bool found = false;
    for (const auto& response : responses) {
        if (response.username == u) {
            cout << "Username: " << response.username << endl;
            cout << "Survey Name: " << response.name << endl << endl;

            for (const auto& singleResponse : response.responses) {
                cout << "Question #" << singleResponse.questionNumber << ": ";
                cout << singleResponse.question << endl;

                // Display user's answers for each question
                for (const auto& answer : singleResponse.answers) {

                    cout << "  " << answer << endl;
                }
                cout << endl;
            }
            cout << "-----------------------------------------------------------";
            cout << endl;
            found = true;
        } 
    }
    if (!found){
        cout << "Response not found!" << endl;
    }
}

void Admin::readUserResponses() {
    responses.clear();
    fstream binaryUserResponse;
    int tempUsernameLength = 0;
    int tempSurveyNameLength = 0;
    int tempQuestionLength = 0;
    int tempAnswerLength = 0;
    int numberOfResponses, numberOfAnswers;
    string tempUsername;
    string tempSurveyName;
    string tempQuestion;
    string tempAnswer;

    binaryUserResponse.open("UserResponses.bin", ios::in | ios::binary);
    binaryUserResponse.seekg(0, ios::end);
    streampos fileSize = binaryUserResponse.tellg();

    // Check if the file is open
    if (!binaryUserResponse.is_open() && fileSize == 0) {
        cout << "Error: Unable to open the file 'UserResponses.bin'." << endl;
        return;
    }

    // Read in user responses from the binary file
    if (fileSize != 0) {
        binaryUserResponse.seekg(0, ios::beg);
        while (binaryUserResponse.read(reinterpret_cast<char*>(&tempUsernameLength), sizeof (int))) {
            SurveyResponse tempResponse;

            // Read username
            tempUsername.resize(tempUsernameLength);
            binaryUserResponse.read(&tempUsername[0], tempUsernameLength);
            tempResponse.username = tempUsername;

            // Read name of the survey that was responded to
            binaryUserResponse.read(reinterpret_cast<char*>(&tempSurveyNameLength), sizeof (int));
            tempSurveyName.resize(tempSurveyNameLength);
            binaryUserResponse.read(&tempSurveyName[0], tempSurveyNameLength);
            tempResponse.name = tempSurveyName;

            // Read the number of responses
            binaryUserResponse.read(reinterpret_cast<char*>(&numberOfResponses), sizeof (int));
            for (int i = 0; i < numberOfResponses; ++i) {
                Response tempSingleResponse;

                // Read question
                binaryUserResponse.read(reinterpret_cast<char*>(&tempQuestionLength), sizeof (int));
                tempQuestion.resize(tempQuestionLength);
                binaryUserResponse.read(&tempQuestion[0], tempQuestionLength);
                tempSingleResponse.question = tempQuestion;

                // Read question number
                binaryUserResponse.read(reinterpret_cast<char*>(&tempSingleResponse.questionNumber), sizeof (int));

                // Read the number of user answers
                binaryUserResponse.read(reinterpret_cast<char*>(&numberOfAnswers), sizeof (int));
                for (int j = 0; j < numberOfAnswers; ++j) {
                    // Read user's answer(s)

                    binaryUserResponse.read(reinterpret_cast<char*>(&tempAnswerLength), sizeof (int));
                    tempAnswer.resize(tempAnswerLength);
                    binaryUserResponse.read(&tempAnswer[0], tempAnswerLength);
                    tempSingleResponse.answers.push_back(tempAnswer);
                }

                tempResponse.responses.push_back(tempSingleResponse);
            }

            responses.push_back(tempResponse);
        }
    }
    binaryUserResponse.close();
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
        cout << "------------------------------------------------------------";
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

void Admin::writeSurveyChanges() {
    int tempSurveyNameLength = 0;
    int tempQuestionLength = 0;
    int tempAnswerLength = 0;
    fstream binarySurveyFile;

    binarySurveyFile.open("Surveys.bin", ios::out | ios::binary);

    // Check if the file is open
    if (!binarySurveyFile.is_open()) {
        cout << "Error: Unable to open the file 'Surveys.bin'." << endl;
        return;
    }
    for (auto& survey : surveys) {
        tempSurveyNameLength = survey.name.size();
        binarySurveyFile.write(reinterpret_cast<char*>(&tempSurveyNameLength), sizeof (int));
        binarySurveyFile.write(&survey.name[0], tempSurveyNameLength);
        binarySurveyFile.write(reinterpret_cast<char*>(&survey.totalQuestions), sizeof (int));
        binarySurveyFile.write(reinterpret_cast<char*>(&survey.status), sizeof (bool));
        for (auto& question : survey.questions) {
            tempQuestionLength = question.question.size();
            binarySurveyFile.write(reinterpret_cast<char*>(&tempQuestionLength), sizeof (int));
            binarySurveyFile.write(&question.question[0], tempQuestionLength);
            binarySurveyFile.write(reinterpret_cast<char*>(&question.questionNumber), sizeof (int));
            int numberOfAnswers = question.answers.size();
            binarySurveyFile.write(reinterpret_cast<char*>(&numberOfAnswers), sizeof (int));
            for (auto& answer : question.answers) {
                tempAnswerLength = answer.size();
                binarySurveyFile.write(reinterpret_cast<char*>(&tempAnswerLength), sizeof (int));
                binarySurveyFile.write(&answer[0], tempAnswerLength);
            }
            binarySurveyFile.write(reinterpret_cast<char*>(&question.singleAnswer), sizeof (bool));
        }
    }
    binarySurveyFile.close();
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

void Admin::displaySurveyInfoMenu() {
    cout << "SURVEY CREATION OPTIONS:" << endl;
    cout << "To create a survey, press (1)" << endl;
    cout << "To review your creation, press (2)" << endl;
    cout << "To clear your creation, press (3) " << endl;
    cout << "To save your survey creation, press (4)" << endl << endl;


    cout << "PREVIOUS SURVEY OPTIONS:" << endl;
    cout << "To view active survey list, press (5)" << endl;
    cout << "To view a full survey list, press (6)" << endl;
    cout << "To display all surveys in there entirety, press (7)" << endl;
    cout << "To display a specific survey, press (8)" << endl;
    cout << "To change a survey's status, press (9)" << endl;
    cout << "To write your change, press (10)" << endl;
    cout << "To go back to the previous menu, press (-1)" << endl;
}

void Admin::displaySurveyDataMenu() {
    cout << "SURVEY DATA OPTIONS:" << endl;
    cout << "To view an overview of the responses, press (1)" << endl;
    cout << "To view all survey responses, press (2)" << endl;
    cout << "To view a user's responses, press (3)" << endl;
    cout << "To view a user's response to a survey, press (4)" << endl;
    cout << "To display a survey's overall data, press (5) " << endl;
    cout << "To go back to the previous menu, press (-1)" << endl;
}

void Admin::changeSurveyStatus() {
    string tempSurveyName;
    bool tempStatus;
    cout << "Enter the survey's name for the status you'd like to change: ";
    getline(cin, tempSurveyName);
    cout << "Enter the activity status (1) for active or (0) for inactive: ";
    cin >> tempStatus;
    int index = findSurveyName(tempSurveyName);
    surveys[index].status = tempStatus;
}

Survey Admin::getSurvey() {
    string tempSurvey;
    cout << endl << "Enter the name of the survey you'd like to take: ";
    getline(cin, tempSurvey);
    int index = findSurveyName(tempSurvey);

    return surveys[index];
}

void Admin::displayFoundSurvey(string surveyName) {
    int optionNumber;
    int index = findSurveyName(surveyName);
    if (index != -1) {
        // Display survey name
        cout << "Survey name: " << surveys[index].name << endl;
        cout << "Total number of questions: " << surveys[index].totalQuestions << endl;
        // Iterate through the questions in the survey
        for (const auto& question : surveys[index].questions) {
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
            cout << endl; // Add a line break between questions
        }
        if (surveys[index].status) {
            cout << "Status: Active" << endl;
        } else {
            cout << "Status: Inactive" << endl;
        }
    } else {
        cout << endl << "SURVEY NOT FOUND!" << endl << endl;
    }
}

void Admin::displayAdminMenu() {
    cout << "-----------------------------------";
    cout << "ADMIN MENU";
    cout << "-----------------------------------" << endl << endl;
    cout << "PREVIOUS SURVEYS & SURVEY CREATION (a)" << endl;
    cout << "SURVEY DATA (b)" << endl;
    cout << "USER INFORMATION OPTIONS (c)" << endl;
    cout << "TO EXIT (x)" << endl;
    cout << "Enter input: ";
}