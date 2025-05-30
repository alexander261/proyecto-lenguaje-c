#pragma once
#include "structs.h"

Task * generateArrayTask(int n);

Task * updateZiseArrayTask(Task * task,int n);

void getDataStatusTask(Task *task);

void getDataDeleteTask(Task *task);

void getDataUpdateTask(Task *task);

void getDataCreateTask(Task *task);

void printTaskTableHeader();

void printTaskRow(Task task);

void printTask(Task task);

int saveDataTask(Task task);

int createTask();

Task parseTaskFromCSVLine(const char *line);

TaskArray getTasks();

int showTableTasks();

int updateDataTask(const char *filename, int taskId, const char *new_title, const char *new_description,const int new_status,const char * new_soft_delete);

int updateTask();

int statusTask();

void showMenuTasks();
