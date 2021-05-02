#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct generos{
    char* genero; 
    char* id; 
    char* artista; 
    int popu;
    char* major; 
    
};

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
int run_archivo(FILE*file){
    return 0;
}









int main(){
    FILE*genres;
    FILE*songs;
    genres=fopen("genres.txt","r");
    songs=fopen("songs.txt","r");

    struct generos* datos = malloc(sizeof(struct generos));


    int numerodedatos = numero_lineas(genres); //Cuento lineas
    printf("%d Datos\n", numerodedatos);

    
    char* line = malloc(255*sizeof(char)); //ACUERDATE DEL FREE 

    
    //char line[255]; //Hay que declarar eso diferente por las decimas
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
            
            for(int c=0; c<10; c++){ //Tratar de recorrer 10 nombres
                char** linea = malloc(3*sizeof(char*));
                for (int i=0;i<5;i++){
                    linea[i]=malloc(100*sizeof(char));
                    } 
                 
                fgets(line,256,genres);
                printf("DATO : %s",line);
                
                char* token = strtok(line, ";");
                
                while(token !=NULL){
                    char* palabra= malloc(100*sizeof(char));
                    strcpy(palabra,token);
                    //strcpy(linea[contador],palabra);
                    linea[contador]=palabra;
                    if(contador==0){
                        datos[c].genero=linea[contador];
                        }
                    if(contador==1){
                        datos[c].id=linea[contador];
                        }
                    if(contador==2){
                        datos[c].artista=linea[contador];
                        }
                    printf("%s",linea[0]);
                    token = strtok(NULL,";");
                    contador++;
                    
                    
                }//termina el while
                datos = realloc(datos,(c+2)*(sizeof(struct generos)));
                
                if(cont_lines>=1){
                    int aux_count=cont_lines+1;
                    char*** aux_lineas = realloc(lineas,aux_count*sizeof(char**));
                    lineas=aux_lineas;
                    lineas[cont_lines]=malloc(3*sizeof(char*));
                    }
                lineas[cont_lines]=linea;
                printf("%s %s %s",lineas[0][0],lineas[0][1],lineas[0][2]);
                contador = 0;
                cont_lines++;
                
            
            free(linea);
            printf("Dato c : %d \n ", c);
            }//termina el for
        }//termina el if
        printf("esto es contador %d",cont_lines);
        for(int i=0;i<cont_lines-1;i++){
            printf("\n");
            printf("%s ",datos[i].genero);
            printf("%s ",datos[i].id);
            printf("%s ",datos[i].artista);
            printf("%d ",datos[i].popu);
            printf("%s \n",datos[i].major);
            
        }
        printf("hola bune señior");
        
    }//termina el while
    free(lineas[0]);
    free(lineas);
    free(line);
    return 0;
}
