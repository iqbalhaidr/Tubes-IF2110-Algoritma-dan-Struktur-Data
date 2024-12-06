#include <stdio.h>
#include "modules.h"
#include "globals.h"
#include "./program/utility.h"
#include "./modules/inbox.h"

boolean authenticated;
ListUser listUser; 
ListEmail listEmail; 
activeUser user;
char fileUserPath[256];
char fileEmailPath[256];

void perintah( ) {
    printf(">> ");
    STARTWORD();
    if (isEqual(currentWord, "INBOX")) {
        Inbox();
    } else {
        printf("Perintah tidak valid.\n");
    }
}

int main(){
    printf("Berhasil run main.\n");

    // Deklarasi Variabel
    authenticated = false;
    CreateListUser(&listUser);
    CreateListEmail(&listEmail, 1000);
    
    // Insialisasi
    int init = inisialisasi(&listUser, &listEmail);
    if(init){        
        perintah();
    //     //Autentikasi Pengguna (REGISTER/LOGIN)
    //     startMenu();
    //     autentikasiUser();

    //     //Program
    //     if (authenticated){
    //         menu();
    //     }
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