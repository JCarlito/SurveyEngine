/* 
 * File:   Response.cpp
 * Author: Josh Carlito
 * 
 * Created on April 13, 2023, 4:10 PM
 */

#include "Response.h"

void ResponseClass::takeSurvey() {
    cout << "Survey: " << survey.name << endl;
    cout << "Total number of questions: " << survey.totalQuestions << endl;

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
    cout << "Survey Name: " << survey.name << endl;
    cout << "Number of Questions: " << survey.totalQuestions << endl;

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