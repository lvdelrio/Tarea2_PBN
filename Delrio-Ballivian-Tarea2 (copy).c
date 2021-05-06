#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <time.h> 
#include <sys/resource.h>

double memoria(){
    struct  rusage r;
    getrusage(RUSAGE_SELF, &r);
    return(double)r.ru_maxrss;
}

struct generos{
    char* genero; 
    char* id; 
    char* artista; 
    int popu;
    char* major; 
    
};

int string_compare(char str1[], char str2[])
{
    int ctr=0;
    //printf("estoy en la super mega funcion : %s \n", str1);
    //printf("%s final de linea \n",str2);
    while(str1[ctr]==str2[ctr])
    {   
        //printf(" letras %c    %c\n",str1[ctr],str2[ctr]);
        if(str1[ctr]=='\0'||str2[ctr]=='\0')
            break;
        ctr++;
    }
    if(str1[ctr]=='\0' && str2[ctr]=='\0')
        return 0;
    else
        return -1;
}

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

//Main
int main(int argc, char** argv){

    double tiempo = clock();

    FILE*genres;
    FILE*songs;
    genres=fopen("genres.txt","r");
    songs=fopen("songs.txt","r");

    struct generos* datos = malloc(sizeof(struct generos));


    int numerodedatos = numero_lineas(genres); //Cuento lineas
    //int numerodedatos = 1500;
    printf("%d Datos\n", numerodedatos);

    
    char* line = malloc(255*sizeof(char)); //ACUERDATE DEL FREE 
    char* line2 = malloc(255*sizeof(char)); 

    
    //char line[255]; //Hay que declarar eso diferente por las decimas
    int contador = 0;
    char*** lineas = malloc(sizeof(char**));
    lineas[0]=malloc(3*sizeof(char*));
    int cont_lines = 0;






//------------inicio de programa------------
//------------Modo -p ----------------------
if(strcmp(argv[1], "-g") == 0){ //=======================================================================================
    int contador_genero = 0;
    for(int c=0; c<numerodedatos; c++){ //Tratar de recorrer 10 nombres
        
        fgets(line,256,genres); //generos.txt 

        line[strcspn(line, "\n")] = 0;

        //printf("DATO : %s \n",line);
        
        char* token = strtok(line, ";");

        
        //printf("token %s\n", token);
        if(strcmp(token, argv[2]) == 0){
            //printf("El token eligio %s\n", argv[2]);

            while(token !=NULL){ //Palabra 1
                char* palabra= malloc(100*sizeof(char));
                strcpy(palabra,token);


                if(contador==0){
                    datos[contador_genero].genero=palabra;
                    }
                if(contador==1){
                    datos[contador_genero].id=palabra;
                    }
                if(contador==2){
                    datos[contador_genero].artista=palabra;
                    }

                token = strtok(NULL,";");
                contador++;
                
                
                
            }//termina el while de geners
            datos = realloc(datos,(contador_genero+2)*(sizeof(struct generos)));

            contador_genero ++;
            cont_lines++;
        }//If modo -g
        else{
            continue;
        }
        contador = 0;

    
    }//termina el for 1

        for(int i=0;i<cont_lines-1;i++){ //Archivo songs
            for(int j = 0; j<numerodedatos;j++){
                fgets(line2,256,songs); 

                line2[strcspn(line2, "\n")] = 0;
                
                char* token2 = strtok(line2,";");
                //printf("datos[i] %s == token2 %s\n",datos[i].id,token2);

                int boolean=string_compare(datos[i].id,token2); //comparo strings letra por letra
                //printf("%d Bool\n", boolean);
                
                if(boolean==0){
                    int contador_song=0;
                    while(token2 != NULL){

                        char* palabra2= malloc(100*sizeof(char));
                        strcpy(palabra2,token2);


                        if(contador_song==1){
                            datos[i].popu=atoi(palabra2);
                            
                            }
                        if(contador_song==2){
                            datos[i].major=palabra2;
                            
                            }
                        
                        token2 = strtok(NULL,";");
                        contador_song++;
                        }
                    break;
                }
                
            }
            
            rewind(songs); //Reinicio gets
        }//fin For

    //Condicion 
    int min_pupo = atoi(argv[3]);

    int cuenta_artistas = 0;

    char** artistas = malloc(1*sizeof(char*));

    float popu_suma = 0;
    float promedio = 0;

    int contador_artistas = 0;
    for(int i=0;i<cont_lines-1;i++){


        char* artista = malloc(100*sizeof(char)); //Artista actual
        strcpy(artista, datos[i].artista);

        
        float popu_suma = 0;
        float promedio = 0;
        
        int cuenta_artistas = 0;
        int flag1 = 1;
        //Compruebo si el artista ya fue calculado (flag = 0 ya esta, flag = 1 no esta)
        for(int k=0;k<contador_artistas;k++){
            if(strcmp(artistas[k], artista) == 0){
                flag1 = 0;
            }
        }
        if(flag1 == 1){
            //cuento tot que aparece el artista
            for(int j=0;j<cont_lines-1;j++){ 
                if(strcmp(artista, datos[j].artista) == 0){
                    popu_suma += datos[j].popu;
                    cuenta_artistas++;
                }
            } 
            //Calculo de promedio
            promedio = popu_suma/cuenta_artistas;
            //Aplico condicion del argv e imprimo
            if(promedio >= min_pupo){
                printf("%s : %.1f \n", datos[i].artista, promedio);
            }
            free(artista);
        }
                
        //Almaceno los artistas en puntero para comparar si ya estan
        int flag2 = 0; //Flag2 ve si artista ya fue almacenado o no

        for(int k=0;k<contador_artistas;k++){
            
            if(artistas[k] != NULL){
                
                if(strcmp(artistas[k], datos[i].artista) == 0){
                    flag2 = 1;
                    break;
                }
                else{
                    continue;
                }
            }
        }
        if(contador_artistas == 0){
            contador_artistas += 1;
        }
        else if(contador_artistas != 0 && flag2 == 0){
            contador_artistas += 1;
            artistas = realloc(artistas, (contador_artistas)*(sizeof(char*)));
        }
        if(flag2 == 0){
            artistas[contador_artistas-1] = datos[i].artista;
        }

        
    }//Fin for de Promedio de artistas

    //Corredor de artistas vvv
    /*
    for(int k=0;k<contador_artistas;k++){
        printf("%s Artistas \n", artistas[k]);
    }
    */

    free(artistas);
    free(lineas);
    free(line);
    free(datos);

}//Fin del modo -g
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++






//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//------------inicio de programa------------
//------------Modo -p ----------------------
else if(strcmp(argv[1], "-p") == 0){
    int contador_song = 0;
    for(int c=0; c<numerodedatos; c++){ //Tratar de recorrer 10 nombres
        
        fgets(line2,256,songs); //songs.txt ---------------------------------------------

        line2[strcspn(line2, "\n")] = 0;

        //printf("DATO : %s \n",line);
        
        char* token2 = strtok(line2, ";");

        
        //printf("token %s\n", token2);
        
            //printf("El token eligio %s\n", argv[2]);

            while(token2 !=NULL){ //Palabra 1
                char* palabra= malloc(100*sizeof(char));
                strcpy(palabra,token2);


                if(contador==0){
                    datos[contador_song].id=palabra;
                }
                if(contador==1){
                    datos[contador_song].popu=atoi(palabra);
                }
                if(contador==2){
                    if(strcmp(token2, argv[2]) == 0){ //Comprobar minor o major (Solo avanzo si cumple condicion)
                        datos[contador_song].major=palabra; //o si no reemplazo
                        datos = realloc(datos,(contador_song+2)*(sizeof(struct generos)));
                        contador_song ++;
                        cont_lines++;
                    }
                }

                token2 = strtok(NULL,";");
                contador++;
                
                
                
            }//termina el while de geners

        contador = 0;

    
    }//termina el for 1
    int contador_genres = 0;
    for(int i=0;i<cont_lines;i++){ //Archivo genres
        for(int j = 0; j<numerodedatos;j++){
            fgets(line,256,genres); 

            line[strcspn(line, "\n")] = 0;
            
            char* token = strtok(line,";");
            char* token1 = malloc(20*sizeof(char));
            strcpy(token1,token);
            token = strtok(NULL,";");
            
            int boolean = 0;
            //printf("datos[i] %s == token %s\n",datos[i].id,token);
            boolean = string_compare(datos[i].id,token); //comparo strings letra por letra
            //printf("%d Bool 1\n", boolean);
            
            
            if(boolean==0){
                int contador_genero=0;
                while(token != NULL){

                    char* palabra2= malloc(100*sizeof(char));
                    strcpy(palabra2,token);

                    if(contador_genero==0){
                        datos[i].genero=token1;
                        
                        }

                    if(contador_genero==1){
                        datos[i].id=palabra2;
                        
                        }
                    if(contador_genero==2){
                        datos[i].artista=palabra2;
                        
                        }
                    
                    token = strtok(NULL,";");
                    //printf("\n contador_song %d \n +++++++++ \n", contador_song);
                    contador_genero++;
                    }
                break;
            }
            free(token1);
            
        }
        
        rewind(genres); //Reinicio 

    }//fin For
        /*
         //Confirmador de datos
        printf("esto es contador %d\n",cont_lines);
        for(int i=0;i<cont_lines;i++){
            printf("FOR ---------\n");
            printf("GEN %s \n",datos[i].genero);
            printf("ID  %s \n",datos[i].id);
            printf("ART %s \n",datos[i].artista);
            printf("POP %d \n",datos[i].popu);
            printf("MAJ %s \n",datos[i].major);  
            
        }
        */
    
    //Condicion 
    char* minmaj = argv[2];

    int cuenta_generos = 0;
    
    //char** artistas = malloc(1*sizeof(char*));
    char** losgeneros = malloc(1*sizeof(char*));


    int contador_generos= 0;
    for(int i=0;i<cont_lines-1;i++){
        
        char* genero = malloc(100*sizeof(char)); //genero actual
        
        strcpy(genero, datos[i].genero);
        
        //float popu_suma = 0;
        //float promedio = 0;
        
        int cuenta_generos = 0;
        int flag1 = 1;
        //Compruebo si el genero ya fue calculado (flag = 0 ya esta, flag = 1 no esta)
        for(int k=0;k<contador_generos;k++){
            if(strcmp(losgeneros[k], genero) == 0){
                flag1 = 0;
            }
        }
        if(flag1 == 1){
            //cuento tot que aparece el genero
            for(int j=0;j<cont_lines-1;j++){ 
                if(strcmp(genero, datos[j].genero) == 0){
                    cuenta_generos++;
                }
            } 


            //Aplico condicion del argv e imprimo

            printf("%s : %d \n", datos[i].genero, cuenta_generos);
            free(genero);
        }
                
        //Almaceno los generos en puntero para comparar si ya estan
        int flag2 = 0; //Flag2 ve si genero ya fue almacenado o no
        //printf("%s \n", datos[i].genero);
        for(int k=0;k<contador_generos;k++){
            
            if(losgeneros[k] != NULL){
                
                if(strcmp(losgeneros[k], datos[i].genero) == 0){
                    flag2 = 1;
                    break;
                }
                else{
                    continue;
                }
            }
        }
        if(contador_generos == 0){
            contador_generos ++;
        }
        else if(contador_generos != 0 && flag2 == 0){
            contador_generos ++;
            losgeneros = realloc(losgeneros, (contador_generos)*(sizeof(char*)));
        }
        if(flag2 == 0){
            losgeneros[contador_generos-1] = datos[i].genero;
        }
    
        
    }//Fin for 
    
    //Corredor de artistas vvv
    /*
    for(int k=0;k<contador_generos;k++){
        printf("%s generos \n", losgeneros[k]);
    }
    */
    
    

    free(losgeneros);
    free(lineas);
    free(line);
    free(datos);
}//Fin del modo -p

    //Stats
    tiempo = clock() - tiempo;
    printf("%lf Tiempo \n", tiempo/CLOCKS_PER_SEC);
    printf("%lf KB Memoria\n", memoria());

    return 0;
}