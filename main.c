//HOW DO I PUSH FROM A SECOND LOCAL BRANCH TO A REMOTE SECOND BRANCH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

//INTERNAL LIBS
#include "fmod/api/lowlevel/inc/fmod.h"

//FUNCTIONS
char *direcGen();
char* SONG_DIREC(char* direc, char* song_name);
char *strremove(char *str, char *sub);
void PLAY_SONG(char *SOUND_FILE_PATH);

int main(void) {//TODO STOP PROGRAM FROM CLOSING AT END OF SONG

    //INITIALIZING VARIABLES
    char* direc = direcGen();
    char *song_name = (char *) malloc(sizeof(char) * 100);

    //GETTING SONG NAME
    printf("Enter song file name:");
    scanf("%s", song_name);

    //REFORMATS DIREC TO INCLUDE THE SONG
    direc = SONG_DIREC(direc, song_name);

    //
    PLAY_SONG(direc);
}

char* direcGen(){
    int MAX_BUF = 200;
    char* direc = (char*)malloc(sizeof(char) * MAX_BUF);

    //GETTING AND STORING CURRENT WORKING DIRECTORY
    strcpy(direc, getcwd(direc, MAX_BUF));
    strcpy(direc, strremove(direc, "\\cmake-build-debug"));
    strcat(direc, "\\music_files\\");

    return direc;
}

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

void PLAY_SONG(char *SOUND_FILE_PATH) {char temp[50];
    FMOD_SYSTEM *system;

    FMOD_RESULT err = FMOD_System_Create(&system);
    if (err != 0) exit(err);

    err = FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, 0);
    if (err != 0) exit(err);

    FMOD_SOUND *sound;
    err = FMOD_System_CreateSound(system, SOUND_FILE_PATH, FMOD_HARDWARE, 0, &sound);
    if (err != 0) exit(err);
    //SONG BEGINS PLAYING HERE
    FMOD_CHANNEL *channel;
    FMOD_System_PlaySound(system, sound, 0, 0, &channel);

    FMOD_BOOL isPlaying = 1;
    while (isPlaying) FMOD_Channel_IsPlaying(channel, &isPlaying);

    err = FMOD_Sound_Release(sound);
    if (err != 0) exit(err);
    err = FMOD_System_Close(system);
    if (err != 0) exit(err);
    err = FMOD_System_Release(system);
    if (err != 0) exit(err);
}