/* 
 * File:   Response.h
 * Author: Josh Carlito
 *
 * Created on April 13, 2023, 4:10 PM
 */

#ifndef RESPONSE_H
#define RESPONSE_H
#include "SurveyEngine.h"
#include "Admin.h"

class ResponseClass {
private:
//    string username;
    SurveyResponse response;
    vector<SurveyResponse> data;
    Survey survey;
    Admin features;
public:

    ResponseClass(string u) {
        response.username = u;
        features.readSurveys();
    }

    void getSurvey() {
        survey = features.getSurvey();
    }

    void displaySurveyInformation() {
        features.displayActiveSurveyInformation();
    }

    void takeSurvey();
    void displaySurveyResponse();
    void writeUserResponse();
    bool surveyTaken();
};

#endif /* RESPONSE_H */

