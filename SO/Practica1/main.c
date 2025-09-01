#include <stdio.h>
#include <string.h>
#include "input.h"
#include "files.h"

int siguienteID = 0;
int fd = -1;

void capturarCriatura(){
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
    escribir_criatura(fd, &c);
};

void mostrarCriaturas(){
    Criatura c;
    fd = abrir_archivo();
    while(leer_criatura(fd, &c) > 0){
        insertar();
    }
    mostrar(lista);
};

void eliminarCriatura(Lista* lista){
    int pos = -1;
    int id = leerEnteroPositivo("Ingrese el ID de la criatura a eliminar (entero positivo)"); 
    Nodo* actual = lista->head;
    
    while(actual != NULL){
        pos++;
        Criatura c = actual->criatura;
        if(c.id == id){
            eliminar(lista, pos);
            return;
        }
        actual = actual->siguiente;
    }
    
    if(eliminar(lista, pos) != 0){
        printf("No se encontro la criatura con el ID = %d\n", id);
    };
};

int main(){
    Lista lista;
    lista.head = NULL;

    fd = abrir_archivo();

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
                eliminarCriatura(&lista);
                break;
            case 4:
                printf("Fin del programa");
                break;
            default:
                printf("Seleccione una opcion valida");
        } 
    }

    cerrar_archivo(fd);
}
