#ifndef USERINFOSTRUCT_H
#define USERINFOSTRUCT_H

#include <string>
using namespace std;

const int USERNAME_LENGTH = 12;
const int PASSWORD_LENGTH = 12;

struct UserInfo {
    string username;
    string password;
    bool adminFlag;
};

#endif /* USERINFOSTRUCT_H */