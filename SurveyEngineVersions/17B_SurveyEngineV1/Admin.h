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
    SurveyData data;
    vector<Survey> surveys;
    vector<UserInfo> userInfo;
    vector<SurveyResponse> responses;
    int findTargetData(const vector<pair<string, int>>&answerData,
            const string& answer);
public:

    Admin() {
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

    void writeSurvey() {
        generator.writeSurvey();
    }

    void setSurveyStatus() {
        generator.setSurveyStatus();
    }

    void fillSurveyData(const string& surveyName);
    void displaySurveyData(const string& surveyName);
    void displaySpecificSurveyResponse(string u);
    void displayResponsesOverview();
    void displayFoundSurvey(string surveyName);
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

