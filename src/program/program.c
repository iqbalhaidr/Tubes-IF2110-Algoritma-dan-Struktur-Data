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
    printf("Jangan lupa sertakan ';' di akhir yaa ~~~\n");
    defaultp();
}

void headerPurryMail() {
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
}

void headerBuatDraft(){
    printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("                   BUAT_DRAFT    \n");
    printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

/* Tampilan Menu Buat Draft */ 
void menuBuatDraft(){
    printf("Masukkan Menu: \n");
    yellow();
    printf("     --- UBAH_DRAFT\n");
    printf("     --- KIRIM_DRAFT\n");
    printf("     --- LIHAT_DRAFT\n");
    printf("     --- UNDO\n");
    printf("     --- REDO\n");
    printf("     --- KELUAR\n");
    printf("Jangan lupa sertakan ';' di akhir yaa ~~~\n");
    defaultp();
}

void headerInbox(){
    printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("                     INBOX    \n");
    printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

/* Tampilan Menu Inbox */ 
void menuInbox(){
    printf("Masukkan Menu: \n");
    yellow();
    printf("     --- DAFTAR_INBOX\n");
    printf("     --- LANJUT\n");
    printf("     --- SEBELUM\n");
    printf("     --- BACA_PESAN EMAILXXX\n");
    printf("     --- KELUAR\n");
    printf("XXX merupakan Email ID yang ingin diakses yaa\n");
    printf("Jangan lupa sertakan ';' di akhir yaa ~~~\n");
    defaultp();
}

void headerBalasPesan(){
    printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("                  BALAS_PESAN    \n");
    printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

/* Tampilan Menu Balas Pesan */ 
void menuBalasPesan(){
    printf("Masukkan Menu: \n");
    yellow();
    printf("     --- DAFTAR_INBOX\n");
    printf("     --- BACA_PESAN EMAILXXX\n");
    printf("     --- BACA_PESAN EMAILXXX\n");
    printf("     --- KELUAR\n");
    printf("XXX merupakan Email ID yang ingin diakses yaa\n");
    printf("Jangan lupa sertakan ';' di akhir yaa ~~~\n");
    defaultp();
}
