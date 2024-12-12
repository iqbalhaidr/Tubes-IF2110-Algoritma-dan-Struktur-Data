#include <stdio.h>
#include <stdlib.h>
#include "draftemail.h"
#include "../globals.h"

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

int FindIdPengirimBasedIdEmail(ListEmail l , int e) {
    for (int i = 0 ; i < l.number ; i++) {
        if (l.data[i].id == e) {
            return l.data[i].idPengirim;
        }
    }
    return IDX_UNDEF;
}

char* FindSubyekBasedIdEmail(ListEmail l , int e) {
    for (int i = 0 ; i < l.number ; i++) {
        if (l.data[i].id == e) {
            return l.data[i].subyek;
        }
    }
    return "";
}

boolean CheckEmptyEmail(ListDin l) {
    for (int i = 0 ; i < l.nEff ; i++) {
        if (ELMTLD(l , i) != BLANK && ELMTLD(l , i) != '\n' && ELMTLD(l , i) != '\0') {
            return false;
        }
    }
    return true;
}

char* MakeNewSubyekEmail(int reply , char* email_old_subyek) {
    currentWord.TabWord[0] = 'R';
    currentWord.TabWord[1] = 'e';
    currentWord.TabWord[2] = '[';
    int idx = 3;
    while (reply > 0) {
        if (reply / 100 > 0) {
            currentWord.TabWord[idx] = '0' + (reply / 100);
            reply %= 100;
            idx++;
        } else if (reply / 10 > 0) {
            currentWord.TabWord[idx] = '0' + (reply / 10);
            reply %= 10;
            idx++;
        } else if (reply / 1 > 0) {
            currentWord.TabWord[idx] = '0' + (reply / 1);
            reply %= 1;
            idx++;
        }
    }
    currentWord.TabWord[idx++] = ']';
    currentWord.TabWord[idx++] = ':';
    currentWord.TabWord[idx++] = BLANK;
    for (int i = 0 ; i < lenWord(email_old_subyek) ; i++) {
        currentWord.TabWord[idx++] = email_old_subyek[i];
    }
    currentWord.TabWord[idx] = '\0';
    currentWord.Length = idx + 1;
    char* res = toString(currentWord);
    return res;
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
    email.starred = false;
    char* stop = "STOP";
    boolean check = true;
    int id_penerima , id_cc;
    while (check) {
        printf("Masukkan Email Penerima : ");
        STARTWORDDraft();
        for (int i = 0 ; i < currentWord.Length ; i++) {
            if (currentWord.TabWord[i] == '\n' || currentWord.TabWord[i] == BLANK) {
                check = false;
                break;
            }
        }
        id_penerima = FindIdBasedEmail(list_user , currentWord);
        if (!check) {
            check = true;
            printf("Input tidak valid, silakan ulangi.\n");
        } else if (isEqual(currentWord , stop)) {
            printf("Proses Pembuatan Draft Email berhasil di FORCE STOP dan tersimpan.\n");
            return email;
        } else if (currentWord.Length == 0) {
            printf("Tidak ada email yang dituju, silakan ulangi.\n");
        } else if (id_penerima == IDX_UNDEF) {
            printf("Pengguna email dengan alamat %s tidak ditemukan.\n" , currentWord.TabWord);
        } else if (currentWord.Length > 255) {
            printf("Email tidak valid karena melebihi batas 255 karakter.\n");
        } else {
            email.idPenerima = id_penerima;
            break;
        }
        printf("Masukkan \"STOP\" untuk force stop Pembuatan Draft Email.\n");
    }
    while (check) {
        printf("Masukkan Penerima CC : ");
        STARTWORDDraft();
        for (int i = 0 ; i < currentWord.Length ; i++) {
            if (currentWord.TabWord[i] == '\n' || currentWord.TabWord[i] == BLANK) {
                check = false;
                break;
            }
        }
        id_cc = FindIdBasedEmail(list_user , currentWord);
        if (currentWord.Length == 0) {
            email.idCC = id_cc;
            break;
        } else {
            if (!check) {
                check = true;
                printf("Input tidak valid, silakan ulangi.\n");
            } else if (isEqual(currentWord , stop)) {
                printf("Proses Pembuatan Draft Email berhasil di FORCE STOP dan tersimpan.\n");
                return email;
            } else if (id_cc == IDX_UNDEF) {
                printf("Pengguna email dengan alamat %s tidak ditemukan.\n" , currentWord.TabWord);
            } else if (id_cc == id_penerima) {
                printf("Penerima CC tidak boleh sama dengan penerima pesan.\n");
            } else if (currentWord.Length > 255) {
                printf("Email tidak valid karena melebihi batas 255 karakter.\n");
            } else {
                email.idCC = id_cc;
                break;
            }
        }
        printf("Masukkan \"STOP\" untuk force stop Pembuatan Draft Email.\n");
    }
    while (check) {
        printf("Masukkan Subjek : ");
        ListDin list_subyek;
        CreateListDin(&list_subyek , 250);
        STARTWORDDraft();
        for (int i = 0 ; i < currentWord.Length ; i++) {
            if (currentWord.TabWord[i] == '\n') {
                check = false;
            }
            if (!isFullLD(list_subyek)) {
                insertLast(&list_subyek , currentWord.TabWord[i]);
            }
        }
        if (isFullLD(list_subyek)) {
            expandList(&list_subyek , 1);
        }
        insertLast(&list_subyek , '\0');
        if (!check) {
            check = true;
            printf("Subjek tidak valid karena melebihi batas 1 baris.\n");
        } else if (isEqual(currentWord , stop)) {
            dealocateList(&list_subyek);
            printf("Proses Pembuatan Draft Email berhasil di FORCE STOP dan tersimpan.\n");
            return email;
        } else if (CheckEmptyEmail(list_subyek)) {
            printf("Subjek tidak valid karena kosong.\n");
        } else if (currentWord.Length > 250) {
            printf("Subjek tidak valid karena melebihi batas 250 karakter.\n");
        } else {
            email.subyek = toString(currentWord);
            break;
        }
        dealocateList(&list_subyek);
        printf("Masukkan \"STOP\" untuk force stop Pembuatan Draft Email.\n");
    }
    while (check) {
        printf("Masukkan Body : ");
        ListDin list_body;
        CreateListDin(&list_body , 1000);
        STARTWORDDraft();
        for (int i = 0 ; i < currentWord.Length ; i++) {
            if (!isFullLD(list_body)) {
                insertLast(&list_body , currentWord.TabWord[i]);
            }
        }
        if (isFullLD(list_body)) {
            expandList(&list_body , 1);
        }
        insertLast(&list_body , '\0');
        if (isEqual(currentWord , stop)) {
            dealocateList(&list_body);
            printf("Proses Pembuatan Draft Email berhasil di FORCE STOP dan tersimpan.\n");
            return email;
        } else if (CheckEmptyEmail(list_body)) {
            printf("Body tidak valid karena kosong.\n");
        } else if (over) {
            printf("Body tidak valid karena melebihi batas 1000 karakter.\n");
        } else {
            email.body = toString(currentWord);
            break;
        }
        dealocateList(&list_body);
        printf("Masukkan \"STOP\" untuk force stop Pembuatan Draft Email.\n");
    }
    printf("Draft Email berhasil dibuat.\n");
    return email;
}

