#include <stdio.h>
#include <stdlib.h>
#include "./modules/boolean.h"
#include "./datatypes/listuser.c"
#include "./datatypes/listemail.c"

const char *fileUser = "../config/pengguna.config";
const char *fileEmail = "../config/email.config";

#define CAPACITY_CHAR_USER 256
#define CAPACITY_CHAR_EMAIL 1001
char* storedWord;

/* String to Integer */
int stringToInt(char* str) {
    int result = 0, sign = 1, i = 0;
    
     if (str[0] == '-') {
        sign = -1; i++;
    }
    
    while (str[i] != '\0') {
        result = result * 10 + (str[i] - '0'); i++;
    } 
    return sign * result;
}

/* Panjang Kata */
int lenWord(char* word) {
    int i = 0;
    while (word[i] != '\0') {
        i++;
    }
    return i;
}

/* Store word yang dibaca pada file */
char* store(char *word){
    storedWord = (char *) malloc(CAPACITY_CHAR_EMAIL);
    int i = 0;
    while (word[i] != '\0'){
        storedWord[i] = word[i];
        i++;
    }
    storedWord[i] = '\0';
    return storedWord;
}

/* Mengembalikan list user */
ListUser loadUser() {
    FILE *file = fopen(fileUser, "r");
    char word[CAPACITY_CHAR_USER];

    /* Read First Line */
    fscanf(file, "%5s", word);

    ListUser listUser;
    CreateListUser(&listUser);
    int lineCount = 0;

    while(fscanf(file, "%255s", word) == 1){
        userType user;
        user.id = stringToInt(word);

        fscanf(file, "%255s", word);
        user.email = store(word);

        fscanf(file, "%255s", word);
        user.password = store(word);

        addUser(&listUser, user);
        lineCount++;
    }
    listUser.number = lineCount;
    return listUser;
}

/* Mengembalikan list email */
ListEmail loadEmail() {
    FILE *file = fopen(fileEmail, "r");
    char word[CAPACITY_CHAR_EMAIL];

    /* Read First Line */
    fscanf(file, "%1000[^\n]\n", word);

    ListEmail listEmail;
    CreateListEmail(&listEmail, 10);
    int lineCount = 0;

    while(fscanf(file, "%1000[^\n]\n", word) != EOF){
        emailType email;
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

        addEmail(&listEmail, email);
        lineCount++;
    }
    listEmail.number = lineCount;
    return listEmail;
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