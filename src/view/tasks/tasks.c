#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tasks.h"
#include "../../utils/utils.h"

#define MAX_LINE 1024


void getDataDeleteTask(Task *task){

    printf("Introduce el ID de la tarea a terminar: ");
    scanf("%d", &task->id);

}

void getDataUpdateTask(Task *task){

    printf("Introduce el ID de la tarea a actualizar: ");
    scanf("%d", &task->id);

    printf("Introduce el nuevo titulo: ");
    scanf("%49s", task->title);

    printf("Introduce la nueva descripcion: ");
    scanf("%254s", task->description);

}

void getDataCreateTask(Task *task){

    int id = getLastId("bdd/constants.txt", "last_id_task");

    task->id = id;

    printf("Introduce el titulo de la tarea: ");
    scanf("%49s", task->title);

    printf("Introduce la descripcion: ");
    scanf("%254s", task->description);


    task->status=1;

    strcpy(task->soft_delete,"");

    getCurrentDate(task->create_at, sizeof(task->create_at));

}

void printTaskTableHeader() {
    printf("\n| %-3s | %-7s | %-20s | %-30s | %-8s | %-19s | %-19s |\n",
           "ID", "UserID", "Titulo", "Descripcion", "Estado", "Creado", "Eliminado");
    printf("|%s|\n", "-----|---------|----------------------|--------------------------------|----------|---------------------|---------------------");
}

void printTaskRow(Task task) {
    printf("| %-3d | %-7d | %-20s | %-30s | %-8s | %-19s | %-19s |\n",
           task.id,
           task.id_user,
           task.title,
           task.description,
           (task.status == 1) ? "Pendiente" : "Terminado",
           task.create_at,
           task.soft_delete
    );
}

void printTask(Task task) {
    printf("\n=====================================\n");
    printf("         INFORMACIÓN DE LA TAREA\n");
    printf("=====================================\n");
    printf("  ID de la Tarea       : %d\n", task.id);
    printf("  ID del Usuario       : %d\n", task.id_user);
    printf("  Título               : %s\n", task.title);
    printf("  Descripción          : %s\n", task.description);
    printf("  Estado               : %s\n", (task.status == 1) ? "Pendiente" : "Terminado");
    printf("  Fecha de Creación    : %s\n", task.create_at);
    printf("  Fecha de Eliminación : %s\n", task.soft_delete);
    printf("=====================================\n");
}

int saveDataTask(Task task){
 
    FILE *archivo = fopen("bdd/tasks.csv", "a");
 
    if (archivo == NULL) {
        return 0;
    }

    fprintf(archivo, "%d,%d,%s,%s,%d,%s,%s\n",
        task.id,
        task.id_user,
        task.title,
        task.description,
        task.status,
        task.create_at,
        task.soft_delete
    );

    fclose(archivo);

    return 1;
}

int createTask(){

    Task task;

    getDataCreateTask(&task);

    int statusCreate = saveDataTask(task);

    if(!statusCreate){

        printf("No se pudo guardar la tarea.\n");
        
        return statusCreate;
    }

    int id = getLastId("bdd/constants.txt", "last_id_task");

    updateLastId("bdd/constants.txt", "last_id_task", id + 1);

    printf("\nTAREA CREADA CORRECTAMENTE.\n");

    printTask(task);

    return statusCreate;
}

Task parseTaskFromCSVLine(const char *line) {
    
    Task task;
    char tempLine[MAX_LINE]; 
    strcpy(tempLine, line);

    char *token = strtok(tempLine, ",");

    task.id = atoi(token); // id

    token = strtok(NULL, ",");
    task.id_user = atoi(token); // id_user

    token = strtok(NULL, ",");
    strcpy(task.title, token); // title

    token = strtok(NULL, ",");
    strcpy(task.description, token); // description

    token = strtok(NULL, ",");
    task.status = atoi(token); // status

    token = strtok(NULL, ",");
    strcpy(task.create_at, token); // create_at

    token = strtok(NULL, ",");
    strcpy(task.soft_delete, token); // soft_delete

    // Eliminamoss el salto de linea
    size_t len = strlen(task.soft_delete);
    if (len > 0 && task.soft_delete[len - 1] == '\n') {
        task.soft_delete[len - 1] = '\0';
    }

    return task;
}

