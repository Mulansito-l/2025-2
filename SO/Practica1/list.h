#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int id;
    char especie[20];
    char apodo[20];
    int nivel;
    int exp;
} Criatura;

typedef struct s_Nodo{
    Criatura criatura;
    struct s_Nodo* siguiente;
} Nodo;

typedef struct{
    Nodo* head;
} Lista;

Nodo* insertar(Lista* lista){
    Nodo* actual = lista->head;
    Nodo* nodo = (Nodo*) malloc(sizeof(Nodo));

    if(lista->head == nullptr){
        lista->head = nodo;
        return nodo;
    }

    while(actual->siguiente != nullptr){
        actual = actual->siguiente; 
    }

    actual->siguiente = nodo;
    return nodo;
}

int eliminar(Lista* lista, int pos){
    int contador = 0;
    Nodo* actual = lista->head;
    Nodo* anterior = nullptr;

    while(actual != nullptr){
        if(contador == pos){
            anterior->siguiente = actual->siguiente; 
            free(actual);
            return 0;
        }
     
        anterior = actual;
        actual = actual->siguiente;
        contador++;
    }

    return 1;
}

void mostrar(Lista* lista){
    Nodo* actual = lista->head;
    if(actual == nullptr){
        printf("La lista se encuentra vacia\n");
        return;
    }

    while(actual != nullptr){
        Criatura c = actual->criatura;
        printf("---%s---\n", c.apodo);
        printf("Especie: %s\n", c.especie);
        printf("Nivel: %d\n", c.nivel);
        printf("Exp: %d\n", c.exp);
        printf("ID: %d\n\n", c.id);
        actual = actual->siguiente;
    }
}
