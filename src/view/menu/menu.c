#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "../users/users.h"
#include "../tasks/tasks.h"

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

        switch(opcion) {
            case 1:
                showMenuUser();
            break;
            case 2:
                showMenuTasks();
                break;
            case 3:
                printf("Cerrando sesion... Hasta luego.\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while(opcion != 3);
}