emailType BuatDraftBalasEmail(int id_user , ListUser list_user , ListEmail list_email , int reply , int id_reply , int id_old) {
    emailType email;
    email.id = -1;
    email.idPengirim = id_user;
    email.idCC = -1;
    email.timestamp = "";
    email.body = "";
    email.reply = id_reply;
    email.read = false;
    email.readCC = false;
    email.starred = false;
    int id_penerima = FindIdPengirimBasedIdEmail(list_email , id_old);
    char* email_penerima = FindEmailBasedId(list_user , id_penerima);
    char* email_old_subyek = FindSubyekBasedIdEmail(list_email , id_old);
    char* email_subyek = MakeNewSubyekEmail(reply , email_old_subyek);
    email.idPenerima = id_penerima;
    email.subyek = email_subyek;
    char* stop = "STOP";
    boolean check = true;
    printf("Masukkan Email Penerima : %s\n" , email_penerima);
    while (check) {
        printf("Masukkan Penerima CC : ");
        STARTWORDDraft();
        for (int i = 0 ; i < currentWord.Length ; i++) {
            if (currentWord.TabWord[i] == '\n' || currentWord.TabWord[i] == BLANK) {
                check = false;
                break;
            }
        }
        int id_cc = FindIdBasedEmail(list_user , currentWord);
        if (currentWord.Length == 0) {
            email.idCC = id_cc;
            break;
        } else {
            if (!check) {
                check = true;
                printf("Input tidak valid, silakan ulangi.\n");
            } else if (isEqual(currentWord , stop)) {
                printf("Proses Pembuatan Draft Balas Email berhasil di FORCE STOP dan tersimpan.\n");
                return email;
            } else if (id_cc == IDX_UNDEF) {
                printf("Pengguna email dengan alamat %s tidak ditemukan.\n" , currentWord.TabWord);
            } else if (id_cc == id_penerima) {
                printf("Penerima CC tidak boleh sama dengan penerima pesan.\n");
            } else if (currentWord.Length > 255) {
                printf("Email tidak valid karena melebihi batas 255 karakter.\n");
            } else {
                email.idCC = id_cc;
                break;
            }
        }
        printf("Masukkan \"STOP\" untuk force stop Pembuatan Draft Balas Email.\n");
    }
    printf("Masukkan Subjek : %s\n" , email_subyek);
    while (check) {
        printf("Masukkan Body : ");
        ListDin list_body;
        CreateListDin(&list_body , 1000);
        STARTWORDDraft();
        for (int i = 0 ; i < currentWord.Length ; i++) {
            if (!isFullLD(list_body)) {
                insertLast(&list_body , currentWord.TabWord[i]);
            }
        }
        if (isFullLD(list_body)) {
            expandList(&list_body , 1);
        }
        insertLast(&list_body , '\0');
        if (isEqual(currentWord , stop)) {
            printf("Proses Pembuatan Draft Balas Email berhasil di FORCE STOP dan tersimpan.\n");
            dealocateList(&list_body);
            return email;
        } else if (CheckEmptyEmail(list_body)) {
            dealocateList(&list_body);
            printf("Body tidak valid karena kosong.\n");
        } else if (over) {
            dealocateList(&list_body);
            printf("Body tidak valid karena melebihi batas 1000 karakter.\n");
        } else {
            email.body = toString(currentWord);
            dealocateList(&list_body);
            break;
        }
        printf("Masukkan \"STOP\" untuk force stop Pembuatan Draft Balas Email.\n");
    }
    printf("Draft Balas Email berhasil dibuat.\n");
    return email;
}

