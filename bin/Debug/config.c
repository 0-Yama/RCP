#include "Struct.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int GetConfig(char * config_path_name, Conf * Config){

    FILE * config_file = fopen(config_path_name,"rb");

    if(!config_file)
        return -1;

    char * sentence = malloc(sizeof(char)*50);


    while(fgets(sentence,14,config_file),!feof(config_file)){
        if(strstr(sentence,"resolution : ")){
            fgets(sentence,5,config_file);
            char * width = malloc(sizeof(char)*4);
            char * height = malloc(sizeof(char)*4);
            strncpy(width,sentence,4);
            Config->width = atoi(width);

            fgets(sentence,2,config_file);
            fgets(sentence,5,config_file);

            strncpy(height,sentence,4);
            Config->height = atoi(height);
        }
        if(strstr(sentence,"musicFile  : ")){
            fgets(sentence,50,config_file);
            //GetContent(Config,sentence,"Musics");
            printf("hello\n");

        }
        if(strstr(sentence,"textureFile: ")){
            fgets(sentence,50,config_file);
            GetContent(Config,sentence,"Images");
            printf("hello\n");
        }
    }
    return 0;
}
int GetContent(Conf * Config,char * path,char * type){
    FILE * loaded_file = fopen(path,"rb");
    int counter = 0;
    char * file = malloc(sizeof(char)*200);
    while(fgets(file,200,loaded_file),!feof(loaded_file)){
        counter++;
    }
    char ** textures = malloc(sizeof(char *)*counter);
    fseek(loaded_file,0,SEEK_SET);
    counter = 0;
    while(fgets(file,200,loaded_file),!feof(loaded_file)){
        char * pathadd = malloc(sizeof(char)*200);
        strcpy(pathadd,type);
        strcat(pathadd,"\\");
        strcat(pathadd,file);
        printf("%s",pathadd);
        textures[counter++] = pathadd;
        free(pathadd);
    }
    Config->Texturespath = textures;
    Config->Texturespathlength = counter;
    free(file);
    free(textures);
    fclose(loaded_file);
}

