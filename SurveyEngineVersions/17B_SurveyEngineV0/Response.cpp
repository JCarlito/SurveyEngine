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
            while (answer < 1 || answer > question.answers.size()){
                
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
            int answer;
            cout << "Enter the number of the answer that applies (1-";
            cout << question.answers.size() << "): ";
            cin >> answer;
            while (answer < 0 || answer > question.answers.size() || (answer == 1 && answerIndices.empty())) {
                cout << "Enter the number of the answer that applies (1-";
                cout << question.answers.size() << "), or enter 0 to continue: ";
                cin >> answer;
            }

            // Store responses
            while (answer != 0) {
                answerIndices.push_back(answer);
                Response tempResponse;
                tempResponse.question = question.question;
                tempResponse.questionNumber = question.questionNumber;
                tempResponse.answers.push_back(question.answers[answer - 1]);
                response.responses.push_back(tempResponse);

                if (answerIndices.size() < question.answers.size()) {
                    do {
                        cout << "Enter the number of another answer that applies (1-" << question.answers.size() << "), or enter 0 to continue: ";
                        cin >> answer;
                    } while (answer < 0 || answer > question.answers.size() || find(answerIndices.begin(), answerIndices.end(), answer) != answerIndices.end());
                } else {
                    answer = 0;
                }
            }
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