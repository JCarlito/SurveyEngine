/* 
 * File:   UserInfoStruct.h
 * Author: Josh Carlito
 *
 * Created on March 20, 2023, 8:25 PM
 */

#ifndef USERINFOSTRUCT_H
#define USERINFOSTRUCT_H
const unsigned char USERNAME_LENGTH = 13;
const unsigned char PASSWORD_LENGTH = 13;

struct UserInfo {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    bool adminFlag;
};



#endif /* USERINFOSTRUCT_H */

