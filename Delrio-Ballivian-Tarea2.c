#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//struct generos

int numero_lineas(FILE*file){ //Contador de Lineas del archivo
    char ch;
    int lineas = 0;
    while(!feof(file)){
        ch = fgetc(file);
        if(ch == '\n'){
            lineas++;
        }
        else{
            continue;
        }
    }
    rewind(file); //Reicinio el Puntero de fgets para usearlo otra vez
    return lineas;
}









int main(){
    FILE*genres;
    FILE*songs;
    genres=fopen("genres.txt","r");
    songs=fopen("songs.txt","r");


    int numerodedatos = numero_lineas(genres); //Cuento lineas
    printf("%d Datos\n", numerodedatos);

    
    char line[255]; //Hay que declarar eso diferente por las decimas
    int contador = 0;
    char*** lineas = malloc(sizeof(char**));
    lineas[0]=malloc(3*sizeof(char*));
    int cont_lines = 0;
//------------inicio de programa------------
    int decision=1;
    while(decision){

        printf("ingrese un numero (1) o (0)");
        scanf("%d",&decision);
        
        if(decision==1){
            for(int c=0; c<numerodedatos; c++){ //Tratar de recorrer 10 nombres
                printf("numero de iteracion %d \n", c);
                char** linea = malloc(3*sizeof(char*));
                for (int i=0;i<5;i++){
                    linea[i]=malloc(100*sizeof(char));
                    }  
                fgets(line,sizeof line,genres);
                printf("%s",line);

                char* token =strtok(line, ";");

                //printf("Token : %s\n", token);
                 
                while(token !=NULL){
                    char* palabra= malloc(100*sizeof(char));
                    strcpy(palabra,token);
                    //strcpy(linea[contador],palabra);
                    linea[contador]=palabra;
                    printf("%s\n",palabra);
                    token = strtok(NULL,";");
                    contador++;
                    free(palabra);
                }
            
            free(linea);
            }
        }
        
    }
    return 0;
}
            
                