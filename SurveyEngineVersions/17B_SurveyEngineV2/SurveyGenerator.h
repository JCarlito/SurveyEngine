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
    void changeQuestion(){
        int index;
        string newQuestion;
        cout << "Enter the question you'd like to change (1-";
        cout << survey.totalQuestions << "): ";
        cin >> index;
        cin.ignore();
        cout << "Enter your new question: ";
        getline(cin, newQuestion);
        survey.questions[index-1].question = newQuestion;
    }
    void changeAnswer(){
        int questionIndex;
        int answerIndex;
        string newAnswer;
        cout << "Enter the question where the response you'd like to change is (1-";
        cout << survey.totalQuestions << "): ";
        cin >> questionIndex;
        cin.ignore();
        cout << "Enter the answer choice you'd like to change (1-";
        cout << survey.questions[questionIndex-1].answers.size() << "): ";
        cin >> answerIndex;
        cin.ignore();
        cout << "Enter the new answer: ";
        getline(cin, newAnswer);
        survey.questions[questionIndex-1].answers[answerIndex-1] = newAnswer;
    }
    void changeName(){
        string newName;
        cout << "Enter the new survey name: ";
        getline(cin, newName);
        survey.name = newName;
    }
    void viewSurvey();
    void writeSurvey();
};

#endif /* SURVEYGENERATOR_H */

