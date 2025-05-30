#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "users.h"
#include "../../utils/utils.h"

#define MAX_LINE 1024


User * generateArrayUsers(int n){
    return malloc(n * sizeof(User));
}


User * updateZiseArrayUsers(User * user,int n){
    return realloc(user,n * sizeof(User));
}

void getDataDeleteUser(User *user){

    printf("Introduce el ID del usuario a desactivar: ");
    scanf("%d", &user->id);

}

void getDataUpdateUser(User *user){

    printf("Introduce el ID del usuario a actualizar: ");
    scanf("%d", &user->id);

    printf("Introduce el nuevo nombre: ");
    scanf("%49s", user->name);

    printf("Introduce el nuevo apellido: ");
    scanf("%49s", user->last_name);


    printf("Introduce tu nueva contrasenia: ");
    scanf("%49s", user->password);

}

void getDataCreateUser(User *user){

    int id = getLastId("bdd/constants.txt", "last_id_user");

    user->id = id;

    printf("Introduce tu nombre: ");
    scanf("%49s", user->name);

    printf("Introduce tu apellido: ");
    scanf("%49s", user->last_name);

    printf("Introduce tu usuario: ");
    scanf("%49s", user->username);

    printf("Introduce tu contrasenia: ");
    scanf("%49s", user->password);

    user->status=1;

    strcpy(user->soft_delete,"");

    getCurrentDate(user->create_at, sizeof(user->create_at));

}

void printUserTableHeader() {
    printf("\n| %-3s | %-15s | %-15s | %-15s | %-8s | %-19s | %-19s |\n",
           "ID", "Username", "Nombre", "Apellido", "Estado", "Creado", "Eliminado");
    printf("|%s|\n", "-----|-----------------|-----------------|-----------------|----------|---------------------|---------------------");
}

void printUserRow(User user) {
    
    printf("| %-3d | %-15s | %-15s | %-15s | %-8s | %-19s | %-19s |\n",
        user.id,
        user.username,
        user.name,
        user.last_name,
        (user.status == 1) ? "Activo" : "Inactivo",
        user.create_at,
        user.soft_delete
    );
}

void printUser(User user) {
    printf("\n=====================================\n");
    printf("     INFORMACIÓN DEL USUARIO\n");
    printf("=====================================\n");
    printf("  ID del Usuario       : %d\n", user.id);
    printf("  Nombre de Usuario    : %s\n", user.username);
    printf("  Nombre               : %s\n", user.name);
    printf("  Apellido             : %s\n", user.last_name);
    printf("  Registrado en        : %s\n", user.create_at);
    printf("  Fecha de Eliminación: %s\n", user.soft_delete);
    printf("=====================================\n");
}

