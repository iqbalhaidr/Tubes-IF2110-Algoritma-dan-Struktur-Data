/* Kelompok   : IF2110-01-B (K01-B)           */
/* Anggota 1  : 13523019 - Shannon A A Lie    */
/* Anggota 2  : 13523021 - M Raihan Nazhim O  */
/* Anggota 3  : 13523025 - Joel Hotlan H S    */
/* Anggota 4  : 13523043 - Najwa Kahani F     */
/* Anggota 5  : 13523111 - M Iqbal Haidar     */
/* Tanggal    : Rabu, 4 Desember 2024         */
/* Proyek     : Alstrukdat - TB1 - Purry Mail */
/* Bagian     : F04 - Draft Email - C         */
/* File       : draftemail.c                  */
/* Deskripsi  : F04A -- F04G [DRAFT EMAIL]    */
/* PJ F04     : 13523021 - M Raihan Nazhim O  */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./modules/datetime.h"
#include "./modules/listuser.h"
#include "./modules/listemail.h"
#include "./modules/mesinkarakter.h"
#include "./modules/mesinkata.h"
#include "./modules/listdin.h"
#include "./modules/stack.h"
#include "loadData.c"

int FindIdBasedEmail(ListUser l , Word e) {
    for (int i = 0 ; i < l.number ; i++) {
        if (isEqual(e , l.data[i].email)) {
            return l.data[i].id;
        }
    }
    return IDX_UNDEF;
}

char* FindEmailBasedId(ListUser l , int e) {
    for (int i = 0 ; i < l.number ; i++) {
        if (l.data[i].id == e) {
            return l.data[i].email;
        }
    }
    return "";
}

emailType BuatDraftEmail(int id_user , ListUser list_user) {
    emailType email;
    email.id = -1;
    email.idPengirim = id_user;
    email.idPenerima = -1;
    email.idCC = -1;
    email.timestamp = "";
    email.subyek = "";
    email.body = "";
    email.reply = -1;
    email.read = false;
    email.readCC = false;
    char* stop = "STOP";
    boolean check = true;
    int id_penerima , id_cc;
    while (check) {
        printf("Masukkan Email Penerima : ");
        STARTWORD();
        while (!EndWord) {
            ADVWORD();
        }
        id_penerima = FindIdBasedEmail(list_user , currentWord);
        if (isEqual(currentWord , stop)) {
            return email;
        } else if (id_penerima == IDX_UNDEF || id_penerima == id_user) {
            printf("Pengguna email dengan alamat %s tidak ditemukan.\n" , currentWord.TabWord);
        } else if (id_penerima == id_user) {
            printf("Penerima pesan tidak boleh sama dengan pengirim pesan.\n" , currentWord.TabWord);
        } else {
            email.idPenerima = id_penerima;
            break;
        }
        printf("Masukkan \"STOP\" untuk force stop pembuatan draft email.\n");
    }
    while (check) {
        printf("Masukkan Penerima CC : ");
        STARTWORD();
        while (!EndWord) {
            ADVWORD();
        }
        id_cc = FindIdBasedEmail(list_user , currentWord);
        if (currentWord.Length == 0) {
            email.idCC = id_cc;
            break;
        } else {
            if (isEqual(currentWord , stop)) {
                return email;
            } else if (id_cc == IDX_UNDEF) {
                printf("Pengguna email dengan alamat %s tidak ditemukan.\n" , currentWord.TabWord);
            } else if (id_cc == id_user) {
                printf("Penerima CC tidak boleh sama dengan pengirim pesan.\n");
            } else if (id_cc == id_penerima) {
                printf("Penerima CC tidak boleh sama dengan penerima pesan.\n");
            } else {
                email.idCC = id_cc;
                break;
            }
        }
        printf("Masukkan \"STOP\" untuk force stop pembuatan draft email.\n");
    }
    while (check) {
        printf("Masukkan Subjek : ");
        ListDin list_subyek;
        CreateListDin(&list_subyek , 250);
        STARTWORDDraft();
        for (int i = 0 ; i < currentWord.Length ; i++) {
            if (!isFull(list_subyek)) {
                insertLast(&list_subyek , currentWord.TabWord[i]);
            } else {
                check = false;
            }
            
        }
        if (currentWord.TabWord[currentWord.Length - 1] != '\n') {
            if (!isFull(list_subyek)) {
                insertLast(&list_subyek , BLANK);
            } else {
                check = false;
            }
        }
        while (!EndWord) {
            ADVWORDDraft();
            for (int i = 0 ; i < currentWord.Length ; i++) {
                if (!isFull(list_subyek)) {
                    insertLast(&list_subyek , currentWord.TabWord[i]);
                } else {
                    check = false;
                }
            }
            if (currentWord.TabWord[currentWord.Length - 1] != '\n') {
                if (!isFull(list_subyek)) {
                    insertLast(&list_subyek , BLANK);
                } else {
                    check = false;
                }
            }
        }
        if (isEqual(currentWord , stop)) {
            return email;
        } else if (isEmpty(list_subyek) || !check) {
            check = true;
            dealocateList(&list_subyek);
            printf("Subjek tidak valid karena kosong / melebihi batas 250 karakter.\n");
        } else {
            compressList(&list_subyek);
            for (int i = 0 ; i < NEFF(list_subyek) ; i++) {
                email.subyek += ELMTLD(list_subyek , i);
            }
            dealocateList(&list_subyek);
            break;
        }
        printf("Masukkan \"STOP\" untuk force stop pembuatan draft email.\n");
    }
    while (check) {
        printf("Masukkan Body : ");
        ListDin list_body;
        CreateListDin(&list_body , 1000);
        STARTWORDDraft();
        for (int i = 0 ; i < currentWord.Length ; i++) {
            if (!isFull(list_body)) {
                insertLast(&list_body , currentWord.TabWord[i]);
            } else {
                check = false;
            }
            
        }
        if (currentWord.TabWord[currentWord.Length - 1] != '\n') {
            if (!isFull(list_body)) {
                insertLast(&list_body , BLANK);
            } else {
                check = false;
            }
        }
        while (!EndWord) {
            ADVWORDDraft();
            for (int i = 0 ; i < currentWord.Length ; i++) {
                if (!isFull(list_body)) {
                    insertLast(&list_body , currentWord.TabWord[i]);
                } else {
                    check = false;
                }
            }
            if (currentWord.TabWord[currentWord.Length - 1] != '\n') {
                if (!isFull(list_body)) {
                    insertLast(&list_body , BLANK);
                } else {
                    check = false;
                }
            }
        }
        if (isEqual(currentWord , stop)) {
            return email;
        } else if (isEmpty(list_body) || !check) {
            check = true;
            dealocateList(&list_body);
            printf("Body tidak valid karena kosong / melebihi batas 1000 karakter.\n");
        } else {
            compressList(&list_body);
            for (int i = 0 ; i < NEFF(list_body) ; i++) {
                email.body += ELMTLD(list_body , i);
            }
            dealocateList(&list_body);
            break;
        }
        printf("Masukkan \"STOP\" untuk force stop pembuatan draft email.\n");
    }
    return email;
}

