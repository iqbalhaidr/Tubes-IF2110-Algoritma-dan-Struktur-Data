#include <stdio.h>
#include "modules.h"
#include "globals.h"
#include "./program/utility.h"

boolean authenticated;
ListUser listUser; 
ListEmail listEmail; 
activeUser user;

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
        startMenu();
        autentikasiUser();

        //Program
        if (authenticated){
            menu();
        }
    } 
    return 0;
}