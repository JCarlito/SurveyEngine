/* 
 * File:   main.cpp
 * Author: Josh Carlito
 *
 * Created on April 13, 2023, 12:49 PM
 * Purpose: Create a simple survey engine
 * Version: 1, be able to view survey data
 */

#include "SurveyEngine.h"
#include "Admin.h"
#include "Response.h"

int main(int argc, char** argv) {
    int stop = 0;

    Admin admin("test");
    admin.readSurveys();
    admin.readUserResponses();
    admin.displaySurveyData("Test123");
    //    ResponseClass user("test");
    //    user.displaySurveyInformation();
    //    user.getSurvey();
    //    if (!user.surveyTaken()) {
    //        user.takeSurvey();
    //        user.displaySurveyResponse();
    //        user.writeUserResponse();
    //    } else {
    //        cout << "The survey was already taken" << endl;
    //}

    return 0;
}