void BatalDraftEmail(emailType *email) {
    (*email).id = -1;
    (*email).idPengirim = -1;
    (*email).idPenerima = -1;
    (*email).idCC = -1;
    (*email).timestamp = "";
    (*email).subyek = "";
    (*email).body = "";
    (*email).reply = -1;
    (*email).read = false;
    (*email).readCC = false;
    printf("Draft email berhasil dibatalkan!\n");
}

void UbahDraftEmail(emailType *email , int id_user , ListUser list_user) {
    char* stop = "STOP";
    boolean check = true;
    int id_penerima , id_cc;
    while (check) {
        printf("Masukkan Email Penerima : ");
        STARTWORD();
        while (!EndWord) {
            ADVWORD();
        }
        id_penerima = FindIdBasedEmail(list_user , currentWord);
        if (isEqual(currentWord , stop)) {
            return;
        } else if (id_penerima == IDX_UNDEF || id_penerima == id_user) {
            printf("Pengguna email dengan alamat %s tidak ditemukan.\n" , currentWord.TabWord);
        } else if (id_penerima == id_user) {
            printf("Penerima pesan tidak boleh sama dengan pengirim pesan.\n" , currentWord.TabWord);
        } else {
            (*email).idPenerima = id_penerima;
            break;
        }
        printf("Masukkan \"STOP\" untuk force stop pembuatan draft email.\n");
    }
    while (check) {
        printf("Masukkan Penerima CC : ");
        STARTWORD();
        while (!EndWord) {
            ADVWORD();
        }
        id_cc = FindIdBasedEmail(list_user , currentWord);
        if (currentWord.Length == 0) {
            (*email).idCC = id_cc;
            break;
        } else {
            if (isEqual(currentWord , stop)) {
                return;
            } else if (id_cc == IDX_UNDEF) {
                printf("Pengguna email dengan alamat %s tidak ditemukan.\n" , currentWord.TabWord);
            } else if (id_cc == id_user) {
                printf("Penerima CC tidak boleh sama dengan pengirim pesan.\n");
            } else if (id_cc == id_penerima) {
                printf("Penerima CC tidak boleh sama dengan penerima pesan.\n");
            } else {
                (*email).idCC = id_cc;
                break;
            }
        }
        printf("Masukkan \"STOP\" untuk force stop pembuatan draft email.\n");
    }
    while (check) {
        printf("Masukkan Subjek : ");
        ListDin list_subyek;
        CreateListDin(&list_subyek , 250);
        STARTWORD();
        for (int i = 0 ; i < currentWord.Length ; i++) {
            if (!isFull(list_subyek)) {
                insertLast(&list_subyek , currentWord.TabWord[i]);
            } else {
                check = false;
            }
            
        }
        if (currentWord.TabWord[currentWord.Length - 1] != '\n') {
            if (!isFull(list_subyek)) {
                insertLast(&list_subyek , BLANK);
            } else {
                check = false;
            }
        }
        while (!EndWord) {
            ADVWORD();
            for (int i = 0 ; i < currentWord.Length ; i++) {
                if (!isFull(list_subyek)) {
                    insertLast(&list_subyek , currentWord.TabWord[i]);
                } else {
                    check = false;
                }
            }
            if (currentWord.TabWord[currentWord.Length - 1] != '\n') {
                if (!isFull(list_subyek)) {
                    insertLast(&list_subyek , BLANK);
                } else {
                    check = false;
                }
            }
        }
        if (isEqual(currentWord , stop)) {
            return;
        } else if (isEmpty(list_subyek) || !check) {
            check = true;
            dealocateList(&list_subyek);
            printf("Subjek tidak valid karena kosong / melebihi batas 250 karakter.\n");
        } else {
            compressList(&list_subyek);
            for (int i = 0 ; i < NEFF(list_subyek) ; i++) {
                (*email).subyek += ELMTLD(list_subyek , i);
            }
            dealocateList(&list_subyek);
            break;
        }
        printf("Masukkan \"STOP\" untuk force stop perubahan draft email.\n");
    }
    while (check) {
        printf("Masukkan Body : ");
        ListDin list_body;
        CreateListDin(&list_body , 1000);
        STARTWORD();
        for (int i = 0 ; i < currentWord.Length ; i++) {
            if (!isFull(list_body)) {
                insertLast(&list_body , currentWord.TabWord[i]);
            } else {
                check = false;
            }
            
        }
        if (currentWord.TabWord[currentWord.Length - 1] != '\n') {
            if (!isFull(list_body)) {
                insertLast(&list_body , BLANK);
            } else {
                check = false;
            }
        }
        while (!EndWord) {
            ADVWORD();
            for (int i = 0 ; i < currentWord.Length ; i++) {
                if (!isFull(list_body)) {
                    insertLast(&list_body , currentWord.TabWord[i]);
                } else {
                    check = false;
                }
            }
            if (currentWord.TabWord[currentWord.Length - 1] != '\n') {
                if (!isFull(list_body)) {
                    insertLast(&list_body , BLANK);
                } else {
                    check = false;
                }
            }
        }
        if (isEqual(currentWord , stop)) {
            return;
        } else if (isEmpty(list_body) || !check) {
            check = true;
            dealocateList(&list_body);
            printf("Body tidak valid karena kosong / melebihi batas 1000 karakter.\n");
        } else {
            compressList(&list_body);
            for (int i = 0 ; i < NEFF(list_body) ; i++) {
                (*email).body += ELMTLD(list_body , i);
            }
            dealocateList(&list_body);
            break;
        }
        printf("Masukkan \"STOP\" untuk force stop perubahan draft email.\n");
    }
}

