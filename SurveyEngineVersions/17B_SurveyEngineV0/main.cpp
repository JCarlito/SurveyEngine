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
    ResponseClass user("test");
//    Admin admin("test");
//    admin.readSurveys();
    user.displaySurveyInformation();
    user.getSurvey();
    user.takeSurvey();
    user.displaySurveyResponse();
    
    return 0;
}