int showTableTasks(){

    int maxID = getLastId("bdd/constants.txt", "last_id_task");

    printf("\n\nTABLA DE TAREAS\n");

    printTaskTableHeader();

    for(int row=1; row < maxID; row++){

        char line[MAX_LINE];
    
        if (readLineFromFile("bdd/tasks.csv", row, line)) {
            Task task = parseTaskFromCSVLine(line);
            printTaskRow(task);
        }

    }

    printf("\n\n");
}


int updateDataTask(const char *filename, int taskId, const char *new_title, const char *new_description,const int new_status) {
    
    FILE *file = fopen(filename, "r");
    
    FILE *tempFile = fopen("bdd/temp_tasks.csv", "w");

     
    if (file == NULL || tempFile == NULL) {
        return 0;
    }

    char line[MAX_LINE];
    int updated = 0;

    while (fgets(line, sizeof(line), file)) {
        Task task = parseTaskFromCSVLine(line);

        if (task.id == taskId) {

            strncpy(task.title, new_title, sizeof(task.title));

            strncpy(task.description, new_description, sizeof(task.description));

            task.status = new_status;

            fprintf(tempFile, "%d,%d,%s,%s,%d,%s,%s\n",
                task.id,
                task.id_user,
                task.title,
                task.description,
                task.status,
                task.create_at,
                task.soft_delete
            );

            updated = 1;

        } else {

            fputs(line, tempFile);

        }
    }

    fclose(file);
    fclose(tempFile);

    remove(filename);
    rename("bdd/temp_tasks.csv", filename);

    return updated;
}

int updateTask(){

    showTableTasks();

    Task task;

    getDataUpdateTask(&task);

    int resultado = updateDataTask("bdd/tasks.csv", task.id, task.title, task.description,1);

    if (!resultado) {
        printf("\nNO SE ENCONTRO LA TAREA A ACTUALIZAR.\n");

        return 0;
    }

    printf("\nTAREA ACTUALIZADA CORRECTAMENTE.\n");
    return 1;
}

int deleteTask(){

    showTableTasks();

    Task task;

    getDataDeleteTask(&task);

    char line[MAX_LINE];    

    if (!readLineFromFile("bdd/tasks.csv", task.id, line)) {

        printf("\nNO SE ENCONTRO LA TAREA A TERMINAR.\n");

        return 0;
    }

    Task taskBDD = parseTaskFromCSVLine(line);


    int resultado = updateDataTask("bdd/tasks.csv", task.id, taskBDD.title, taskBDD.description,0);

    if (!resultado) {
        printf("\nNO SE ENCONTRO LA TAREA A TERMINAR.\n");

        return 0;
    }

    printf("\nTAREA TERMINADA CORRECTAMENTE.\n");

    return 1;
}

void showMenuTasks() {
    int opcion;

    do {
        printf("\n=====================================\n\n");
        printf("   MÓDULO DE GESTIÓN DE TAREAS\n\n");
        printf("=====================================\n");
        printf(" 1.  Ver todas las Tareas\n");
        printf(" 2.  Crear nueva Tarea\n");
        printf(" 3.  Actualizar datos de Tarea\n");
        printf(" 4.  Terminar Tarea\n");
        printf(" 5.  Volver al menú principal\n");
        printf("-------------------------------------\n");
        printf("Seleccione una opción (1-5): ");

        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                showTableTasks();
                break;
            case 2:
                createTask();
                break;
            case 3:
                updateTask();
                break;
            case 4:
                deleteTask();
                break;
            case 5:
                printf("Regresando al menu principal...\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while(opcion != 5);
}