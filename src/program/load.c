#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "load.h"
#include "utility.h"
#include "../globals.h"
#include "program.h"
#include "utility.h"

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef _WIN32
#include <direct.h>  // For _mkdir on Windows
#else
    #include <unistd.h>  // For POSIX functions (e.g., access)
#endif

void inisialisasi(ListUser *listUser, ListEmail *listEmail) {
    printf("Masukkan folder konfigurasi untuk dimuat: ");

    STARTWORD();
    char *folderPath = toString(currentWord);

    if (!loadConfigfromFoler(folderPath, listUser, listEmail)){
        red(); printf("Gagal memuat file config dari %s.\n", folderPath); defaultp();
        printf("Exiting...\n");
        sleep(2);
        system("clear");
        exit(0);
    } else {
        green(); printf("Memuat konfigurasi Purry Mail...\n");
        sleep(1);
        printf("Memuat konfigurasi Purry Mail...\n");
        sleep(1);
        printf("Memuat konfigurasi Purry Mail...\n"); defaultp();
        sleep(3);
        system("clear");
        printf("Silakan REGISTER/LOGIN untuk memulai!\n");
        do {
            startMenu();
            autentikasiUser();
        } while (!authenticated);
    }
}

int loadConfigfromFoler(char *folderPath, ListUser *listUser, ListEmail *listEmail) {
    snprintf(fileUserPath, sizeof(fileUserPath), "./%s/pengguna.config", folderPath);
    if (!loadUser(fileUserPath, listUser)){
        return 0;
    }

    snprintf(fileEmailPath, sizeof(fileEmailPath), "./%s/email.config", folderPath);
    if (!loadEmail(fileEmailPath, listEmail)){
        return 0;
    }

    snprintf(fileUmumPath, sizeof(fileUmumPath), "./%s/umum.config", folderPath);
    if (!loadUmum(fileUmumPath, &pagination, &importantInteraction)){
        return 0;
    }
    return 1;
}

/* Memuat config umum */
int loadUmum(char *filePath, int *pagination, int *importantInteraction){
    int suc = StartWordFromFile(filePath);
    if (suc) {
        *pagination = stringToInt(toString(currentWord));
        ADVNewLine();
        *importantInteraction = stringToInt(toString(currentWord));
        return 1;
    }
    return 0;
}

/* Memuat list user */
int loadUser(char *filePath, ListUser *listUser){
    CreateListUser(listUser);
    char *id;
    int suc = StartWordFromFile(filePath);
    if (suc) {
        char *count = toString(currentWord); //banyaknya user
        listUser->number= stringToInt(count);
        for (int i = 0; i < listUser->number; i++){
            ADVNewLine();
            id = toString(currentWord);
            listUser->data[i].id = stringToInt(id);
            ADVNewLine();
            listUser->data[i].email = toString(currentWord);
            ADVNewLine();
            listUser->data[i].password = toString(currentWord);
        }
        return 1;
    }
    return 0;
    
}

/* Memuat list email */
int loadEmail(char* filePath, ListEmail *listEmail) {
    CreateListEmail(listEmail, 1000);
    char *temp;
    int suc = StartWordFromFile(filePath);
    if (suc) {
        char *count = toString(currentWord); //banyaknya email
        int numemail = stringToInt(count);
        emailType email;

        for (int i = 0; i < numemail; i++){
            ADVNewLine();
            temp = toString(currentWord);
            email.id = stringToInt(temp);
            
            ADVNewLine();
            temp = toString(currentWord);
            email.idPengirim = stringToInt(temp);

            ADVNewLine();
            temp = toString(currentWord);
            email.idPenerima = stringToInt(temp);

            ADVNewLine();
            temp = toString(currentWord);
            email.idCC = stringToInt(temp);

            ADVNewLine();
            email.timestamp = toString(currentWord);

            ADVNewLine();
            email.subyek = toString(currentWord);
            while (currentWord.TabWord[currentWord.Length - 1] == '\\') {
                email.subyek[currentWord.Length-1] = '\0';
               
                ADVNewLine();
                email.subyek = concat(email.subyek, " ");
                email.subyek = concat(email.subyek, toString(currentWord));
            }

            ADVNewLine();
            email.body = toString(currentWord);
            while (currentWord.TabWord[currentWord.Length - 1] == '\\') {
                email.body[currentWord.Length-1] = '\0';
               
                ADVNewLine();
                email.body = concat(email.body, " ");
                email.body = concat(email.body, toString(currentWord));
            }

            ADVNewLine();
            temp = toString(currentWord);
            email.reply = stringToInt(temp);

            ADVNewLine();
            temp = toString(currentWord);
            email.read = stringToInt(temp);

            ADVNewLine();
            temp = toString(currentWord);
            email.readCC = stringToInt(temp);

            addEmail(listEmail, email);
        }
        return 1;
    }
    return 0;
}