int saveDataUser(User user){
 
    FILE *archivo = fopen("bdd/users.csv", "a");
 
    if (archivo == NULL) {
        return 0;
    }

    fprintf(archivo, "%d,%s,%s,%s,%s,%d,%s,%s\n",
        user.id,
        user.username,
        user.password,
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

    getDataCreateUser(&user);

    int statusCreate = saveDataUser(user);

    if(!statusCreate){

        printf("No se pudo guardar el usuario.\n");
        
        return statusCreate;
    }

    int id = getLastId("bdd/constants.txt", "last_id_user");

    updateLastId("bdd/constants.txt", "last_id_user", id + 1);

    printf("\nUSUARIO CREADO CORRECTAMENTE.\n");

    printUser(user);

    return statusCreate;
}

User parseUserFromCSVLine(const char *line) {
    
    User user;
    char tempLine[MAX_LINE];
    strcpy(tempLine, line); 

    char *token = strtok(tempLine, ",");

    user.id = atoi(token); // id

    token = strtok(NULL, ",");
    strcpy(user.username, token); // username


    token = strtok(NULL, ",");
    strcpy(user.password, token); // password

    token = strtok(NULL, ",");
    strcpy(user.name, token); // name

    token = strtok(NULL, ",");
    strcpy(user.last_name, token); // last_name

    token = strtok(NULL, ",");
    user.status = atoi(token); // status

    token = strtok(NULL, ",");
    strcpy(user.create_at, token); // create_at


    token = strtok(NULL, ",");
    strcpy(user.soft_delete, token); // soft_delete

    // Eliminamoss el salto de linea
    size_t len = strlen(user.soft_delete);
    if (len > 0 && user.soft_delete[len - 1] == '\n') {
        user.soft_delete[len - 1] = '\0';
    }

    return user;
}


UserArray getUsers(){

    int maxID = getLastId("bdd/constants.txt", "last_id_user");
    
    UserArray users;

    users.length = 0;
    users.array = generateArrayUsers(users.length);

    for(int row=1; row < maxID; row++){

        char line[MAX_LINE];
    
        if (readLineFromFile("bdd/users.csv", row, line)) {

            users.array = updateZiseArrayUsers(users.array,users.length + 1);
            users.array[users.length] = parseUserFromCSVLine(line);
            users.length++;
        
        }

    }

    return users;
}


int showTableUsers(){

    UserArray users = getUsers();

    printf("\n\nTABLA DE USUARIOS\n");

    printUserTableHeader();

    for(int row = 0; row < users.length; row++){

        printUserRow(users.array[row]);

    }

    printf("\n\n");

    free(users.array);

    return 1;
}

int searchCredentialsUser(char * username,char * password){

    int maxID = getLastId("bdd/constants.txt", "last_id_user");

    int ID=-1;

    for(int row=1; row < maxID; row++){

        char line[MAX_LINE];
    
        if (readLineFromFile("bdd/users.csv", row, line)) {
            User user = parseUserFromCSVLine(line);

            
            if (!strcmp(user.username, username) && 
                !strcmp(user.password, password) && 
                user.status == 1 
            ) {

                ID = user.id;

            }
            
        }

    }

    return ID;
}


int updateDataUser(const char *filename, int userId, const char *new_name, const char *new_last_name,const char * new_password,const int new_status) {
    
    FILE *file = fopen(filename, "r");
    
    FILE *tempFile = fopen("bdd/temp_users.csv", "w");

     
    if (file == NULL || tempFile == NULL) {
        return 0;
    }

    char line[MAX_LINE];
    int updated = 0;

    while (fgets(line, sizeof(line), file)) {
        User user = parseUserFromCSVLine(line);

        if (user.id == userId) {

            strncpy(user.name, new_name, sizeof(user.name));

            strncpy(user.last_name, new_last_name, sizeof(user.last_name));


            strncpy(user.password, new_password, sizeof(user.password));
            
            user.status = new_status;

            fprintf(tempFile, "%d,%s,%s,%s,%s,%d,%s,%s\n",
                user.id,
                user.username,
                user.password,
                user.name,
                user.last_name,
                user.status,
                user.create_at,
                user.soft_delete
            );

            updated = 1;

        } else {

            fputs(line, tempFile);

        }
    }

    fclose(file);
    fclose(tempFile);

    remove(filename);
    rename("bdd/temp_users.csv", filename);

    return updated;
}

int updateUser(){

    showTableUsers();

    User user;

    getDataUpdateUser(&user);

    int resultado = updateDataUser("bdd/users.csv", user.id, user.name, user.last_name,user.password,1);

    if (!resultado) {
        printf("\nNO SE ENCONTRO EL USUARIO A ACTUALIZAR.\n");

        return 0;
    }

    printf("\nUSUARIO ACTUALIZADO CORRECTAMENTE.\n");
    return 1;
}

int deleteUser(){

    showTableUsers();

    User user;

    getDataDeleteUser(&user);

    char line[MAX_LINE];    

    if (!readLineFromFile("bdd/users.csv", user.id, line)) {

        printf("\nNO SE ENCONTRO EL USUARIO A DESACTIVAR.\n");

        return 0;
    }

    User userBDD = parseUserFromCSVLine(line);


    int resultado = updateDataUser("bdd/users.csv", user.id, userBDD.name, userBDD.last_name,userBDD.password,0);

    if (!resultado) {
        printf("\nNO SE ENCONTRO EL USUARIO A DESACTIVAR.\n");

        return 0;
    }

    printf("\nUSUARIO DESACTIVADO CORRECTAMENTE.\n");

    return 1;
}

void showMenuUser() {
    int opcion;

    do {
        printf("\n=====================================\n\n");
        printf("   MÓDULO DE GESTIÓN DE USUARIOS\n\n");
        printf("=====================================\n");
        printf(" 1.  Ver todos los usuarios\n");
        printf(" 2.  Crear nuevo usuario\n");
        printf(" 3.  Actualizar datos de usuario\n");
        printf(" 4.  Desactivar un usuario\n");
        printf(" 5.  Volver al menú principal\n");
        printf("-------------------------------------\n");
        printf("Seleccione una opción (1-5): ");

        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                showTableUsers();
                break;
            case 2:
                createUser();
                break;
            case 3:
                updateUser();
                break;
            case 4:
                deleteUser();
                break;
            case 5:
                printf("Regresando al menu principal...\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while(opcion != 5);
}