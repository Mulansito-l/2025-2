#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "list.h"

int abrir_archivo(){
    int fd = open("criaturas.archivo", O_WRONLY | O_CREAT);
    if(fd == -1){
        printf("No se pudo abrir el archivo criaturas");
    }
    return fd; 
}

void escribir_criatura(int fd, Criatura* c){
   write(fd, c, sizeof(Criatura)); 
}

int leer_criatura(int fd, Criatura* criatura){
    return read(fd, criatura, sizeof(Criatura));
}

void cerrar_archivo(int fd){
    close(fd);
}
