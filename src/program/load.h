#ifndef _LOAD_H
#define _LOAD_H

#include "../modules.h"
#include "../modules/listuser.h"
#include "../modules/listemail.h"


#define CAPACITY_CHAR_USER 256
#define CAPACITY_CHAR_EMAIL 1001

void inisialisasi(ListUser *listUser, ListEmail *listEmail);
int loadConfigfromFoler(char *folderPath, ListUser *listUser, ListEmail *listEmail);
int loadUmum(char *filePath, int *pagination, int *importantInteraction);
int loadUser(char *filePath, ListUser *listUser);
int loadEmail(char* filePath, ListEmail *listEmail);
int isDirectoryExist(char *folderPath);
int createDirectory(char *folderPath);
void SaveConfig();
void ExitProgram();

#endif