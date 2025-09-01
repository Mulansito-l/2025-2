#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "input.h"
#include "list.h"

Lista* lista = NULL;
int siguienteID = 0;

void capturarCriatura(){
    borrar(lista);
    int fd = open("criaturas.archivo", O_WRONLY | O_CREAT | O_APPEND);
    getchar();
    Criatura c; 
    printf("Ingrese la especie:\n");
    leerStringSinEnter(c.especie, 20);
    printf("Ingrese el apodo:\n");
    leerStringSinEnter(c.apodo, 20);
    c.nivel = leerEnteroPositivo("Ingrese el nivel de la criatura (entero positivo):");
    c.exp = leerEnteroPositivo("Ingrese la experiencia actual de la criatura (entero positivo):");
    c.id = siguienteID;
    siguienteID++;
    write(fd, &c, sizeof(Criatura)); 
    printf("Tamaño de struct al guardar: %lu\n", sizeof(Criatura));
    close(fd);
    borrar(lista);
};

void mostrarCriaturas(){
    Criatura c;
    int fd = open("criaturas.archivo", O_RDONLY);

    while(read(fd, &c, sizeof(Criatura)) > 0){
        Nodo* nuevo = insertar(lista);
        memcpy(&nuevo->criatura,&c,sizeof(Criatura));
    }
    printf("Tamaño de struct: %lu\n", sizeof(Criatura));
    mostrar(lista);
    borrar(lista);
    close(fd);
};

void escribirLista(){
    unlink("criaturas.archivo");
    getchar();
    int fd = open("criaturas.archivo", O_WRONLY | O_CREAT);
    Nodo* actual = lista->head; 
    while(actual != NULL){
        write(fd, &actual->criatura, sizeof(Criatura)); 
        actual = actual->siguiente;
    }
    close(fd);
}

void eliminarCriatura(){
    Criatura c;
    int fd = open("criaturas.archivo", O_RDONLY);
    while(read(fd, &c, sizeof(Criatura)) > 0){
        Nodo* nuevo = insertar(lista);
        memcpy(&nuevo->criatura,&c,sizeof(Criatura));
    }
    close(fd);

    int pos = -1;
    int id = leerEnteroPositivo("Ingrese el ID de la criatura a eliminar (entero positivo)"); 
    Nodo* actual = lista->head;
    
    while(actual != NULL){
        pos++;
        Criatura c = actual->criatura;
        if(c.id == id){
            eliminar(lista, pos);
            escribirLista();
            borrar(lista);
            return;
        }
        actual = actual->siguiente;
    }
    
    printf("No se encontro la criatura con el ID = %d\n", id);
    escribirLista();
    borrar(lista);
};

void obtenerMaxID(){
    Criatura c;
    int fd = open("criaturas.archivo", O_RDONLY);

    while(read(fd, &c, sizeof(Criatura)) > 0){
        siguienteID = c.id + 1;
    }
    close(fd);
}

int main(){
    Lista lista_s;
    lista_s.head = NULL;
    lista = &lista_s;
    obtenerMaxID();

    int op = 0;

    while (op != 4) {
        printf("---Repertorio de criaturas---\n");
        printf("--- 1) Capturar           ---\n");
        printf("--- 2) Mostrar            ---\n");
        printf("--- 3) Eliminar           ---\n");
        printf("--- 4) Salir              ---\n");
        printf("Ingrese la opcion a realizar:");
        scanf("%d",&op);
        switch (op) {
            case 1:
                capturarCriatura();
                break;
            case 2:
                mostrarCriaturas();
                break;
            case 3:
                eliminarCriatura();
                break;
            case 4:
                printf("Fin del programa");
                break;
            default:
                printf("Seleccione una opcion valida");
        } 
    }
}
