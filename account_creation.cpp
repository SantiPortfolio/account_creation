#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <fstream>
#include <cstdio>
#include <termios.h>
#include <cstdlib>
#include "encode.cpp"

using namespace std;
string username_textFile = "usernames.txt";
string password_textFile = "passwords.txt";
int key = rand() % 100;

string username_check(string username, int min, int max)
{
    bool used=false;
    while(true)
    {
        cout<<"\nInput the name of the account. Min " + to_string(min) + " characters Max " + to_string(max) + " characters. \n";
        cin>>username;
        if(username.length()<min)
        {
            cout<<"\nPlease enter a username with at least " + to_string(min) + " characters. \n";
        }
        else if(username.length()>max)
        {
            cout<<"\nPlease enter a username with " + to_string(max) + " characters ors less. \n";
        }
        else
        {
            used = false;
            string used_Usernames;
            fstream accounts(username_textFile, ios::app);
            ifstream read(username_textFile);
            while(getline (read, used_Usernames))
            {
                if(used_Usernames==username)
                {
                    cout<<"\nError: Username already in use";
                    used = true;
                }
            }
            if(used==false)
            {    
                accounts<<"\n"<<username;
                accounts.close();
                read.close();
                break;
            }
        }
    }
    cout<<"Username Accepted\n";
    return username;
}

string password_check(int min, int max)
{
    string password;
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    bool used = false;
    while(true)
    {
        used = false;
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        cout<<"\nInput the password for the account. Min " + to_string(min) + " characters Max " + to_string(max) + " characters. \n";
        cin>>password;
        if(password.length()<min)
        {
            cout<<"\nPlease enter a password with at least " + to_string(min) + " characters. \n";
        }
        else if(password.length()>max)
        {
            cout<<"\nPlease enter a password with " + to_string(max) + " characters or less. \n";
        }
        else
        {
            password = encoder(password, key);
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            string used_Passwords;
                fstream accounts(password_textFile, ios::app);
                ifstream read(password_textFile);
                while(getline (read, used_Passwords))
                {
                    if (used_Passwords==password)
                    {
                        cout<<"\nError: Password already in use";
                        used = true;
                    }
                }
                accounts.close();
                read.close();
            if(used!=true) break;
        }
    }
    cout<<"Password Accepted\n";
    return password;
}

void user_accounts()
{
    int min = 5;
    int max = 12;
    string username, password;
    
    username = username_check(username, min, max);
    password = password_check(min, max);
    fstream accounts(password_textFile, ios::app);
    accounts<<"\n"<<password;
    accounts.close();
}

bool login_check(string username, string password)
{
    bool username_correct = false;
    int password_line = 0;
    bool logged = false;
    string checked_Usernames;
    ifstream read(username_textFile);
    while(getline (read, checked_Usernames))
    {
        if(username==checked_Usernames)
        {
            username_correct = true;
            break;
        }
        password_line++;
    }
    while(username_correct)
    {
        string checked_Passwords;
        ifstream read(password_textFile);
        for (int i=0; i<password_line+1; i++)
        {   
            getline (read, checked_Passwords);
            if (password!=checked_Passwords)
            {
                logged = false;
            }
            else
            {
                logged = true;
                break;
            }
        }
        break;
    }
    return logged;
}

string login()
{
    string booltemp;
    bool logged_in;
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    int min = 5;
    int max = 12;
    string username, password;
    while(true)
    {
        cout<<"\nInput the name of the account: \n";
        cin>>username;
        if(username.length()<min)
        {
            cout<<"\nPlease enter a username with at least " + to_string(min) + " characters: ";
        }
        else if(username.length()>max)
        {
            cout<<"\nPlease enter a username with " + to_string(max) + " characters ors less: ";
        }
        else
        {
            while(true)
            {
                tcsetattr(STDIN_FILENO, TCSANOW, &newt);
                cout<<"\nInput the password for the account: ";
                cin>>password;
                if(username.length()<min)
                {
                    cout<<"\nPlease enter a password with at least " + to_string(min) + " characters: ";
                }
                else if(username.length()>max)
                {
                    cout<<"\nPlease enter a password with " + to_string(max) + " characters or less: ";
                }
                else
                {
                    break;
                }
            }
            password = encoder(password, key);
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            logged_in = login_check(username, password);

            if(logged_in==true)
            {
                cout<<"\nSuccessful Loggin\n";
                break;
            }
            else 
            {
                cout<<"\nLoggin failed.";
            }
        }
    }
    return username;
}

