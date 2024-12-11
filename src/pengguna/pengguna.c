#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../globals.h"
#include "pengguna.h"
#include "../program/load.h"

/*** REGISTER ***/
void registerUser(){
    boolean emailValid = false;
    boolean passwordValid = false;
    char *emailReg; char* passReg;

    /*Input Email*/
    do {
        printf("Masukkan email address: ");
        STARTWORD();
        emailReg = toString(currentWord);
        // Validasi Email
        if (lenWord(emailReg) > 255) {
            printf("Panjang email maksimal 255 karakter.\n");
        } else if (!isEmailValid(emailReg)) {
            printf("Email tidak valid!\n");
        } else if (idUser(listUser, currentWord) != -1) {
            printf("Email sudah digunakan, buat email lain.\n");
        } else {
            emailValid = true;
        }
    } while (!emailValid);

    /*Input Password*/
    do {
        printf("Masukkan kata sandi: ");
        STARTWORD();
        passReg = toString(currentWord);
        // Validasi Password
        if (currentWord.Length > 20) {
            printf("Gagal membuat password :(\n Panjang password maksimal adalah 20 Karakter.\n");
        } else {
            passwordValid = true;
        }
    } while (!passwordValid);
    
    // Save ID, Email, and Password to Config File
    if (passwordValid && emailValid) {
        /* Adjust the listUser */
        listUser.data[listUser.number].id = listUser.number + 1;
        listUser.data[listUser.number].email = emailReg;
        listUser.data[listUser.number].password = passReg;
        listUser.number ++;

        //welcome message
        printf("Akun berhasil didaftarkan! Silakan LOGIN untuk memulai menggunakan program.\n");
    }
}

void loginUser(){
    boolean emailValid = false;
    boolean passwordValid = false;
    char *emailLogin;
    int id;
    
    /* Input Email */
    printf("Masukkan email address: ");
    STARTWORD();
    //validasi email
    if (idUser(listUser, currentWord) == -1){
        printf("Email belum terdaftar!\n");
    } else {
        emailValid = true;
        emailLogin = toString(currentWord);
        id = idUser(listUser, currentWord);
    }

    if (emailValid){
         /* Input Password */
        do {
            printf("Masukkan password: ");
            STARTWORD();
            //validasi password
            if (!isEqual(currentWord, listUser.data[id].password)){
                printf("Password salah!\n");
            } else {
                passwordValid = true;
            }
        } while (!passwordValid);
    }

    if (passwordValid && emailValid) {
        user.id = id + 1;
        user.email = emailLogin;
        authenticated = true;
        green(); printf("Login berhasil, selamat datang di PurryMail!\n"); defaultp();
    }
}

void LogoutUser() {
    printf("Konfigurasi yang belum disimpan akan hilang setelah LOGOUT.\n");
    printf("LOGOUT dari program?\n");
    red(); printf("     --- YA\n"); defaultp();
    green(); printf("     --- TIDAK\n"); defaultp();
    Word input = perintah();
    if (isEqual(input, "YA")){
        printf("Keluar Purry Mail...\n");
        sleep(2);
        system("clear");
        authenticated = false;
        user.id = -1;
        user.email = '\0';
        printf("Terima kasih sudah menggunakan PurryMail! Sampai jumpa!\n");
    } else if (!isEqual(input, "TIDAK")){
        red();
        printf("Masukan tidak valid!");
        defaultp();
    }
    sleep(2);
    system("clear");
}

void autentikasiUser(){
    Word currentWord = perintah();

    if (isEqual(currentWord, "REGISTER") && listUser.number <= 20) {
        if (!authenticated){
            registerUser();
        } else {
            printf("Anda sudah LOGIN sebagai %s\n", user.email);
        }
    } else if (isEqual(currentWord, "LOGIN")) {
        if (!authenticated) {
            loginUser();
        } else {
            printf("Anda sudah LOGIN sebagai %s\n", user.email);
        }
    } else if (isEqual(currentWord, "QUIT")) {
        ExitProgram();
    } else if (isEqual(currentWord, "LOGOUT")) {
        if (authenticated){
            LogoutUser();
        } else {
            printf("Anda belum LOGIN!\n");
        }
    } else if (listUser.number > 20) {
        red(); printf("Sudah terdapat 20 pengguna, konfigurasi penuh!\n"); defaultp();
    } else {
        printf("Masukan tidak valid.\n");
    }
    sleep(2);
    system("clear");
}

/* REGEX */
//^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$

boolean isAlphaNumeric(char c){
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

boolean isLocalChar(char c){
    return isAlphaNumeric(c) || (c == '.') || (c == '_') ||(c == '%') || (c == '+') || (c == '-');
}

boolean isDomainChar(char c){
    return isAlphaNumeric(c) || (c == '.') || (c == '-');
}

boolean isTLDChar(char c){
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

boolean isEmailValid(char* email){
    char* c = email;
    //check local
    if(*c == '@'){return false;}
    while (*c != '@'){
        if (*c == '\0') {
            return false;
        } else if (!isLocalChar(*c)){
            return false;
        }
        c++;
    }
    c++;
    //check domain & count TLD length
    int countTLD = 0;
    boolean foundDot = false;
    if(*c == '.'){return false;}
    while (*c != '\0'){
        if(!isDomainChar(*c)){
            return false;
        }
        if (*c == '.'){
            foundDot = true;
            countTLD = 0;
        }
        c++, countTLD++;
    }
    if (!foundDot){return false;}
    //check tld
    if (countTLD <= 2) {
        return false;
    } else {
        int n = lenWord(email);
        for(int j = n - countTLD + 1; j < n; j++){
            if (!isTLDChar(email[j])){
                return false;
            }
        }
    }
    return true;
}

// Driver Regex
// int main() {
//     char *testEmails[] = {
//         "test.email@example.com",
//         "user@sub.domain.co",
//         "invalid-email.com",
//         "user@domain",
//         "@missing.local",
//         "missing@.domain",
//         "user@domain.c",
//     };

//     for (int i = 0; i < sizeof(testEmails) / sizeof(testEmails[0]); i++) {
//         printf("Testing: %s -> %s\n",
//                testEmails[i],
//                isEmailValid(testEmails[i]) ? "Valid" : "Invalid");
//     }

//     return 0;
// }


// Driver Pengguna
// int main(){
//     activeUser user;
//     boolean authenticated;

//     autentikasiUser(user, authenticated);

//     return 0;
// }