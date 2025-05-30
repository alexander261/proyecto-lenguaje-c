#pragma once

typedef struct {
    int id;
    int id_user;
    char title[50];
    char description[255];
    int status;
    char create_at[20];
    char soft_delete[20];
} Task;

typedef struct {
    Task * array;
    int length;
} TaskArray;