void BatalDraftEmail(emailType *email , int reply) {
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
    (*email).starred = false;
    if (reply == 0) {
        printf("Draft Email berhasil dibatalkan!\n");
    } else {
        printf("Draft Balas Email berhasil dibatalkan!\n");
    }
}

void UbahDraftEmail(emailType *email , int id_user , ListUser list_user) {
    char* stop = "STOP";
    boolean check = true;
    int id_penerima , id_cc;
    while (check) {
        printf("Masukkan Email Penerima : ");
        STARTWORDDraft();
        for (int i = 0 ; i < currentWord.Length ; i++) {
            if (currentWord.TabWord[i] == '\n' || currentWord.TabWord[i] == BLANK) {
                check = false;
                break;
            }
        }
        id_penerima = FindIdBasedEmail(list_user , currentWord);
        if (!check) {
            check = true;
            printf("Input tidak valid, silakan ulangi.\n");
        } else if (isEqual(currentWord , stop)) {
            printf("Proses Ubah Draft Email berhasil di FORCE STOP dan tersimpan.\n");
            return;
        } else if (currentWord.Length == 0) {
            printf("Tidak ada email yang dituju, silakan ulangi.\n");
        } else if (id_penerima == IDX_UNDEF) {
            printf("Pengguna email dengan alamat %s tidak ditemukan.\n" , currentWord.TabWord);
        } else if (currentWord.Length > 255) {
            printf("Email tidak valid karena melebihi batas 255 karakter.\n");
        } else {
            (*email).idPenerima = id_penerima;
            break;
        }
        printf("Masukkan \"STOP\" untuk force stop Ubah Draft Email.\n");
    }
    while (check) {
        printf("Masukkan Penerima CC : ");
        STARTWORDDraft();
        for (int i = 0 ; i < currentWord.Length ; i++) {
            if (currentWord.TabWord[i] == '\n' || currentWord.TabWord[i] == BLANK) {
                check = false;
                break;
            }
        }
        id_cc = FindIdBasedEmail(list_user , currentWord);
        if (currentWord.Length == 0) {
            (*email).idCC = id_cc;
            break;
        } else {
            if (!check) {
                check = true;
                printf("Input tidak valid, silakan ulangi.\n");
            } else if (isEqual(currentWord , stop)) {
                printf("Proses Ubah Draft Email berhasil di FORCE STOP dan tersimpan.\n");
                return;
            } else if (id_cc == IDX_UNDEF) {
                printf("Pengguna email dengan alamat %s tidak ditemukan.\n" , currentWord.TabWord);
            } else if (id_cc == id_penerima) {
                printf("Penerima CC tidak boleh sama dengan penerima pesan.\n");
            } else if (currentWord.Length > 255) {
                printf("Email tidak valid karena melebihi batas 255 karakter.\n");
            } else {
                (*email).idCC = id_cc;
                break;
            }
        }
        printf("Masukkan \"STOP\" untuk force stop Ubah Draft Email.\n");
    }
    while (check) {
        printf("Masukkan Subjek : ");
        ListDin list_subyek;
        CreateListDin(&list_subyek , 250);
        STARTWORDDraft();
        for (int i = 0 ; i < currentWord.Length ; i++) {
            if (currentWord.TabWord[i] == '\n') {
                check = false;
            }
            if (!isFullLD(list_subyek)) {
                insertLast(&list_subyek , currentWord.TabWord[i]);
            }
        }
        if (isFullLD(list_subyek)) {
            expandList(&list_subyek , 1);
        }
        insertLast(&list_subyek , '\0');
        if (!check) {
            check = true;
            printf("Subjek tidak valid karena melebihi batas 1 baris.\n");
        } else if (isEqual(currentWord , stop)) {
            dealocateList(&list_subyek);
            printf("Proses Ubah Draft Email berhasil di FORCE STOP dan tersimpan.\n");
            return;
        } else if (CheckEmptyEmail(list_subyek)) {
            printf("Subjek tidak valid karena kosong.\n");
        } else if (currentWord.Length > 250) {
            printf("Subjek tidak valid karena melebihi batas 250 karakter.\n");
        } else {
            (*email).subyek = toString(currentWord);
            break;
        }
        dealocateList(&list_subyek);
        printf("Masukkan \"STOP\" untuk force stop Ubah Draft Email.\n");
    }
    while (check) {
        printf("Masukkan Body : ");
        ListDin list_body;
        CreateListDin(&list_body , 1000);
        STARTWORDDraft();
        for (int i = 0 ; i < currentWord.Length ; i++) {
            if (!isFullLD(list_body)) {
                insertLast(&list_body , currentWord.TabWord[i]);
            }
        }
        if (isFullLD(list_body)) {
            expandList(&list_body , 1);
        }
        insertLast(&list_body , '\0');
        if (isEqual(currentWord , stop)) {
            dealocateList(&list_body);
            printf("Proses Ubah Draft Email berhasil di FORCE STOP dan tersimpan.\n");
            return;
        } else if (CheckEmptyEmail(list_body)) {
            printf("Body tidak valid karena kosong.\n");
        } else if (over) {
            printf("Body tidak valid karena melebihi batas 1000 karakter.\n");
        } else {
            (*email).body = toString(currentWord);
            break;
        }
        dealocateList(&list_body);
        printf("Masukkan \"STOP\" untuk force stop Ubah Draft Email.\n");
    }
    printf("Draft Email berhasil diubah.\n");
    return;
}