int isDirectoryExist(char *folderPath) {
    struct stat info;
    if (stat(folderPath, &info) != 0) {
        // Cannot access path, directory may not exist
        return 0;
    } else if (S_ISDIR(info.st_mode)) {
        // Path exists and is a directory
        return 1;
    }
    return 0;
}

int createDirectory(char *folderPath) {
    if (!isDirectoryExist(folderPath)) {
        #ifdef _WIN32
            if (_mkdir(folderPath) == 0) {
                printf("Folder berhasil dibuat!\n");
                return 0; // Directory successfully created
            } else {
                printf("Gagal membuat folder.\n");
                return -1; // Failed to create directory
            }
        #else
            if (mkdir(folderPath, 0755) == 0) {
                printf("Folder berhasil dibuat!\n");
                return 0; // Directory successfully created
            } else {
                printf("Gagal membuat folder.\n");
                return -1; // Failed to create directory
            }
        #endif
    }
    return 0; // Directory already exists
}

void SaveConfig(){
    /* Save User */
    char *folderPath; char fileSaveUserPath[256]; char fileSaveEmailPath[256]; char fileSaveUmumPath[256];
    printf("Masukkan nama folder penyimpanan: ");
    STARTWORD();

    folderPath = toString(currentWord);

    if (createDirectory(folderPath) != 0){
        return;
    }

    /* Save Umum */
    snprintf(fileSaveUmumPath, sizeof(fileSaveUmumPath), "./%s/umum.config", folderPath);
    FILE *fileSaveUmum = fopen(fileSaveUmumPath, "w");
    if (fileSaveUmum == NULL){
        printf("Gagal menyimpan konfigurasi :(\n");
        return;
    }
    fprintf(fileSaveUmum, "%d\n", pagination);
    fprintf(fileSaveUmum, "%d", importantInteraction);

    fclose(fileSaveUmum);

    /* Save User */

    snprintf(fileSaveUserPath, sizeof(fileSaveUserPath), "./%s/pengguna.config", folderPath);

    FILE *fileSaveUser = fopen(fileSaveUserPath, "w");
    if (fileSaveUser == NULL){
        printf("Gagal menyimpan konfigurasi :(\n");
        return;
    }
    //number of user
    fprintf(fileSaveUser, "%d\n", listUser.number);
    int k = 0;
    for (int i = 0; i <listUser.number; i++){
        fprintf(fileSaveUser, "%d\n", listUser.data[k].id);
        fprintf(fileSaveUser, "%s\n", listUser.data[k].email);
        fprintf(fileSaveUser, "%s", listUser.data[k].password);
        if (i < listUser.number - 1){
            fprintf(fileSaveUser, "\n");
        }
        k++;
    }
    fclose(fileSaveUser);

    /* Save Email */

    snprintf(fileSaveEmailPath, sizeof(fileSaveEmailPath), "./%s/email.config", folderPath);

    FILE *fileSaveEmail = fopen(fileSaveEmailPath, "w");
    if (fileSaveEmail == NULL){
        printf("Gagal menyimpan konfigurasi :(\n");
        return;
    }
    //number of email
    fprintf(fileSaveEmail, "%d\n", listEmail.number);
    k = 0;
    for (int i = 0; i <listEmail.number; i++){
        fprintf(fileSaveEmail, "%d\n", listEmail.data[k].id);
        fprintf(fileSaveEmail, "%d\n", listEmail.data[k].idPengirim);
        fprintf(fileSaveEmail, "%d\n", listEmail.data[k].idPenerima);
        fprintf(fileSaveEmail, "%d\n", listEmail.data[k].idCC);
        fprintf(fileSaveEmail, "%s\n", listEmail.data[k].timestamp);
        fprintf(fileSaveEmail, "%s\n", listEmail.data[k].subyek);
        fprintf(fileSaveEmail, "%s\n", listEmail.data[k].body);
        fprintf(fileSaveEmail, "%d\n", listEmail.data[k].reply);
        fprintf(fileSaveEmail, "%d\n", listEmail.data[k].read);
        fprintf(fileSaveEmail, "%d", listEmail.data[k].readCC);
        if (i < listEmail.number - 1){
            fprintf(fileSaveEmail, "\n");
        }
        k++;
    }
    fclose(fileSaveEmail);
    printf("File konfigurasi telah disimpan!\n");
}

void ExitProgram(){
    printf("Keluar dari program?\n");
    red(); printf("     --- YA\n"); defaultp();
    green(); printf("     --- TIDAK\n"); defaultp();
    if (isEqual(perintah(), "YA")){
        printf("Exiting...\n");
        sleep(2);
        system("clear");
        exit(0);
    }
}

/* DRIVER */
// int main(){
//     ListUser listUser;
//     CreateListUser(&listUser);
//     loadDataTry(fileUserPath, &listUser);

//     return 0;
// }