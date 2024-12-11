#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "program.h"
#include "../globals.h"

void intro(){
    printf("Selamat datang di PurryMail!\n");
    printf("\n");
    // printf("Memulai program...\n"); sleep(1);
    // printf("Memulai program...\n"); sleep(1);
    // printf("Memulai program...\n"); sleep(1);
    // sleep(2);
    system("clear");
}

/* Tampilan Menu Awal untuk Autentikasi */
void startMenu(){
    printf("Masukkan Opsi Masuk Program: \n");
    yellow();
    printf("     --- REGISTER\n");
    printf("     --- LOGIN\n");
    printf("     --- QUIT\n");
    defaultp();
}

/* Tampilan Menu Email */ 
void menu(){
    printf("Masukkan Menu: \n");
    yellow();
    printf("     --- BUAT_DRAFT\n");
    printf("     --- INBOX\n");
    printf("     --- BALAS_EMAIL\n");
    printf("     --- STATUS_KEPENTINGAN\n");
    printf("     --- NOTIFIKASI\n");
    printf("     --- SAVE\n");
    printf("     --- LOGOUT\n");
    defaultp();
}

void menuNonAuth(){
    printf("Masukkan Menu: \n");
    yellow();
    printf("     --- REGISTER\n");
    printf("     --- LOGIN\n");
    printf("     --- SAVE\n");
    printf("     --- LOAD\n");
    printf("     --- QUIT\n");
    defaultp();
}