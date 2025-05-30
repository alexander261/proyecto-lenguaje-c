#pragma once
#include "structs.h"

User * generateArrayUsers(int n);

User * updateZiseArrayUsers(User * user,int n);

void getDataDeleteUser(User *user);

void getDataUpdateUser(User *user);

void getDataCreateUser(User *user);

void printUserTableHeader();

void printUserRow(User user);

void printUser(User user);

int saveDataUser(User user);

int createUser();

User parseUserFromCSVLine(const char *line);

UserArray getUsers();

int showTableUsers();

int searchCredentialsUser(char * username,char * password);

int updateDataUser(const char *filename, int userId, const char *new_name, const char *new_last_name,const char * new_password,const int new_status);

int updateUser();

int deleteUser();

void showMenuUser();