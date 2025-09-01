#include <stdio.h>
#include <stdlib.h>

int leerEnteroPositivo(const char* prompt){
    int num = 0;
    int* leido = (int*)malloc(sizeof(int));
    printf("%s\n", prompt);
    scanf("%d",leido);
    while(*leido < 0){
        printf("%s\n", prompt);
        scanf("%d",leido);
    }
    
    num = *leido;
    free(leido);
    return num;
};

void leerStringSinEnter(char* buf, int n){
    fgets(buf, n, stdin);
    for (int i = 0; i < n; i++) {
        if(buf[i] == '\n'){
            buf[i] = '\0';
            return;
        } 
    }
};