void UbahDraftBalasEmail(emailType *email , int id_user , ListUser list_user) {
    int id_penerima = (*email).idPenerima;
    char* email_penerima = FindEmailBasedId(list_user , id_penerima);
    char* email_subyek = (*email).subyek;
    char* stop = "STOP";
    boolean check = true;
    printf("Masukkan Email Penerima : %s\n" , email_penerima);
    while (check) {
        printf("Masukkan Penerima CC : ");
        STARTWORDDraft();
        for (int i = 0 ; i < currentWord.Length ; i++) {
            if (currentWord.TabWord[i] == '\n' || currentWord.TabWord[i] == BLANK) {
                check = false;
                break;
            }
        }
        int id_cc = FindIdBasedEmail(list_user , currentWord);
        if (currentWord.Length == 0) {
            (*email).idCC = id_cc;
            break;
        } else {
            if (!check) {
                check = true;
                printf("Input tidak valid, silakan ulangi.\n");
            } else if (isEqual(currentWord , stop)) {
                printf("Proses Ubah Draft Balas Email berhasil di FORCE STOP dan tersimpan.\n");
                return;
            } else if (id_cc == IDX_UNDEF) {
                printf("Pengguna email dengan alamat %s tidak ditemukan.\n" , currentWord.TabWord);
            } else if (id_cc == id_penerima) {
                printf("Penerima CC tidak boleh sama dengan penerima pesan.\n");
            } else if (currentWord.Length > 255) {
                printf("Email tidak valid karena melebihi batas 255 karakter.\n");
            } else {
                (*email).idCC = id_cc;
                break;
            }
        }
        printf("Masukkan \"STOP\" untuk force stop Ubah Draft Balas Email.\n");
    }
    printf("Masukkan Subjek : %s\n" , email_subyek);
    while (check) {
        printf("Masukkan Body : ");
        ListDin list_body;
        CreateListDin(&list_body , 1000);
        STARTWORDDraft();
        for (int i = 0 ; i < currentWord.Length ; i++) {
            if (!isFullLD(list_body)) {
                insertLast(&list_body , currentWord.TabWord[i]);
            }
        }
        if (isFullLD(list_body)) {
            expandList(&list_body , 1);
        }
        insertLast(&list_body , '\0');
        if (isEqual(currentWord , stop)) {
            printf("Proses Ubah Draft Balas Email berhasil di FORCE STOP dan tersimpan.\n");
            dealocateList(&list_body);
            return;
        } else if (CheckEmptyEmail(list_body)) {
            dealocateList(&list_body);
            printf("Body tidak valid karena kosong.\n");
        } else if (over) {
            dealocateList(&list_body);
            printf("Body tidak valid karena melebihi batas 1000 karakter.\n");
        } else {
            (*email).body = toString(currentWord);
            dealocateList(&list_body);
            break;
        }
        printf("Masukkan \"STOP\" untuk force stop Ubah Draft Balas Email.\n");
    }
    printf("Draft Balas Email berhasil diubah.\n");
    return;
}

