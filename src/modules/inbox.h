/* *** ADT Inbox *** */
#include "../modules.h"

// Fungsi untuk membagi dengan pembulatan ke atas
int ceil_division(int a, int b);

// Fungsi untuk menampilkan garis pada inbox
void lineInbox();

// Fungsi untuk memformat Email ID (e.g., EMAIL001)
void formatEmailID(int emailID, char* output);

// Fungsi untuk memotong string
void truncateString(const char* input, char* output, int maxLength);

// Fungsi untuk menampilkan daftar inbox
void DisplayInbox(ListEmail listEmail);

// Fungsi untuk bacaPesanInbox
void bacaPesanInbox(ListEmail listEmail, int emailID);

// Fungsi untuk membaca pesan, yang menerima parameter berupa email ID setelah proses validasi berhasil dilakukan.
void bacaPesan(int emailID);

// Fungsi menjalankan perintah inbox
void Inbox();
