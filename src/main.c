#include <Windows.h>
#include <stdio.h>
#include "../include/xor.h"

int main(int argc, char **argv){
    int i;
    int o_flag, e_flag;
    char o_option[6];
    char e_option[6];

    if(argc < 3){
        printf("ERROR: Not enough arguments provided, usage: main.exe <flag> <option> ...\nPlease use the -h flag to see what options are available.\n");
        return 0;
    }
    
    for(i=0; i<argc; i++){
        if(!strcmp(argv[i],"-o")){
            
        }

        if(!strcmp(argv[i],"-e")){
            
        }
    }
}