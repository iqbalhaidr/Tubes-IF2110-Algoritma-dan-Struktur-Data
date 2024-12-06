#include <stdio.h>
#include "modules.h"
#include "globals.h"
#include "./program/utility.h"

boolean authenticated;
ListUser listUser; 
ListEmail listEmail; 
activeUser user;
char fileUserPath[256];
char fileEmailPath[256];

int main(){
    printf("Berhasil run main.\n");

    // Deklarasi Variabel
    authenticated = false;
    CreateListUser(&listUser);
    CreateListEmail(&listEmail, 1000);
    
    // Insialisasi
    int init = inisialisasi(&listUser, &listEmail);
    if(init){        
        //Autentikasi Pengguna (REGISTER/LOGIN)
        do {
            startMenu();
            autentikasiUser();
        } while (!authenticated);

        //Program
        if (authenticated){

            // printListUser(listUser);
            // printf("\n");
            // printListEmail(listEmail);

            saveConfig();

            menu();
        }
    } 
    return 0;
}