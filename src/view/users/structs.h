#pragma once

typedef struct {
    int id;
    char username[50];
    char name[50];
    char last_name[50];
    int status;
    char create_at[20];
    char soft_delete[20];
} User;
