/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Admin.h
 * Author: Josh Carlito
 *
 * Created on April 13, 2023, 1:02 PM
 */

#ifndef ADMIN_H
#define ADMIN_H
#include "SurveyEngine.h"
#include "SurveyGenerator.h"

class Admin {
private:
    string username;
    int userInfoIndex;
    SurveyGenerator generator;
    vector<Survey> surveys;
    vector<UserInfo> userInfo;
    vector<SurveyResponse> responses;
public:
    Admin(){
        username = "";
    }
    Admin(string u);

    void setSurveyName(string surveyName) {
        while (findSurveyName(surveyName) != -1) {
            cout << "Survey name taken, try again: ";
            getline(cin, surveyName);
        }
        generator.setSurveyName(surveyName);
    }

    void createQuestion() {
        generator.createQuestion();
    }

    void displayFoundSurvey(string surveyName) {
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

    void writeSurvey() {
        generator.writeSurvey();
    }

    void setSurveyStatus() {
        generator.setSurveyStatus();
    }

    void readSurveys();
    void readUserResponses();
    void displayAllSurveys();
    void displaySurveyInformation();
    int findSurveyName(string surveyName);
    void readUserInfo();
    void printAllUserInfo();
    void changeUserStatus(string username, bool status);
    void changeUserPassword(string username, string password);
    void writeUserInfoChanges();
    void displayUsersInfo(string usernameSearch);
    void findUsername(string usernameSearch);
    void displayUserInfoMenu();
    Survey getSurvey();
    void displayActiveSurveyInformation();
    void displayAllSurveyResponses();
};

#endif /* ADMIN_H */

