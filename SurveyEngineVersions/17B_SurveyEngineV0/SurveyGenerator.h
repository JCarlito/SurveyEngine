/* 
 * File:   SurveyGenerator.h
 * Author: Josh Carlito
 *
 * Created on April 13, 2023, 1:05 PM
 */

#ifndef SURVEYGENERATOR_H
#define SURVEYGENERATOR_H
#include "SurveyEngine.h"

class SurveyGenerator {
private:
    Survey survey;
    int number = 0;
public:
    void setSurveyStatus();
    void setSurveyName(string surveyName);
    void createQuestion();
    void viewSurvey();
    void writeSurvey();
};

#endif /* SURVEYGENERATOR_H */

