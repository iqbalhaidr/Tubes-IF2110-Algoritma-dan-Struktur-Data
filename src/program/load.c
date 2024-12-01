#include <stdio.h>
#include <stdlib.h>
#include "load.h"
#include "utility.h"
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
    char filePath[256];

    snprintf(filePath, sizeof(filePath), "./%s/pengguna.config", folderPath);
    if (!loadUser(filePath, listUser)){
        return 0;
    }

    snprintf(filePath, sizeof(filePath), "./%s/email.config", folderPath);
    if (!loadEmail(filePath, listEmail)){
        return 0;
    }

    return 1;
}

/* Memuat list user */
int loadUser(char* fileUser, ListUser *listUser) {
    fileUser = "./config/pengguna.config";
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

        addUser(listUser, user); ///pos
        lineCount++;
    }
    listUser->number = lineCount;
    fclose(file);
    return 1;
}

/* Memuat list email */
int loadEmail(char* fileEmail, ListEmail *listEmail) {
    fileEmail = "./config/email.config";
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

/* DRIVER */
// int main(){
//     ListUser listUser = loadUser();
//     printf("LIST USER:\n");
//     printListUser(listUser);
//     printf("listnum user: %d\n", listUser.number);

//     ListEmail listEmail = loadEmail();
//     printListEmail(listEmail);
//     printf("listnum email: %d\n", listEmail.number);

//     return 0;
// }