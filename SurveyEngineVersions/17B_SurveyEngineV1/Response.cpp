/* 
 * File:   Response.cpp
 * Author: Josh Carlito
 * 
 * Created on April 13, 2023, 4:10 PM
 */

#include "Response.h"

void ResponseClass::takeSurvey() {
    cout << "Survey: " << survey.name << endl;
    cout << "Total number of questions: " << survey.totalQuestions << endl << endl;
    response.name = survey.name;

    for (const auto& question : survey.questions) {
        cout << "Question #" << question.questionNumber << ": " << question.question << endl;
        if (question.singleAnswer) {
            // Display answer options for single-response question
            for (int i = 0; i < question.answers.size(); i++) {
                cout << i + 1 << ") " << question.answers[i] << endl;
            }

            // Prompt user for answer
            int answer;
            cout << "Enter your answer (1-" << question.answers.size() << "): ";
            cin >> answer;
            while (answer < 1 || answer > question.answers.size()) {
                cout << "You entered an invalid response!" << endl;
                cout << "Try again: ";
                cin >> answer;
            }
            cout << endl;
            // Store response
            Response tempResponse;
            tempResponse.question = question.question;
            tempResponse.questionNumber = question.questionNumber;
            tempResponse.answers.push_back(question.answers[answer - 1]);
            response.responses.push_back(tempResponse);
        } else {
            // Display answer options for multiple-response question
            for (int i = 0; i < question.answers.size(); i++) {
                cout << i + 1 << ") " << question.answers[i] << endl;
            }


            vector<int> answerIndices;
            int counter = 0;
            int answer;
            cout << "This is a multi-answer question. Once you are satisfied";
            cout << " with you responses press (0):" << endl;
            cout << "Enter the number of the answer that applies (1-";
            cout << question.answers.size() << "): ";
            cin >> answer;
            cin.ignore();
            while (answer == 0 && counter == 0) {
                cout << "You have to respond!" << endl;
                cout << "Enter the number of the answer that applies (1-";
                cout << question.answers.size() << "): ";
                cin >> answer;
                cin.ignore();
            }
            counter++;
            answerIndices.push_back(answer - 1);
            while (answer != 0 && counter < question.answers.size()) {
                cout << "Enter the next number of the answer that applies (1-";
                cout << question.answers.size() << ") or (0) to continue: ";
                cin >> answer;
                cin.ignore();
                if (answer != 0) {
                    answerIndices.push_back(answer - 1);
                }
                counter++;
            }
            cout << endl;
            Response tempResponse;
            tempResponse.question = question.question;
            tempResponse.questionNumber = question.questionNumber;
            for (auto& response : answerIndices) {
                tempResponse.answers.push_back(question.answers[response]);
            }
            response.responses.push_back(tempResponse);
        }
    }
}

void ResponseClass::displaySurveyResponse() {
    cout << "Survey Name: " << response.name << endl << endl;

    for (const auto& question : survey.questions) {
        cout << "Question #" << question.questionNumber << ": " << question.question << endl;

        // Display answer options for each question
        for (const auto& response : response.responses) {
            if (response.questionNumber == question.questionNumber) {
                for (const auto& answer : response.answers) {
                    cout << "  " << answer << endl;
                }
            }
        }
        cout << endl;
    }
}

