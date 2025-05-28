#pragma once
#include "structs.h"

void getCurrentDate(char *destino, int tam);

void getDataUser(User *user);

void printUser(User user);

int saveDataUser(User user);

int createUser();

void test(User u);