void password_Change(string username)
{
    int min = 5;
    int max = 12;
    int lines = 0;
    string usernames;
    ifstream read(username_textFile);
    while(getline(read, usernames))
    {
        if(usernames==username)
        {
            break;
        }
        else lines++;
    }
    read.close();
    int integer = 0;
    string temp;
    read.open(username_textFile);
    while(getline(read,temp))
    {
        integer++;
    }
    read.close();
    ifstream password_FileRead;
    password_FileRead.open(password_textFile);
    string passwordtxt_Contents[50];
    if(password_FileRead.is_open())
    {
        for (int i=0; i<=integer+1;i++)
        {
            password_FileRead>>passwordtxt_Contents[i];
        }
    }
    integer = integer + 2;
    remove("passwords.txt");
    fstream password_FileWrite(password_textFile, ios::app);
    string password = password_check(min, max);
    for(int i = 0;i<lines;i++)
    {
        password_FileWrite<<passwordtxt_Contents[i]<< endl;
    }
    password_FileWrite<<password<<"\n";
    password_FileRead.close();
    for(int i=0;i<=integer;i++)
    {
        if(i<lines)
        {

        }
        else password_FileWrite<<passwordtxt_Contents[i+1]<<"\n";
    }
    return;
}

int admin_commands(string username)
{
    int command,exit;
    fstream username_file, password_file;
    while(true)
    {
        cout<<"\nCommands:\nWipe Data(1)\nChange Password(2)\nLoggout and Exit(3)\nLoggout(4)\n";
        cin>>command;
        if(command==1)
        {
            remove("passwords.txt");
            remove("usernames.txt");
            fstream username_file(username_textFile, ios::out);
            fstream password_file(password_textFile, ios::out);
            username_file<<"Usernames:\nadmin";
            string password = encoder("Niamh031218!", key);
            password_file<<"Passwords:\n"<<password;
        }
        if(command==2)
        {
            password_Change(username);
        }
        if(command==3)
        {
            break;
        }
        else if(command==4)
        {
            break;
        }
        else
        {
            cout<<"\nError: Invalid Input ";
        }
    }
    return command;
}

int commands(string username)
{
    int command;
    while(true)
    {
        cout<<"\nCommands:\nChange Password(1)\nLoggout(2)\nLoggout and Exit(3)\n";
        cin>>command;
        if(command==1)
        {
            password_Change(username);
        }
        else if(command==2)
        {
            break;
        }
        else if(command==3)
        {
            break;
        }
    }
    return command;
}

int main()
{
    cout<<key;
    while(true)
    {
        int exit = 0;
        bool logged = false;
        string account_creation, username;
        cout<<"\nWould you like to sign-up(1), log-in(2), or exit(3)?: ";
        while (true)
        {
            cin>>account_creation;
            if(account_creation.length()>1)
            {
                cout<<"\nError: Please Enter 1 or 2 only.: ";
            }
            else if(sizeof(account_creation)<1)
            {
                cout<<"\nError: Please Enter The Character 1 or 2: ";
            }
            else
            {
                if(account_creation=="1")
                {
                    user_accounts();
                    break;
                }
                else if(account_creation=="2")
                {
                    username = login();
                    logged = true;
                    break;
                }
                else if(account_creation=="3")
                {
                    return 0;
                }
                else cout<<"\nError: Please Enter Y or N only: ";
            }
        }

        if(logged==false)
        {    
            cout<<"\nWould you like to log-in(1) or to exit(2)?: ";
            while(true)
            {
                cin>>account_creation;
                transform(account_creation.begin(), account_creation.end(), account_creation.begin(), ::toupper);
                if(account_creation.length()>1)
                {
                    cout<<"\nError: Please Enter 1 or 2 only.: ";
                }
                else if(sizeof(account_creation)<1)
                {
                    cout<<"\nError: Please Enter The Character 1 or 2: ";
                }
                else
                {
                    if(account_creation=="1")
                    {
                        username = login();
                        logged = true;
                        break;
                    }
                    else if(account_creation=="2")
                    {
                        return 0;
                    }
                    else cout<<"\nError: Please Enter Y or N only: ";
                }
            }
        }
        if(username=="0")
        return 0;
        if(username=="admin")
        {
            exit = admin_commands(username);
        }
        else
        {
            exit = commands(username);
        }

        if(exit==3)
        {
            return 0;
        }
    }
    cout<<"\nExiting...\n";
    return 0;
}