void KirimDraftEmail(ListEmail *list_email , emailType *email) {
    Datetime t;
    CreateDatetime(&t);
    getDatetime(&t);
    Word time_stamp;
    time_stamp.Length = 20;
    time_stamp.TabWord[0] = '0' + (t.year / 1000) % 10;
    time_stamp.TabWord[1] = '0' + (t.year / 100) % 10;
    time_stamp.TabWord[2] = '0' + (t.year / 10) % 10;
    time_stamp.TabWord[3] = '0' + t.year % 10;
    time_stamp.TabWord[4] = '-';
    time_stamp.TabWord[5] = '0' + (t.month / 10) % 10;
    time_stamp.TabWord[6] = '0' + t.month % 10;
    time_stamp.TabWord[7] = '-';
    time_stamp.TabWord[8] = '0' + (t.day / 10) % 10;
    time_stamp.TabWord[9] = '0' + t.day % 10;
    time_stamp.TabWord[10] = BLANK;
    time_stamp.TabWord[11] = '0' + (t.hour / 10) % 10;
    time_stamp.TabWord[12] = '0' + t.hour % 10;
    time_stamp.TabWord[13] = '.';
    time_stamp.TabWord[14] = '0' + (t.minute / 10) % 10;
    time_stamp.TabWord[15] = '0' + t.minute % 10;
    time_stamp.TabWord[16] = '.';
    time_stamp.TabWord[17] = '0' + (t.second / 10) % 10;
    time_stamp.TabWord[18] = '0' + t.second % 10;
    time_stamp.TabWord[19] = '\0';
    (*email).id = (*list_email).number + 1;
    (*email).timestamp = toString(time_stamp);
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
    (*email).starred = false;
    printf("Draft Email berhasil dikirim!\n");
    return;
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
    if (!isEqualStr(email.subyek, "")) {
        printf("Subjek : %s\n" , email.subyek);
    } else {
        printf("Subjek : <Tidak Ada>\n");
    }
    if (!isEqualStr(email.body, "")) {
        printf("Body : %s\n" , email.body);
    } else {
        printf("Body : <Tidak Ada>\n");
    }
    char* stop = "STOP";
    printf("\nMasukkan \"STOP\" untuk kembali ke menu draft.\n");
    printf(">> ");
    STARTWORDDraft();
    while (!isEqual(currentWord , stop)) {
        printf("Masukan Anda tidak valid.\n");
        printf("Masukkan \"STOP\" untuk kembali ke menu draft.\n");
        printf("\n>> ");
        STARTWORDDraft();
    }
    return;
}

