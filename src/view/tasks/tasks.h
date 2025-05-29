#pragma once
#include "structs.h"

void getDataDeleteTask(Task *task);

void getDataUpdateTask(Task *task);

void getDataCreateTask(Task *task);

void printTaskTableHeader();

void printTaskRow(Task task);

void printTask(Task task);

int saveDataTask(Task task);

int createTask();

Task parseTaskFromCSVLine(const char *line);

int showTableTasks();

int updateDataTask(const char *filename, int taskId, const char *new_title, const char *new_description,const int new_status);

int updateTask();

int deleteTask();

void showMenuTasks();
