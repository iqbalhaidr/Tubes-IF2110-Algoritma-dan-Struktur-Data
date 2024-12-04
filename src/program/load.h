#ifndef LOAD_H
#define LOAD_H

#include "../modules.h"

#define CAPACITY_CHAR_USER 256
#define CAPACITY_CHAR_EMAIL 1001

int inisialisasi();
int loadConfigfromFoler(char *folderPath, ListUser *listUser, ListEmail *listEmail);
int loadUser(char* fileUser, ListUser *listUser);
int loadEmail(char* fileEmail, ListEmail *listEmail);
int saveConfig();

#endif