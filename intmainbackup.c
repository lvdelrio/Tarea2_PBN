//Main
int main(int argc, char** argv){
    FILE*genres;
    FILE*songs;
    genres=fopen("genres.txt","r");
    songs=fopen("songs.txt","r");

    struct generos* datos = malloc(sizeof(struct generos));


    int numerodedatos = numero_lineas(genres); //Cuento lineas
    printf("%d Datos\n", numerodedatos);

    
    char* line = malloc(255*sizeof(char)); //ACUERDATE DEL FREE 
    char* line2 = malloc(255*sizeof(char)); 

    
    //char line[255]; //Hay que declarar eso diferente por las decimas
    int contador = 0;
    char*** lineas = malloc(sizeof(char**));
    lineas[0]=malloc(3*sizeof(char*));
    int cont_lines = 0;
//------------Selector de modo--------------
    if(strcmp(argv[1], "-p") == 0){
        char* exe_mode = argv[1];
        char* p_mode = argv[2];
    }
    else if(strcmp(argv[1], "-g") == 0){
        char* exe_mode = argv[1];
        char* g_mode = argv[2];
    }
//------------inicio de programa------------
    //
    for(int c=0; c<100; c++){ //Tratar de recorrer 10 nombres
        char** linea = malloc(3*sizeof(char*));
        char** linea2 = malloc(3*sizeof(char*));
        for (int i=0;i<5;i++){ //Generos
            linea[i]=malloc(100*sizeof(char));
            } 
        for (int i=0;i<3;i++){//Songs
            linea2[i]=malloc(100*sizeof(char));
            } 
            
        fgets(line,256,genres); //generos.txt ---------------------------------------------

        line[strcspn(line, "\n")] = 0;

        //printf("DATO : %s \n",line);
        
        char* token = strtok(line, ";");
        /*
        printf("token %s\n", token);
        if(strcmp(token, argv[2])){
            printf("El token eligio \n");
        }
        */
        while(token !=NULL){ //Palabra 1
            char* palabra= malloc(100*sizeof(char));
            strcpy(palabra,token);

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
            //printf("%s Print en Palabra 1",linea[0]);
            token = strtok(NULL,";");
            contador++;
            
            
        }//termina el while de geners

        datos = realloc(datos,(c+2)*(sizeof(struct generos)));
        
        if(cont_lines>=1){
            int aux_count=cont_lines+1;
            char*** aux_lineas = realloc(lineas,aux_count*sizeof(char**));
            lineas=aux_lineas;
            lineas[cont_lines]=malloc(3*sizeof(char*));
            }
        lineas[cont_lines]=linea;
        //printf("%s %s %s",lineas[0][0],lineas[0][1],lineas[0][2]);
        contador = 0;
        cont_lines++;
        
    
    free(linea);
    //printf("Dato c : %d \n ", c);
    }//termina el for
       
        for(int i=0;i<cont_lines;i++){ //Archivo songs
            for(int j = 0; j<cont_lines;j++){
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
                        //strcpy(linea[contador],palabra);

                        if(contador_song==1){
                            datos[i].popu=atoi(palabra2);
                            
                            }
                        if(contador_song==2){
                            datos[i].major=palabra2;
                            
                            }
                        
                        token2 = strtok(NULL,";");
                        //printf("\n contador_song %d \n +++++++++ \n", contador_song);
                        contador_song++;
                        }
                    break;
                }
                

            }
            
            rewind(songs); //Reinicio 
        }
        
        
        printf("esto es contador %d\n",cont_lines);
        for(int i=0;i<cont_lines-1;i++){
            printf("FOR ---------\n");
            printf("GEN %s \n",datos[i].genero);
            printf("ID  %s \n",datos[i].id);
            printf("ART %s \n",datos[i].artista);
            printf("POP %d \n",datos[i].popu);
            printf("MAJ %s \n",datos[i].major);  
        }
        

    
    //Modos
    int cantidad_major = 0;
    int cantidad_genero = 0;
    /*
    if(strcmp(argv[1], "-p") == 0){ //Comparar el dato actual y contar la cantidad 
                                    //de major/minor con ese dato actual

        for(int i=0;i<cont_lines-1;i++){
            char* genero_actual = datos[i].genero;
            
            for(int i=0;i<cont_lines-1;i++){
                char* genero_actual = datos[i].genero;

                printf("%s major \n", datos[i].major);
                if(strcmp(argv[2], datos[i].major) == 0){
                    //Cuento el genro con el major/minor
                    cantidad_major ++;
                    
                    printf("%s : %d \n", datos[i].genero, cantidad_genero);

                    
                    
                }
                
            
            }
        }
        printf("%d Cantidad del %s \n", cantidad_major, argv[2]);
    }
    */   
    
    //free(lineas[0]); Esto me tira core dumped
    free(lineas);
    free(line);
    return 0;
}