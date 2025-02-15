#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "program.h"
#include "../globals.h"

void intro(){
    system("clear");
    headerPurryMail();
    printf("\n");
    printf("Memulai program...\n"); sleep(1);
    printf("Memulai program...\n"); sleep(1);
    printf("Memulai program...\n"); sleep(1);
    sleep(2);
    system("clear");
}

/* Tampilan Menu Awal untuk Autentikasi */
void startMenu(){
    headerStartMenu();
    printf("Masukkan Opsi Masuk Program: \n");
    yellow(); bold();
    printf("     --- REGISTER\n");
    printf("     --- LOGIN\n");
    printf("     --- QUIT\n");
    defaultp();
}

/* Tampilan Menu Email */ 
void menu(){
    headerMenu();
    printf("Masukkan Menu: \n");
    yellow(); bold();
    printf("     --- BUAT_DRAFT\n");
    printf("     --- INBOX\n");
    printf("     --- STATUS_KEPENTINGAN\n");
    printf("     --- NOTIFIKASI\n");
    printf("     --- SAVE\n");
    printf("     --- LOGOUT\n");
    defaultp();
}

void menuNonAuth(){
    printf("Masukkan Menu: \n");
    yellow(); bold();
    printf("     --- REGISTER\n");
    printf("     --- LOGIN\n");
    printf("     --- SAVE\n");
    printf("     --- LOAD\n");
    printf("     --- QUIT\n");
    defaultp();
}

void headerPurryMail() {
    yellow(); 
    printf("--------------------------------------------------------------------------\n");
    printf(" ######                                    ##   ##             ##    ###    \n");
    printf(" ##   ##                                   ##   ##                    ##    \n");
    printf(" ##   ##  ##   ##  ## ###  ## ###  ##  ##  ### ###   ######  ####     ##    \n");
    printf(" ######   ##   ##  ###     ###     ##  ##  ## # ##  ##   ##    ##     ##    \n");
    printf(" ##       ##   ##  ##      ##      ##  ##  ## # ##  ##   ##    ##     ##    \n");
    printf(" ##       ##  ###  ##      ##       #####  ##   ##  ##  ###    ##     ##    \n");
    printf(" ##        ### ##  ##      ##          ##  ##   ##   ### ##  ######  ####   \n");
    printf("                                    ####                                       \n");
    printf("--------------------------------------------------------------------------\n");
    defaultp();
}

void headerBuatDraft(){
    sleep(1);
    system("clear");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("                 DRAFT EMAIL    \n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

/* Tampilan Menu Buat Draft */ 
void menuBuatDraft(){
    printf("Masukkan Menu: \n");
    yellow(); bold();
    printf("     --- UBAH_DRAFT\n");
    printf("     --- KIRIM_DRAFT\n");
    printf("     --- LIHAT_DRAFT\n");
    printf("     --- UNDO\n");
    printf("     --- REDO\n");
    printf("     --- KELUAR\n");
    defaultp();
    printf("Jangan lupa sertakan ';' di akhir yaa ~~~\n");
}

void headerInbox(){
    sleep(1);
    // system("clear");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("                    INBOX    \n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n");
    defaultp();
}

void headerStartMenu(){
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("                  MENU AWAL    \n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void headerMenu(){
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("           MENU UTAMA PURRY MAIL    \n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

/* Tampilan Menu Inbox */ 
void menuInbox(){
    printf("Masukkan Menu: \n");
    yellow(); bold();
    printf("     --- DAFTAR_INBOX\n");
    printf("     --- LANJUT\n");
    printf("     --- SEBELUM\n");
    printf("     --- BACA_PESAN EMAILXXX\n");
    printf("     --- BALAS_PESAN EMAILXXX\n");
    printf("     --- DAFTAR_STARRED\n");
    printf("     --- LANJUT_STAR\n");
    printf("     --- SEBELUM_STAR\n");
    printf("     --- STAR EMAILXXX\n");
    printf("     --- UNSTAR EMAILXXX\n");
    printf("     --- KELUAR\n");
    defaultp();
    printf("XXX merupakan Email ID yang ingin diakses yaa\n");
    printf("Jangan lupa sertakan ';' di akhir yaa ~~~\n");
}

void headerStatusKepentingan(){
    sleep(1);
    system("clear");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("             STATUS KEPENTINGAN    \n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}
