#include <stdio.h>
#include <stdlib.h>
#include "load.h"
#include "utility.h"
#include "../globals.h"
#include "../modules.h"

int inisialisasi(ListUser *listUser, ListEmail *listEmail) {
    printf("Selamat datang di PurryMail!\n");
    printf("\n");
    printf("Masukkan folder konfigurasi untuk dimuat: ");

    STARTWORD();
    char *folderPath = toString(currentWord);
    if (!loadConfigfromFoler(folderPath, listUser, listEmail)){
        printf("Gagal memuat file config dari %s\n", folderPath);
        return 0;
    } else {
        printf("Silakan REGISTER/LOGIN untuk memulai!\n");
    }
    return 1;
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

    return 1;
}

/* Memuat list user */
int loadUser(char* fileUser, ListUser *listUser) {
    FILE *file = fopen(fileUser, "r");
    char word[CAPACITY_CHAR_USER];

    if (file == NULL) {
        printf("File %s gagal dimuat!\n", fileUser);
        return 0;
    }

    /* Read First Line */
    fscanf(file, "%5s", word);

    int lineCount = 0;

    while(fscanf(file, "%255s", word) == 1){
        userType user;
        user.id = stringToInt(word);

        fscanf(file, "%255s", word);
        user.email = store(word);

        fscanf(file, "%255s", word);
        user.password = store(word);

        addUser(listUser, user);
        lineCount++;
    }
    listUser->number = lineCount;
    fclose(file);
    return 1;
}

/* Memuat list email */
int loadEmail(char* fileEmail, ListEmail *listEmail) {
    FILE *file = fopen(fileEmail, "r");
    char word[CAPACITY_CHAR_EMAIL];

    if (file == NULL) {
        printf("File %s gagal dimuat!\n", fileEmail);
        return 0;
    }

    /* Read First Line */
    fscanf(file, "%1000[^\n]\n", word);

    int lineCount = 0;
    emailType email;

    while(fscanf(file, "%1000[^\n]\n", word) != EOF){
        email.id = stringToInt(word);

        fscanf(file, "%1000[^\n]\n", word);  
        email.idPengirim = stringToInt(word);

        fscanf(file, "%1000[^\n]\n", word);
        email.idPenerima = stringToInt(word);

        fscanf(file, "%1000[^\n]\n", word);
        email.idCC = stringToInt(word);

        fscanf(file, "%1000[^\n]\n", word);
        email.timestamp = store(word);

        fscanf(file, "%1000[^\n]\n", word);
        email.subyek = store(word);

        fscanf(file, "%1000[^\n]\n", word);
        //handle \\ for new line in email.config
        email.body = store(word);

        fscanf(file, "%1000[^\n]\n", word);
        email.reply = stringToInt(word);

        fscanf(file, "%1000[^\n]\n", word);
        email.read = *store(word) - '0';

        fscanf(file, "%1000[^\n]\n", word);
        email.readCC = *store(word) - '0';

        addEmail(listEmail, email);
        lineCount++;
    }
    listEmail->number = lineCount;
    fclose(file);

    return 1;
}

int saveConfig(){
    /* Save User */
    FILE *fileUser = fopen(fileUserPath, "w");
    if (fileUser == NULL){
        printf("Gagal menyimpan konfigurasi :(\n");
        return 0;
    }
    //number of user
    fprintf(fileUser, "%d\n", listUser.number);
    int k = 0;
    for (int i = 0; i <listUser.number; i++){
        fprintf(fileUser, "%d\n", listUser.data[k].id);
        fprintf(fileUser, "%s\n", listUser.data[k].email);
        fprintf(fileUser, "%s\n", listUser.data[k].password);
        k++;
    }
    fclose(fileUser);

    /* Save Email */
    FILE *fileEmail = fopen(fileEmailPath, "w");
    if (fileEmail == NULL){
        printf("Gagal menyimpan konfigurasi :(\n");
        return 0;
    }
    //number of email
    fprintf(fileEmail, "%d\n", listEmail.number);
    k = 0;
    for (int i = 0; i <listEmail.number; i++){
        fprintf(fileEmail, "%d\n", listEmail.data[k].id);
        fprintf(fileEmail, "%d\n", listEmail.data[k].idPengirim);
        fprintf(fileEmail, "%d\n", listEmail.data[k].idPenerima);
        fprintf(fileEmail, "%d\n", listEmail.data[k].idCC);
        fprintf(fileEmail, "%s\n", listEmail.data[k].timestamp);
        fprintf(fileEmail, "%s\n", listEmail.data[k].subyek);
        fprintf(fileEmail, "%s\n", listEmail.data[k].body);
        fprintf(fileEmail, "%d\n", listEmail.data[k].reply);
        fprintf(fileEmail, "%d\n", listEmail.data[k].read);
        fprintf(fileEmail, "%d\n", listEmail.data[k].readCC);
        k++;
    }
    fclose(fileEmail);
    printf("File konfigurasi telah disimpan!\n");
    return 1;
}

void readFileToArray(char* fileUser, ListUser *listUser){
    FILE *file = fopen(fileUser, "r");
    // char word[CAPACITY_CHAR_USER];

    if (file == NULL) {
        printf("File %s gagal dimuat!\n", fileUser);
        // return 0;
    }

    STARTWORD();
    char* readWord = toString(currentWord);
    printf("%s\n", readWord);
}

/* DRIVER */
// int main(){
//     readFileToArray(fileUserPath, &listUser);

//     return 0;
// }