void KirimDraftEmail(ListEmail *list_email , emailType *email) {
    Datetime t;
    CreateDatetime(&t);
    getDatetime(&t);
    char time_stamp[20];
    time_stamp[0] = '0' + (t.year / 1000) % 10;
    time_stamp[1] = '0' + (t.year / 100) % 10;
    time_stamp[2] = '0' + (t.year / 10) % 10;
    time_stamp[3] = '0' + t.year % 10;
    time_stamp[4] = '-';
    time_stamp[5] = '0' + (t.month / 10) % 10;
    time_stamp[6] = '0' + t.month % 10;
    time_stamp[7] = '-';
    time_stamp[8] = '0' + (t.day / 10) % 10;
    time_stamp[9] = '0' + t.day % 10;
    time_stamp[10] = ' ';
    time_stamp[11] = '0' + (t.hour / 10) % 10;
    time_stamp[12] = '0' + t.hour % 10;
    time_stamp[13] = '.';
    time_stamp[14] = '0' + (t.minute / 10) % 10;
    time_stamp[15] = '0' + t.minute % 10;
    time_stamp[16] = '.';
    time_stamp[17] = '0' + (t.second / 10) % 10;
    time_stamp[18] = '0' + t.second % 10;
    time_stamp[19] = '\0';
    (*email).id = (*list_email).number;
    (*email).timestamp = time_stamp;
    addEmail(&*list_email , *email);
    (*email).id = -1;
    (*email).idPengirim = -1;
    (*email).idPenerima = -1;
    (*email).idCC = -1;
    (*email).timestamp = "";
    (*email).subyek = "";
    (*email).body = "";
    (*email).reply = -1;
    (*email).read = false;
    (*email).readCC = false;
    printf("Draft Email berhasil dikirim!\n");
}

