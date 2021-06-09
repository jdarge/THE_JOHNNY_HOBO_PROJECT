#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

//INTERNAL LIBS
#include "raylib.h"
#include "fmod/api/lowlevel/inc/fmod.h"

//UTILITY
char *direcGen();
char* newDirec(char* direc, char* input);
char *strremove(char *str, char *sub);

//SONG
void PLAY_SONG(char *SOUND_FILE_PATH);
char* REMOVE_SONG(char *direc, char* song);
char* SONG_DIREC(char* direc, char* song_name);

//GUI
void CREATE_GUI();

int main(void) {//TODO STOP PROGRAM FROM CLOSING AT END OF SONG

    //INITIALIZING VARIABLES
    char x[1] = {'/'};
    char* def = direcGen();
    char* direc = (char*)malloc(sizeof(char) * (strlen(def) + 1));
    char *input = (char *) malloc(sizeof(char) * 100);

    strcpy(direc, def);
    while(1){
        //waiting for command
        scanf("%s", input);
        if(strcmp(input,"-direc") == 0){
            scanf("%s", input);
            if(strcmp(input,"-default") == 0){
                printf("DEFAULT: %s\n",def);
                direc = strcpy(direc,def);
            } else {
                strcat(input, x);
                direc = newDirec(direc, input);
                printf("%llu %s\n", strlen(direc), direc);
            }
        } else if(strcmp(input,"-play") == 0){
            scanf("%s",input);
            direc = SONG_DIREC(direc, input);
            CREATE_GUI();
            PLAY_SONG(direc);
            direc = REMOVE_SONG(direc, input);
            //printf("%s\n",direc);
        } else if(strcmp(input,"-exit") == 0){
            break;
        } else {
            printf("\nCOMMAND NOT UNDERSTOOD...\n");
        } while ((getchar()) != '\n');
    }
}

//-------SONG-----------------------------------------------------------------------------------------------------------

char* SONG_DIREC(char* direc, char* song_name) {
    //LENGTH OF direc
    unsigned long long length = 1 + strlen(direc);

    //REFORMATTING SONG DIRECTORY
    strcat(direc, song_name);//<-----

    // replaces '\' w/ '/' for FMOD to work properly
    for (int i = 0; i < length; i++)
        if (direc[i] == '\\') direc[i] = '/';

    return direc;
}

void PLAY_SONG(char *SOUND_FILE_PATH) {
    while(1) {
        char temp[6];
        char x;


        FMOD_SYSTEM *system;

        FMOD_RESULT err = FMOD_System_Create(&system);
        if (err != 0) break;

        err = FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, 0);
        if (err != 0) break;

        FMOD_SOUND *sound;
        err = FMOD_System_CreateSound(system, SOUND_FILE_PATH, FMOD_HARDWARE, 0, &sound);
        if (err != 0) break;
        //SONG BEGINS PLAYING HERE
        FMOD_CHANNEL *channel;
        FMOD_System_PlaySound(system, sound, 0, 0, &channel);

        FMOD_BOOL isPlaying = 1;
        while (isPlaying){
            scanf("%s",temp);
            if(strcmp(temp,"-stop") == 0){//while((x=getchar()!='\n')&& x != EOF);
                break;
            } else {

            }
            FMOD_Channel_IsPlaying(channel, &isPlaying);
        }

        err = FMOD_Sound_Release(sound);
        if (err != 0) break;
        err = FMOD_System_Close(system);
        if (err != 0) break;
        err = FMOD_System_Release(system);
        if (err != 0) break;
        break;
    }
}

char* REMOVE_SONG(char *direc, char* song){
    strremove(direc,song);
    return direc;
}

//-------GUI-----------------------------------------------------------------------------------------------------------



//-------UTILITY--------------------------------------------------------------------------------------------------------

char* direcGen(){
    int MAX_BUF = 200;
    char* direc = (char*)malloc(sizeof(char) * MAX_BUF);

    //GETTING AND STORING CURRENT WORKING DIRECTORY
    strcpy(direc, getcwd(direc, MAX_BUF));
    strcpy(direc, strremove(direc, "\\cmake-build-debug-mingw"));// debug purposes only
    strcat(direc, "\\music_files\\");

    unsigned long long length = 1 + strlen(direc);

    for (int i = 0; i < length; i++)
        if (direc[i] == '\\') direc[i] = '/';

    return direc;
}

char* newDirec(char* direc, char* input){
    strcpy(direc, input);
    realloc(direc,sizeof(char) * (strlen(input) + 2));

    unsigned long long length = 2 + strlen(input);

    for (int i = 0; i < length - 1; i++){
        if (direc[i] == '\\') direc[i] = '/';
    }

    return direc;
}

char *strremove(char *str, char *sub) {
    char *p, *q, *r;
    if ((q = r = strstr(str, sub)) != NULL) {
        size_t len = strlen(sub);
        while ((r = strstr(p = r + len, sub)) != NULL) {
            while (p < r)
                *q++ = *p++;
        }
        while ((*q++ = *p++) != '\0')
            continue;
    }
    return str;
}

