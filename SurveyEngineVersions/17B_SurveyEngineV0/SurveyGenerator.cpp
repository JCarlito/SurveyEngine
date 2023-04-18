/* 
 * File:   SurveyGenerator.cpp
 * Author: Josh Carlito
 * 
 * Created on April 13, 2023, 1:05 PM
 */

#include "SurveyGenerator.h"

void SurveyGenerator::setSurveyName(string surveyName) {
    survey.name = surveyName;
}

void SurveyGenerator::createQuestion() {
    Question tempQuestion; // Temporary question
    string tempAnswer; // temporary answer

    // Set question number
    tempQuestion.questionNumber = number + 1;
    // Prompt admin for the question
    cout << "Enter " << survey.name << "'s question #";
    cout << tempQuestion.questionNumber << ": ";
    getline(cin, tempQuestion.question);
    // Prompt admin for the answer options
    cout << "Enter " << survey.name << "'s answer options for question #";
    cout << tempQuestion.questionNumber << " (press x to stop): ";
    getline(cin, tempAnswer);
    // While the admin doesn't press 'x' keep asking for answer options
    while (tempAnswer != "x" && tempAnswer != "X") {
        tempQuestion.answers.push_back(tempAnswer);
        cout << "Enter next option (press x to stop): ";
        getline(cin, tempAnswer);
    }
    // Prompt admin for the type of response this question allows
    cout << "Enter the type of question this is (1) for single response or ";
    cout << "(0) for multiple response: ";
    cin >> tempQuestion.singleAnswer;
    survey.questions.push_back(tempQuestion);
    survey.totalQuestions = survey.questions.size();
    number++;
}

void SurveyGenerator::viewSurvey() {
    int optionNumber;
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
        cout << endl; // Add a line break between questions
    }
    if (survey.status) {
        cout << "Status: Active" << endl;
    } else {
        cout << "Status: Inactive" << endl;
    }
}

void SurveyGenerator::writeSurvey() {
    int tempSurveyNameLength = 0;
    int tempQuestionLength = 0;
    int tempAnswerLength = 0;
    fstream binarySurveyFile;

    binarySurveyFile.open("Surveys.bin", ios::app | ios::binary);

    // Check if the file is open
    if (!binarySurveyFile.is_open()) {
        cout << "Error: Unable to open the file 'Surveys.bin'." << endl;
        return;
    }
    
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
    binarySurveyFile.close();
}

void SurveyGenerator::setSurveyStatus() {
    cout << "Enter the status of the survey:" << endl;
    cout << "(1) for ACTIVE or (0) for INACTIVE: ";
    cin >> survey.status;
    cin.ignore();
}