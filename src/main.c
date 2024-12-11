#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "modules.h"
#include "./modules/listuser.h"
#include "./modules/listemail.h"
#include "./pengguna/pengguna.h"

/* Global Variables */
boolean authenticated;
ListUser listUser; 
ListEmail listEmail; 
activeUser user;
char fileUserPath[256];
char fileEmailPath[256];
char fileUmumPath[256];
int pagination;
int importantInteraction;

#include "./program/load.h"
#include "./email/inbox.h"
#include "./email/draftemail.h"
#include "./email/balasemail.h"
#include "./program/notifikasi.h"
#include "./program/statuskepentingan.h"

int main(){
    printf("Berhasil run main.\n");

    /* Deklarasi Variabel Awal */
    authenticated = false;

    /* Tampilan Awal */
    intro();
    
    /* Inialisasi: Load, Register, Login */
    inisialisasi(&listUser, &listEmail);
    
    /* Program Utama */
    do {
        if (authenticated){
             do {
                menu();
                Word input = perintah();
                if (isEqual(input, "BUAT_DRAFT")) {
                    StartDraftEmail();
                } else if (isEqual(input, "INBOX")) {
                    StartInbox();
                } else if (isEqual(input, "STATUS_KEPENTINGAN")) {
                    StartStatusKepentingan();
                } else if (isEqual(input, "NOTIFIKASI")) {
                    StartNotifikasi();
                } else if (isEqual(input, "SAVE")) {
                    SaveConfig();
                } else if (isEqual(input, "LOGOUT")) {
                    LogoutUser();
                } else if (isEqual(input, "BALAS_EMAIL")) {
                    StartBalasEmail();
                } else {
                    red(); printf("Masukan tidak valid!\n"); defaultp();
                }
                sleep(2);
                system("clear");
            } while (authenticated);    
        }

        do {
            menuNonAuth();
            Word input = perintah();
            if (isEqual(input, "SAVE")) {
                SaveConfig();
            } else if (isEqual(input, "LOAD")) {
                inisialisasi(&listUser, &listEmail);
            } else if (isEqual(input, "QUIT")) {
                ExitProgram();
            } else {
                red(); printf("Masukan tidak valid!\n"); defaultp();
            }
            sleep(2);
            system("clear");
        } while (!authenticated);
        
    } while (1);
    
    return 0;
}