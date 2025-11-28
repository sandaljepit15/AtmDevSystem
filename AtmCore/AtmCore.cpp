#include "pch.h"
#include "AtmCore.h"
#include <string>
#include <stdio.h> // Untuk sprintf

// Variabel Global untuk menyimpan alamat fungsi di C#
LogCallbackType g_LogToUI = nullptr;

// Fungsi Internal untuk mempermudah kirim log
void SendLog(const char* fmt, ...) {
    if (g_LogToUI == nullptr) return; // Jangan kirim kalau UI belum siap

    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    // Panggil fungsi di C#
    g_LogToUI(buffer);
}

// --- FUNGSI-FUNGSI YANG AKAN DIPANGGIL C# ---

// 1. Registrasi: C# menyerahkan fungsi log-nya ke sini
ATM_API void SetupCallback(LogCallbackType callback) {
    g_LogToUI = callback;
    SendLog("[Middleware] Callback terdaftar. Jalur komunikasi siap.");
}

// 2. Simulasi Inisialisasi Sistem
ATM_API int InitializeSystem() {
    SendLog("[Middleware] Memulai inisialisasi sistem...");

    // Di sini nanti Anda masukkan WFSStartUp
    // Simulasi delay proses
    Sleep(500);

    SendLog("[Middleware] Sistem Inti BERHASIL dimuat.");
    return 1; // 1 = Sukses
}

// 3. Simulasi Cek Koneksi ke XFS (WFSOpen)
ATM_API int CheckDeviceStatus(const char* deviceName) {
    SendLog("[Middleware] Memeriksa status perangkat: %s ...", deviceName);

    // Simulasi logika WFSOpen
    // Anggap saja di kantor Anda "CDM30" itu ada/simulasi sukses
    if (strcmp(deviceName, "CDM30") == 0) {
        Sleep(1000); // Pura-pura mikir
        SendLog("[Middleware] SUKSES: Perangkat %s Terhubung (Handle: 0x1234).", deviceName);
        return 1;
    }
    else if (strcmp(deviceName, "PIN30") == 0) {
        Sleep(500);
        SendLog("[Middleware] SUKSES: Perangkat %s Terhubung (Secure Mode).", deviceName);
        return 1;
    }
    else {
        SendLog("[Middleware] ERROR: Perangkat %s tidak dikenal/offline.", deviceName);
        return 0;
    }
}

// 4. Simulasi Operasi (Misal: Dispense)
ATM_API void DoTransactionTest() {
    SendLog("[Middleware] Memulai simulasi transaksi...");
    for (int i = 1; i <= 3; i++) {
        Sleep(800);
        SendLog("[Middleware] Proses tahap %d/3...", i);
    }
    SendLog("[Middleware] Transaksi Selesai.");
}