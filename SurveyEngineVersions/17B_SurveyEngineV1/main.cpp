/* 
 * File:   main.cpp
 * Author: Josh Carlito
 *
 * Created on April 13, 2023, 12:49 PM
 * Purpose: Create a simple survey engine
 */

#include "SurveyEngine.h"
#include "Admin.h"
#include "Response.h"

int main(int argc, char** argv) {
    int stop = 0;
//    ResponseClass user("jcar");
        Admin admin("test");
        admin.readUserResponses();
        admin.displayAllSurveyResponses();
//        admin.readSurveys();
//    user.displaySurveyInformation();
//    user.getSurvey();
//    if (!user.surveyTaken()) {
//        user.takeSurvey();
//        user.displaySurveyResponse();
//        user.writeUserResponse();
//    } else {
//        cout << "The survey was already taken" << endl;
//    }

    return 0;
}