void ResponseClass::writeUserResponse() {
    fstream binaryUserResponse;
    int tempUsernameLength = 0;
    int tempSurveyNameLength = 0;
    int tempQuestionLength = 0;
    int tempAnswerLength = 0;


    binaryUserResponse.open("UserResponses.bin", ios::app | ios::binary);

    // Check if the file is open
    if (!binaryUserResponse.is_open()) {
        cout << "Error: Unable to open the file 'Surveys.bin'." << endl;
        return;
    }

    // Store username
    tempUsernameLength = response.username.size();
    binaryUserResponse.write(reinterpret_cast<char*>(&tempUsernameLength), sizeof (int));
    binaryUserResponse.write(&response.username[0], tempUsernameLength);

    // Store name of survey that was responded too
    tempSurveyNameLength = response.name.size();
    binaryUserResponse.write(reinterpret_cast<char*>(&tempSurveyNameLength), sizeof (int));
    binaryUserResponse.write(&response.name[0], tempSurveyNameLength);

    // Store the number of responses
    int numberOfResponses = response.responses.size();
    binaryUserResponse.write(reinterpret_cast<char*>(&numberOfResponses), sizeof (int));
    for (auto& response : response.responses) {
        // Store question answered
        tempQuestionLength = response.question.size();
        binaryUserResponse.write(reinterpret_cast<char*>(&tempQuestionLength), sizeof (int));
        binaryUserResponse.write(&response.question[0], tempQuestionLength);

        // Store question number
        binaryUserResponse.write(reinterpret_cast<char*>(&response.questionNumber), sizeof (int));

        // Store the number of user answers
        int numberOfAnswers = response.answers.size();
        binaryUserResponse.write(reinterpret_cast<char*>(&numberOfAnswers), sizeof (int));
        for (auto& answer : response.answers) {
            // Store the user's answer(s)
            tempAnswerLength = answer.size();
            binaryUserResponse.write(reinterpret_cast<char*>(&tempAnswerLength), sizeof (int));
            binaryUserResponse.write(&answer[0], tempAnswerLength);
        }
    }

    binaryUserResponse.close();
}

bool ResponseClass::surveyTaken() {
    fstream binaryUserResponse;
    int tempUsernameLength = 0;
    int tempSurveyNameLength = 0;
    int tempQuestionLength = 0;
    int tempAnswerLength = 0;
    string tempUsername;
    string tempSurveyName;

    binaryUserResponse.open("UserResponses.bin", ios::in | ios::binary);
    binaryUserResponse.seekg(0, ios::end);
    streampos fileSize = binaryUserResponse.tellg();

    // Check if the file is open
    if (!binaryUserResponse.is_open() && fileSize == 0) {
        cout << "Error: Unable to open the file 'UserResponse.bin'." << endl;
        return false;
    }

    if (fileSize != 0) {
        binaryUserResponse.seekg(0, ios::beg);
        // Loop through each response in the binary file
        while (binaryUserResponse.read(reinterpret_cast<char*>(&tempUsernameLength), sizeof (int))) {
            // Read the length of the username and read the username
            tempUsername.resize(tempUsernameLength);
            binaryUserResponse.read(&tempUsername[0], tempUsernameLength);

            // Read the length of the survey name and read the survey name
            binaryUserResponse.read(reinterpret_cast<char*>(&tempSurveyNameLength), sizeof (int));
            tempSurveyName.resize(tempSurveyNameLength);
            binaryUserResponse.read(&tempSurveyName[0], tempSurveyNameLength);

            // Check if the current response matches the username and survey name
            if (tempUsername == response.username && tempSurveyName == survey.name) {
                binaryUserResponse.close();
                return true;
            }

            int numberOfResponses;
            binaryUserResponse.read(reinterpret_cast<char*>(&numberOfResponses), sizeof (int));
            for (int i = 0; i < numberOfResponses; i++) {
                string tempQuestion;
                // Read the question
                binaryUserResponse.read(reinterpret_cast<char*>(&tempQuestionLength), sizeof (int));
                tempQuestion.resize(tempQuestionLength);
                binaryUserResponse.read(&tempQuestion[0], tempQuestionLength);

                // Read the question number
                int tempQuestionNumber;
                binaryUserResponse.read(reinterpret_cast<char*>(&tempQuestionNumber), sizeof (int));

                // Read the number of answers and skip over each answer
                int numberOfAnswers;
                binaryUserResponse.read(reinterpret_cast<char*>(&numberOfAnswers), sizeof (int));
                for (int j = 0; j < numberOfAnswers; j++) {
                    string tempAnswer;
                    binaryUserResponse.read(reinterpret_cast<char*>(&tempAnswerLength), sizeof (int));
                    tempAnswer.resize(tempAnswerLength);
                    binaryUserResponse.read(&tempAnswer[0], tempAnswerLength);
                }
            }
        }
    }
    binaryUserResponse.close();
    return false;
}