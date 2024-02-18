#ifndef USERDATA_H
#define USERDATA_H

#include <iostream>
#include "CircularQueue.h"  
#include "Activity.h"
class UserData {
public:
    std::string userID;
    std::string username;
    CircularQueue<Activity::ActivityData> activityQueue;

    UserData();

    UserData(const UserData& other);

    void displayCredits() ;

    void displayAll() ;

    bool operator==(const UserData& other) ;

    bool operator<(const UserData& other) ;

    bool operator>(const UserData& other) ;
};

UserData::UserData()
{
}

UserData::UserData(const UserData& other) : userID(other.userID), username(other.username) {
    for (int i = 0; i < other.activityQueue.currentSize; ++i) {
        activityQueue.enqueue(*(other.activityQueue.elements[i]));
    }
}

void UserData::displayCredits()  {
    std::cout << "User ID: " << userID << std::endl;
    std::cout << "Username: " << username << std::endl;
}

void UserData::displayAll()  {
    
    cout << "[*] "
        << "\033[33mUser: \033[0m" << endl;
    std::cout << "    User ID: " << userID << std::endl;
    std::cout << "    Username: " << username << std::endl<<endl;
    cout << "[*] "
        << "\033[33mRecent Activities:\n \033[0m";
    activityQueue.display();
    cout << endl;
    cout << "=================================================" << endl;
    
}

bool UserData::operator==(const UserData& other)  {
    return username == other.username && userID == other.userID;
}

bool UserData::operator<(const UserData& other)  {
    return username < other.username;
}

bool UserData::operator>(const UserData& other)  {
    return username > other.username;
}
#endif