void LihatDraftEmail(ListUser list_user , emailType email) {
    if (email.idPenerima != -1) {
        char* email_penerima = FindEmailBasedId(list_user , email.idPenerima);
        printf("Email Penerima : %s\n" , email_penerima);
    } else {
        printf("Email Penerima : <Tidak Ada>\n");
    }
    if (email.idCC != -1) {
        char* email_cc = FindEmailBasedId(list_user , email.idCC);
        printf("Penerima CC : %s\n" , email_cc);
    } else {
        printf("Penerima CC : <Tidak Ada>\n");
    }
    if (email.subyek != "") {
        printf("Subjek : %s\n" , email.subyek);
    } else {
        printf("Subjek : <Tidak Ada>\n");
    }
    if (email.body != "") {
        printf("Body : %s\n" , email.body);
    } else {
        printf("Body : <Tidak Ada>\n");
    }
}

void UndoDraftEmail(emailType *email , Stack *stack_main , Stack *stack_temp) {
    if (!IsEmptyStack(*stack_main)) {
        emailType email_temp;
        Pop(&*stack_main , &email_temp);
        if (IsEmptyStack(*stack_main)) {
            printf("Belum ada perubahan yang dapat di-undo.\n");
            Push(&*stack_main , email_temp);
        } else {
            Push(&*stack_temp , email_temp);
            *email = InfoTop(*stack_main);
            printf("Perubahan berhasil di-undo.\n");
        }
    } else {
        printf("Belum ada perubahan yang dapat di-undo.\n");
    }
}

void RedoDraftEmail(emailType *email , Stack *stack_main , Stack *stack_temp) {
    if (!IsEmptyStack(*stack_temp)) {
        emailType email_temp;
        Pop(&*stack_temp , &email_temp);
        Push(&*stack_main , email_temp);
        *email = InfoTop(*stack_main);
        printf("Perubahan berhasil di-redo.\n");
    } else {
        printf("Belum ada perubahan yang dapat di-redo.\n");
    }
}

void DraftEmail(int id_user , ListUser list_user , ListEmail list_email) {
    printf("==================================\n");
    printf("SELAMAT DATANG DI MENU DRAFT EMAIL\n");
    char* buat_draft = "BUAT_DRAFT";
    char* ubah_draft = "UBAH_DRAFT";
    char* lihat_draft = "LIHAT_DRAFT";
    char* kirim_draft = "KIRIM_DRAFT";
    char* undo = "UNDO";
    char* redo = "REDO";
    char* batal = "BATAL";
    Stack stack_main , stack_temp;
    CreateEmpty(&stack_main);
    CreateEmpty(&stack_temp);
    emailType email = BuatDraftEmail(id_user , list_user);
    Push(&stack_main , email);
    while (true) {
        printf(">> ");
        STARTWORD();
        while (!EndWord) {
            ADVWORD();
        }
        if (isEqual(currentWord , buat_draft)) {
            printf("Maaf, sudah ada draft terbuat! Silahkan finalisasi draft yang sudah dibuat.\n");
        } else if (isEqual(currentWord , ubah_draft)) {
            UbahDraftEmail(&email , id_user , list_user);
            Push(&stack_main , email);
        } else if (isEqual(currentWord , lihat_draft)) {
            LihatDraftEmail(list_user , email);
        } else if (isEqual(currentWord , kirim_draft)) {
            KirimDraftEmail(&list_email , &email);
        } else if (isEqual(currentWord , undo)) {
            UndoDraftEmail(&email , &stack_main , &stack_temp);
        } else if (isEqual(currentWord , redo)) {
            RedoDraftEmail(&email , &stack_main , &stack_temp);
        } else if (isEqual(currentWord , batal)) {
            BatalDraftEmail(&email);
            return;
        } else {
            printf("Perintah Tidak Valid. Masukkan \"BATAL\" untuk kembali ke menu utama.\n");
        }
    }
}