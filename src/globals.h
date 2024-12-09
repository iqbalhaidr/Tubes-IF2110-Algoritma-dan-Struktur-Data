#ifndef GLOBALS_H
#define GLOBALS_H

#include "./modules/boolean.h"
#include "./pengguna/pengguna.h"
#include "./modules/listuser.h"
#include "./modules/listemail.h"

extern boolean authenticated;
extern ListUser listUser;
extern ListEmail listEmail; 
extern activeUser user;
extern char fileUserPath[256];
extern char fileEmailPath[256];
extern char fileUmumPath[256];
extern int pagination;
extern int importantInteraction;

#endif