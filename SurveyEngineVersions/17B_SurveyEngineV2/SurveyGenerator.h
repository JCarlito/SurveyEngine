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

    SurveyGenerator() {
        survey.name = "";
        survey.questions.clear();
        survey.totalQuestions = 0;
        survey.status = 0;
    }
    void setSurveyStatus();
    void setSurveyName(string surveyName);

    void clearSurvey() {
        survey.name = "";
        survey.questions.clear();
        survey.totalQuestions = 0;
        survey.status = 0;
        number = 0;
    }
    void createQuestion();
    void viewSurvey();
    void writeSurvey();
};

#endif /* SURVEYGENERATOR_H */