void UndoDraftEmail(emailType *email , Stack *stack_main , Stack *stack_temp) {
    if (!IsEmptyStack(*stack_main)) {
        emailType email_temp;
        PopStack(&*stack_main , &email_temp);
        if (IsEmptyStack(*stack_main)) {
            printf("Belum ada perubahan yang dapat di-undo.\n");
            PushStack(&*stack_main , email_temp);
        } else {
            PushStack(&*stack_temp , email_temp);
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
        PopStack(&*stack_temp , &email_temp);
        PushStack(&*stack_main , email_temp);
        *email = InfoTop(*stack_main);
        printf("Perubahan berhasil di-redo.\n");
    } else {
        printf("Belum ada perubahan yang dapat di-redo.\n");
    }
}

void DraftEmail(int id_user , ListUser list_user , ListEmail *list_email , int reply , int id_reply , int id_old) {
    emailType email;
    Stack stack_main , stack_temp;
    CreateEmptyStack(&stack_main);
    CreateEmptyStack(&stack_temp);
    char* buat_draft = "BUAT_DRAFT";
    char* ubah_draft = "UBAH_DRAFT";
    char* lihat_draft = "LIHAT_DRAFT";
    char* kirim_draft = "KIRIM_DRAFT";
    char* undo = "UNDO";
    char* redo = "REDO";
    char* batal = "BATAL";
    if (id_reply == 0) {
        printf("\n==================================\n");
        printf("SELAMAT DATANG DI MENU DRAFT EMAIL\n");
        email = BuatDraftEmail(id_user , list_user);
    } else {
        printf("\n========================================\n");
        printf("SELAMAT DATANG DI MENU DRAFT BALAS EMAIL\n");
        email = BuatDraftBalasEmail(id_user , list_user , *list_email , reply , id_reply , id_old);
    }
    PushStack(&stack_main , email);
    while (true) {
        if (reply == 0) {
            printf("\n==================================\n");
            printf("SELAMAT DATANG DI MENU DRAFT EMAIL\n");
        } else {
            printf("\n========================================\n");
            printf("SELAMAT DATANG DI MENU DRAFT BALAS EMAIL\n");
        }
        printf("Pilihan Opsi :\n");
        printf("     --- BUAT_DRAFT\n");
        printf("     --- UBAH_DRAFT\n");
        printf("     --- LIHAT_DRAFT\n");
        printf("     --- KIRIM_DRAFT\n");
        printf("     --- UNDO\n");
        printf("     --- REDO\n");
        printf("     --- BATAL\n\n");
        printf(">> ");
        STARTWORDDraft();
        if (isEqual(currentWord , buat_draft)) {
            printf("Maaf, sudah ada draft terbuat! Silahkan finalisasi draft yang sudah dibuat.\n");
        } else if (isEqual(currentWord , ubah_draft)) {
            if (reply == 0) {
                UbahDraftEmail(&email , id_user , list_user);
            } else {
                UbahDraftBalasEmail(&email , id_user , list_user);
            }
            PushStack(&stack_main , email);
            while (!IsEmptyStack(stack_temp)) {
                emailType email_temp;
                PopStack(&stack_temp , &email_temp);
            }
        } else if (isEqual(currentWord , lihat_draft)) {
            LihatDraftEmail(list_user , email);
        } else if (isEqual(currentWord , kirim_draft)) {
            if (isEqualStr(email.body, "")) {
                printf("Draft belum sempurna, mohon disempurnakan terlebih dahulu.\n");
            } else {
                KirimDraftEmail(&*list_email , &email);
                return;
            }
        } else if (isEqual(currentWord , undo)) {
            UndoDraftEmail(&email , &stack_main , &stack_temp);
        } else if (isEqual(currentWord , redo)) {
            RedoDraftEmail(&email , &stack_main , &stack_temp);
        } else if (isEqual(currentWord , batal)) {
            BatalDraftEmail(&email , reply);
            return;
        } else {
            printf("Perintah Tidak Valid. Masukkan \"BATAL\" untuk kembali ke menu utama.\n");
        }
    }
}

void StartDraftEmail() {
    DraftEmail(user.id , listUser , &listEmail , 0 , 0 , 0);
}