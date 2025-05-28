#pragma once

int getLastId(const char *filename, const char *key);

int updateLastId(const char *filename, const char *key, int newId);

int readLineFromFile(const char *filename, int lineNumber, char *resultLine);

void getCurrentDate(char *destino, int tam);