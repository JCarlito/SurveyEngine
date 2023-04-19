/* 
 * File:   SurveyEngine.h
 * Author: Josh Carlito
 *
 * Created on April 13, 2023, 12:58 PM
 */

#ifndef SURVEYENGINE_H
#define SURVEYENGINE_H
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>
#include <utility>

using namespace std;

const int USERNAME_LENGTH = 12;
const int PASSWORD_LENGTH = 12;

struct UserInfo {
    string username; // User's username
    string password; // User's password
    bool status; // User's account status
    bool adminFlag; // User's admin status
};

struct Question {
    string question; // survey question
    int questionNumber; // question number
    vector<string> answers; // number of proper answers
    bool singleAnswer; // single answer (true) or multiple (false) 
};

struct Survey {
    string name; // name of the survey
    vector<Question> questions; // questions in the survey
    int totalQuestions; // total # of questions
    bool status; // Survey status
};

struct Response {
    string question; // survey question
    int questionNumber; // question number
    vector<string> answers; // survery reponses
};

struct SurveyResponse {
    string username; // user's username
    string name; // name of the survey
    vector<Response> responses; // survey response
};

struct Data {
    string question;
    int questionNumber;
    vector<pair<string, int>> answerData;
    
};

struct SurveyData {
    string name;
    vector<Data> data;
};

#endif /* SURVEYENGINE_H */

