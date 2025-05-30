#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "../users/users.h"
#include "../tasks/tasks.h"
#include "../../utils/globals.h"


int login(){

    int idUserLogin=-1;

    while(1){

        char username[50];
        char password[50];

        printf("\n=====================================\n\n");
        printf("        INICIAR SESION\n\n");
        printf("=====================================\n");
        printf("Usuario: ");
        scanf("%s", username);

        printf("Contraseña: ");
        scanf("%s", password);

        idUserLogin = searchCredentialsUser(username,password);

        if(idUserLogin != -1){

            printf("\n¡Login exitoso! Bienvenido, %s.\n", username);

            break;
        }
        
        printf("\nAcceso denegado. Usuario o contraseña incorrectos.\n");

    }

    printf("\n\n");

    ID_USER = idUserLogin;

    showMenu();

    return 1;
}

void showMenu() {


    int opcion;

    do {
        printf("\n=====================================\n\n");
        printf("        MENÚ PRINCIPAL\n\n");
        printf("=====================================\n");
        printf(" 1.  Módulo de Usuarios\n");
        printf(" 2.  Módulo de Tareas\n");
        printf(" 3.  Cerrar sesión\n");
        printf("-------------------------------------\n");
        printf("Seleccione una opción (1-3): ");
        scanf("%d", &opcion);


        printf("\n\n\n\n");
        switch(opcion) {
            case 1:

                showMenuUser();
                printf("\n\n\n\n");
            break;
            case 2:
                showMenuTasks();
                printf("\n\n\n\n");
                break;
            case 3:
                printf("Cerrando sesion... Hasta luego.\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while(opcion != 3);
}

