#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "users.h"
#include "../../utils/utils.h"


void getDataUser(User *user){

    printf("Introduce tu nombre: ");
    scanf("%49s", user->name);

    printf("Introduce tu apellido: ");
    scanf("%49s", user->last_name);

    printf("Introduce tu nombre de usuario: ");
    scanf("%49s", user->username);

    user->status=1;
    user->id=5;

    strcpy(user->soft_delete,"");

    getCurrentDate(user->create_at, sizeof(user->create_at));

}


void printUser(User user){

    printf("ID: %d\n", user.id);
    printf("Username: %s\n", user.username);
    printf("Nombre: %s\n", user.name);
    printf("Apellido: %s\n", user.last_name);
    printf("Fecha y hora de registro: %s\n", user.create_at);
    printf("Fecha Delete: %s\n", user.soft_delete);

}


int saveDataUser(User user){
 
    FILE *archivo = fopen("bdd/users.csv", "a");
 
    if (archivo == NULL) {
        return 0;
    }

    fprintf(archivo, "%d,%s,%s,%s,%d,%s,%s\n",
        user.id,
        user.username,
        user.name,
        user.last_name,
        user.status,
        user.create_at,
        user.soft_delete
    );

    fclose(archivo);

    return 1;
}

int createUser(){


    User user;

    getDataUser(&user);

    int statusCreate = saveDataUser(user);

    if(!statusCreate){

        printf("No se pudo guardar el usuario.\n");
        
        return statusCreate;
    }



    printf("Usuario guardado correctamente.\n");

    printUser(user);

    return statusCreate;
}

User parseUserFromCSVLine(const char *line) {
    
    User user;
    char tempLine[1024];
    strcpy(tempLine, line); 

    char *token = strtok(tempLine, ",");

    user.id = atoi(token); // id

    token = strtok(NULL, ",");
    strcpy(user.username, token); // username

    token = strtok(NULL, ",");
    strcpy(user.name, token); // name

    token = strtok(NULL, ",");
    strcpy(user.last_name, token); // last_name

    token = strtok(NULL, ",");
    user.status = atoi(token); // status

    token = strtok(NULL, ",");
    strcpy(user.create_at, token); // create_at

    // Elimina el salto de línea
    size_t len = strlen(user.create_at);
    if (len > 0 && user.create_at[len - 1] == '\n') {
        user.create_at[len - 1] = '\0';
    }

    return user;
}



void showMenuUser() {
    int opcion;

    do {
        printf("\n=== MODULO DE USUARIOS ===\n");
        printf("1. Crear usuario\n");
        printf("2. Eliminar usuario\n");
        printf("3. Actualizar usuario\n");
        printf("4. Regresar\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                // crearUsuario();
                break;
            case 2:
                // eliminarUsuario();
                break;
            case 3:
                // actualizarUsuario();
                break;
            case 4:
                printf("Regresando al menu principal...\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while(opcion != 4);
}

void test2(){

        char line[1024];
    if (readLineFromFile("bdd/users.csv", 2, line)) {
        User user = parseUserFromCSVLine(line);
        printf("ID: %d\n", user.id);
        printf("Username: %s\n", user.username);
        printf("Name: %s %s\n", user.name, user.last_name);
        printf("Status: %d\n", user.status);
        printf("Created at: %s\n", user.create_at);
    }

    int id = getLastId("bdd/constants.txt", "last_id_user");

    if (id != -1) {

        int newId = id + 1;

        // Usas newId para crear el nuevo usuario

        updateLastId("bdd/constants.txt", "last_id_user", newId);

    }
}
void test(User user) {

    showMenuUser();
    // createUser();
    
    // printf("ID: %d\n", user.id);
    
    // printf("user: %s\n", user.username);

}
