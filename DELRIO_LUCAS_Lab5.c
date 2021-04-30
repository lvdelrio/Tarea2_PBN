#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char* concat(const char *s1, const char *s2){
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
    }

struct Alumno{
    char *nombre;
    float nota;
    int rut;
    char sexo;
    int edad;
};
typedef struct Alumno Alumno;

int main(){
    int eleccion=0;
    char*** lineas = malloc(sizeof(char**));
    char line[255];
    int contador_lineas=0;
    while(1){
        printf("Desea ingresar un alumno? (1) si / (0) no:\n");
        
        scanf("%d",&eleccion);
        int contador = 0;
        int contador_final=0;

        if (eleccion == 1){
            printf("entraste\n");
            printf("ingrese datos: \n");
            fgets(line,sizeof line,stdin);
            fgets(line,sizeof line,stdin);
            char* token=strtok(line, " ");
            char** linea = malloc(5*sizeof(char*));
            for (int i=0;i<5;i++){
                linea[i]=malloc(100*sizeof(char));
                }   
            printf("hola voy a entrar2\n");
            //Andres 3.1 101452514 m 30
            //Maria 6.0 86095270 f 22
            int contador = 0;
            printf("hola voy a entrar\n");
            while(token !=NULL){
                char* palabra= malloc(100*sizeof(char));
                //printf("%s \n",token);
            
                palabra=token;
                linea[contador]=palabra;
                printf("%s\n",palabra);
                printf("hola como estas buen señior2222 %d \n",contador);
                token = strtok(NULL," ");
                contador++;

                    
                printf("voy a salir %d\n",contador);

                }
            printf("hola como estas buen señior\n");
            
            for(int i=0;i<5;i++){
                printf("%s \n",linea[i]);
                }
            int aux = contador_lineas+1;
            lineas=realloc(lineas,aux*sizeof(char**));
            lineas[contador_lineas]=linea;
            contador_lineas++;
            
            
            printf("contadores");
            printf("%d",contador_lineas);
            
            
            
            }

        else{
            printf("no entraste");
            break;
            }  
        }
    for(int i=0;i<contador_lineas;i++){
        printf("\n");
        for(int j=0; j<5;j++){
            printf("%s ",lineas[i][j]);

            }
        }
    }