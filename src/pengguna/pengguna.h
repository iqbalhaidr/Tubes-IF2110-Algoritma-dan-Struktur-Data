#ifndef _PENGGUNA_H
#define _PENGGUNA_H

#include "../modules/boolean.h"
#include "../modules/listuser.h"
#include "../modules/listemail.h"

typedef struct {
    int id;
    char* email;
} activeUser;

boolean isEmailValid(char* email);
void registerUser();
void loginUser();
void LogoutUser();
void autentikasiUser();

#endif