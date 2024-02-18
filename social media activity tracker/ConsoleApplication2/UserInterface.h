#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <iostream>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include "SocialMediaActivityTracker.h"
using namespace std;
class UserInterface {
public:
    void run() {
        char choice;
        do {
            displayMenu();
            std::cin >> choice;

            switch (choice) {
            case '1':
                addUser();
                break;
            case '2':
                createPost();
                break;
            case '3':
                deleteUser();
                break;
            case '4':
                displayAllUsers();
                break;
            case '5':
                displayUserActivities();
                break;
            case '6':
                searchUser();
                break;
            case '0':
                std::cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != '0');
    }

private:
    SocialMediaActivityTracker tracker;
    void displayMenu() const {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "*****************************************************" << endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "*                                                   *" << endl;
        cout << "*";
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
        cout << "           SOCIAL MEDIA ACTIVITY TRACKER           ";
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "*" << endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "*                                                   *" << endl;
        cout << "*****************************************************" << endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        cout << "\033[33m| 1 |\033[0m" << " Create Account" << endl;
        cout << "\033[33m| 2 |\033[0m" << " Create Post" << endl;
        cout << "\033[33m| 3 |\033[0m" << " Delete User" << endl;
        cout << "\033[33m| 4 |\033[0m" << " Display All Users" << endl;
        cout << "\033[33m| 5 |\033[0m" << " Display User Activities" << endl;
        cout << "\033[33m| 6 |\033[0m" << " Search User" << endl;
        cout << "\033[33m| 0 |\033[0m" << " Exit" << endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        cout << "==========================================" << endl;
        cout << "Type your option : ";
    }

    void CreateMenu()
    {
        int key;
        system("CLS");
        displayHeaderWithTitle("CREATE POST");
        cout << "\033[33m| 1 |\033[0m"
            << " Post" << endl;
        cout << "\033[33m| 2 |\033[0m"
            << " Comment" << endl;
        cout << "\033[33m| 3 |\033[0m"
            << " Reaction" << endl;
        cout << "\033[33m| 4 |\033[0m"
            << " Follow Someone" << endl;
        cout << "\033[33m| 0 |\033[0m"
            << " Return Main" << endl << endl;
        cout << "[*] "
            << "\033[33mChoose The Method You Want To Search With: \033[0m";
        cin >> key;
        cout << "\n\n";

        if (key == 1)
        {
            system("CLS");
            displayHeaderWithTitle("POST");
            std::string username;
            cout << "[*] "
                << "\033[33mEnter Your Account's Username: \033[0m";
            std::cin.ignore();
            std::getline(std::cin, username);
            cout << endl;
            tracker.createActivity(username, 1);
            cout << endl;
            displaySavingAnimation();
            CreateMenu();
        }

        else if (key == 2)
        {
            system("CLS");
            displayHeaderWithTitle("COMMENT");
            std::string username;
            cout << "[*] "
                << "\033[33mEnter Your Account's Username: \033[0m";
            std::cin.ignore();
            std::getline(std::cin, username);
            cout << endl;
            tracker.createActivity(username, 2);
            cout << endl;
            displaySavingAnimation();
            CreateMenu();
        }

        else if (key == 3)
        {
            system("CLS");
            displayHeaderWithTitle("REACTION");
            std::string username;
            cout << "[*] "
                << "\033[33mEnter Your Account's Username: \033[0m";
            std::cin.ignore();
            std::getline(std::cin, username);
            cout << endl;
            tracker.createActivity(username, 3);
            cout << endl;
            displaySavingAnimation();
            CreateMenu();
        }
        else if (key == 4)
        {
            system("CLS");
            displayHeaderWithTitle("FOLLOW");
            std::string username;
            cout << "[*] "
                << "\033[33mEnter Your Account's Username: \033[0m";
            std::cin.ignore();
            std::getline(std::cin, username);
            cout << endl;
            tracker.createActivity(username, 4);
            cout << endl;
            displaySavingAnimation();
            CreateMenu();
        }
        else
        {
            system("CLS");
        }
    }

    void addUser() {
        system("CLS");
        displayHeaderWithTitle("ADD USER");
        std::string userID, username;
        cout << "[*] "
            << "\033[33mEnter Account's User ID: \033[0m";
        cin.ignore();
        getline(cin, userID);
        cout << endl;
        cout << "[*] "
            << "\033[33mEnter Account's Username: \033[0m";
        getline(cin, username);
        tracker.addUser(userID, username);
        cout << endl;
        cout << "[*] "
            << "\033[33mUser added successfully! \033[0m" << endl;
        displaySavingAnimation();
    }

    void createPost() {
        system("CLS");
        CreateMenu();
    }

    void deleteUser() {
        system("CLS");
        displayHeaderWithTitle("DELETE USER");
        std::string userID, username;
        cout << "[*] "
            << "\033[33mEnter Account's User ID: \033[0m";
        cin.ignore();
        getline(cin, userID);
        cout << endl;
        cout << "[*] "
            << "\033[33mEnter Account's Username: \033[0m";
        getline(cin, username);
        cout << endl;
        tracker.deleteUser(userID, username, username);
        cout << endl;
        displaySavingAnimation();
    }

    void displayAllUsers() {
        system("CLS");
        displayHeaderWithTitle("ALL USERS");
        tracker.displayAllUsers();
        waitForEscapeKeyPress();
    }

    void displayUserActivities() {
        system("CLS");
        displayHeaderWithTitle("USER ACTIVITY");
        std::string username;
        cout << "[*] "
            << "\033[33mEnter Account's Username: \033[0m";
        cin.ignore();
        getline(cin, username);
        cout << endl;
        tracker.displayUserActivities(username);
        waitForEscapeKeyPress();
    }

    void searchUser() {
        system("CLS");
        displayHeaderWithTitle("SEARCH USER");
        std::string username;
        cout << "[*] "
            << "\033[33mEnter Account's Username: \033[0m";
        cin.ignore();
        getline(cin, username);
        cout << endl;
        tracker.searchUser(username);
        waitForEscapeKeyPress();
    }

    void displaySavingAnimation()
    {
        cout << endl;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
        cout << "Saving";

        for (int i = 2; i > 0; i--)
        {
            cout << ".";
            Sleep(1000);
        }

        system("CLS");
    }

    void waitForEscapeKeyPress()
    {
        int keyCode;
        cout << endl;
        cout << "[*] "
             << "\033[33mPress Esc to return back to the main screen. \033[0m";

        do
        {
            keyCode = _getch();
            if (keyCode == 27)
            {
                system("CLS");
                Sleep(1000);
            }
        } while (keyCode != 27);
    }

    void displayHeaderWithTitle(const string& title)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << setw(50) << setfill('*') << "" << endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
        cout << setw(27) << setfill(' ') << title << endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << setw(50) << setfill('*') << "" << endl;
        cout << endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    }

};
#endif

