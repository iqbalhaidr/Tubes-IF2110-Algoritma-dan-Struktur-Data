#ifndef PENGGUNA_H
#define PENGGUNA_H

#include "../modules.h"

typedef struct {
    int id;
    char* email;
} activeUser;


boolean isEmailValid(char* email);
void registerUser();
void loginUser();
void logoutUser();
void autentikasiUser();

#endif