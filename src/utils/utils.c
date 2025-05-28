#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"


int getLastId(const char *filename, const char *key) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }

    char line[256];
    char searchKey[100];
    sprintf(searchKey, "%s:", key);

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, searchKey, strlen(searchKey)) == 0) {
            int value = atoi(line + strlen(searchKey));
            fclose(file);
            return value;
        }
    }

    fclose(file);
    return -1;
}

int updateLastId(const char *filename, const char *key, int newId) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 0; // Error
    }

    // Cargamos todo en memoria
    char lines[20][256]; // suponiendo como máximo 20 constantes
    int lineCount = 0;
    char searchKey[100];
    sprintf(searchKey, "%s:", key);

    while (fgets(lines[lineCount], sizeof(lines[0]), file)) {
        if (strncmp(lines[lineCount], searchKey, strlen(searchKey)) == 0) {
            sprintf(lines[lineCount], "%s%d;\n", searchKey, newId);
        }
        lineCount++;
    }

    fclose(file);

    // Escribimos el archivo actualizado
    file = fopen(filename, "w");
    if (file == NULL) {
        return 0;
    }

    for (int i = 0; i < lineCount; i++) {
        fputs(lines[i], file);
    }

    fclose(file);
    return 1;
}

int readLineFromFile(const char *filename, int lineNumber, char *resultLine) {
    
    int MAX_LINE=1024;

    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
        return 0;
    }

    char buffer[MAX_LINE];
    int currentLine = 1;

    while (fgets(buffer, MAX_LINE, file) != NULL) {
        
        if (currentLine == lineNumber) {
            strcpy(resultLine, buffer);
            fclose(file);
            return 1;
        }

        currentLine++;
    }

    fclose(file);
    return 0; // Línea no encontrada
}

void getCurrentDate(char *destino, int tam) {
    time_t t;
    struct tm *tm_info;

    time(&t);
    tm_info = localtime(&t);

    strftime(destino, tam, "%Y-%m-%d %H:%M:%S", tm_info);
}
