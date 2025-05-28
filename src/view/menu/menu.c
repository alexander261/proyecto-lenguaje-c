#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

void showMenu() {
    int opcion;

    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Modulo de Usuarios\n");
        printf("2. Modulo de Productos\n");
        printf("3. Cerrar sesion\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                // mostrarMenuUsuarios();
                break;
            case 2:
                // mostrarMenuProductos();
                break;
            case 3:
                printf("Cerrando sesion... Hasta luego.\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while(opcion != 3);
}

// void mostrarMenuUsuarios() {
//     int opcion;

//     do {
//         printf("\n--- MODULO DE USUARIOS ---\n");
//         printf("1. Crear usuario\n");
//         printf("2. Eliminar usuario\n");
//         printf("3. Actualizar usuario\n");
//         printf("4. Regresar\n");
//         printf("Seleccione una opcion: ");
//         scanf("%d", &opcion);

//         switch(opcion) {
//             case 1:
//                 crearUsuario();
//                 break;
//             case 2:
//                 eliminarUsuario();
//                 break;
//             case 3:
//                 actualizarUsuario();
//                 break;
//             case 4:
//                 printf("Regresando al menu principal...\n");
//                 break;
//             default:
//                 printf("Opcion invalida. Intente de nuevo.\n");
//         }
//     } while(opcion != 4);
// }

// void mostrarMenuProductos() {
//     int opcion;

//     do {
//         printf("\n--- MODULO DE PRODUCTOS ---\n");
//         printf("1. Agregar producto (pendiente)\n");
//         printf("2. Eliminar producto (pendiente)\n");
//         printf("3. Regresar\n");
//         printf("Seleccione una opcion: ");
//         scanf("%d", &opcion);

//         switch(opcion) {
//             case 1:
//             case 2:
//                 printf(">> Esta funcionalidad aún no está implementada.\n");
//                 break;
//             case 3:
//                 printf("Regresando al menu principal...\n");
//                 break;
//             default:
//                 printf("Opcion invalida. Intente de nuevo.\n");
//         }
//     } while(opcion != 3);
// }
