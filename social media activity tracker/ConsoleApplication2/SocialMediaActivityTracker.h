#ifndef SOCIALMEDIAACTIVITYTRACKER_H
#define SOCIALMEDIAACTIVITYTRACKER_H


#include <iostream>
#include "AVLTree.h"  
#include "Activity.h"
#include "UserData.h"  
using namespace std;

class SocialMediaActivityTracker {
private:
    AVLTree<UserData> userTree;
    Activity activity;
public:
    void addUser(const string& userID, const string& username);
    void createActivity(const string& currentUser, int keyActivity);
    void deleteUser(const string& userID, const string& currentUser, const string& mapKey);
    void displayAllUsers();
    void displayUserActivities(const string& currentUser);
    void searchUser(const string& currentUser);
};

void SocialMediaActivityTracker::addUser(const string& userID, const string& username)
{
    UserData* newUser = new UserData;
    newUser->userID = userID;
    newUser->username = username;
    userTree.insert(*newUser, username);
}

void SocialMediaActivityTracker::createActivity(const string& currentUser, int keyActivity)
{
    if (userTree.isEmpty())
    {
        cout << "[*] "
            << "\033[33mNo Users in the database \033[0m" << endl;
        return;
    }
    AVLTreeNode<UserData>* foundTargetUser = userTree.searchNode(currentUser);
    if (foundTargetUser ) {
        string targetUser;  
        AVLTreeNode<UserData>* foundNode = nullptr; 

        switch (keyActivity) {
        case 1:
            foundTargetUser->data.activityQueue.enqueue(activity.createPost(currentUser));
            cout << endl;
            cout << "[*] "
                << "\033[33mPost created successfully! \033[0m" << endl;
            break;
        case 2:
            cout << "[*] "
                << "\033[33mEnter the username of the post owner: \033[0m" ;
            std::getline(std::cin, targetUser);
            foundNode = userTree.searchNode(targetUser);
            if (foundNode && !foundNode->data.activityQueue.isEmpty() )
            {
                string targetPost;
                foundNode->data.activityQueue.displayposts();
                cout << "[*] "
                    << "\033[33mChoose The Post you want to comment on: \033[0m" ;
                std::getline(std::cin, targetPost);
                cout << endl;
                Activity::Post* tempPost = new Activity::Post(targetPost);
                Activity::ActivityData activityData(*tempPost);
                Activity::ActivityData* foundDataPtr = foundNode->data.activityQueue.search(activityData);
                if (foundDataPtr)
                {
                    Activity::ActivityData foundData = *foundDataPtr;
                    foundTargetUser->data.activityQueue.enqueue(activity.createComment(currentUser, targetUser, targetPost));
                    cout << "[*] "
                        << "\033[33mComment Submitted. \033[0m" << endl;
                }
            }
            else {
                cout << "    User Not Found. " << endl;
            }
            break;
        case 3:
            cout << "[*] "
                << "\033[33mEnter the username of the post owner: \033[0m";
            std::getline(std::cin, targetUser);
            foundNode = userTree.searchNode(targetUser);
            if (foundNode && !foundNode->data.activityQueue.isEmpty())
            {
                string targetPost;
                foundNode->data.activityQueue.displayposts();
                cout << "[*] "
                    << "\033[33mChoose The Post you want to react to: \033[0m" ;
                std::getline(std::cin, targetPost);
                cout << endl;
                Activity::Post* tempPost = new Activity::Post(targetPost);
                Activity::ActivityData activityData(*tempPost);
                Activity::ActivityData* foundDataPtr = foundNode->data.activityQueue.search(activityData);
                if (foundDataPtr)
                {
                    Activity::ActivityData foundData = *foundDataPtr;
                    foundTargetUser->data.activityQueue.enqueue(activity.reactToPost(currentUser, targetUser, targetPost));
                    cout << "    Reaction Submitted." << endl;
                }
            }
            else {
                cout << "    User Not Found. " << endl;
            }
            break;
        case 4:
            cout << "[*] "
                << "\033[33mEnter The Username you want to follow: \033[0m" ;
            std::getline(std::cin, targetUser);
            foundNode = userTree.searchNode(targetUser);
            if (foundNode)
            {
                foundTargetUser->data.activityQueue.enqueue(activity.followUser(currentUser, targetUser));
                cout << "    Followed." << endl;
            }
            else {
                cout << "    User Not Found. " << endl;
            }
            break;
        default:
            cout << "[*] "
                << "\033[33minvalid input. \033[0m" << endl;
        }
    }
    else {
        cout << "    User Not Found. " << endl;
    }
}


void SocialMediaActivityTracker::deleteUser(const string& userID, const string& username, const string& mapKey)
{
    if (userTree.isEmpty())
    {
        cout << "[*] "
            << "\033[33mNo Users in the database \033[0m" << endl;
        return;
    }
    UserData userToDelete;
    userToDelete.userID = userID;
    userToDelete.username = username;
    userTree.deleteNode(userToDelete, mapKey);
}

void SocialMediaActivityTracker::displayAllUsers()
{
    if (userTree.isEmpty())
    {
        cout << "[*] "
            << "\033[33mNo Users in the database \033[0m"<<endl;
        return;
    }
    userTree.inOrderTraversal();
}

void SocialMediaActivityTracker::displayUserActivities(const string& username)
{
    if (userTree.isEmpty())
    {
        cout << "[*] "
            << "\033[33mNo Users in the database \033[0m" << endl;
        return;
    }
    AVLTreeNode<UserData>* foundNode = userTree.searchNode(username);
    if (foundNode) {
        cout << "[*] "
            << "\033[33mUser Activities: \033[0m" << endl;
        foundNode->data.activityQueue.display();
        cout << endl;
    }
    else {
        cout << "    User Not Found. " << endl;
    }
}

void SocialMediaActivityTracker::searchUser(const string& username)
{
    if (userTree.isEmpty())
    {
        cout << "[*] "
            << "\033[33mNo Users in the database \033[0m" << endl;
        return;
    }
    AVLTreeNode<UserData>* foundNode = userTree.searchNode(username);
    if (foundNode) {
        cout << "[*] "
            << "\033[33mUser Found : \033[0m" << endl;
        foundNode->data.displayAll();
        cout << endl;
    }
    else {
        cout << "    User Not Found. " << endl;
    }
}
#endif 