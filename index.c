#include <stdio.h>
#include "src/view/users/users.h"
#include "src/view/menu/menu.h"


// 

/*

gcc index.c src/view/users/users.c src/view/tasks/tasks.c src/view/menu/menu.c src/utils/utils.c -o index && ./index

gcc -Wall -Wextra -pedantic index.c src/view/users/users.c src/view/tasks/tasks.c src/view/menu/menu.c src/utils/utils.c src/utils/globals.c -o index && ./index


PENDIENTES:

MOSTRAS SOLO LOS DATOS DEL USUARIO
AGREGAR MEMORIA DINAMICA
AGREGAR USUARIO SUPERADMIN

*/

int main() {

    login();

    return 0;
}
