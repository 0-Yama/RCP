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
            Config->Musicspath = sentence;
            //printf("hello\n");

        }
        if(strstr(sentence,"textureFile: ")){
            fgets(sentence,50,config_file);
            Config->texturespath = sentence;
            //printf("hello\n");
        }
    }
    return 0;
}

