#pragma once
#pragma once
#include <windows.h> // Wajib untuk tipe data Windows

// Standar Export agar bisa dibaca C#
#define ATM_API extern "C" __declspec(dllexport)

// Definisi tipe data untuk fungsi Callback (Logback ke UI)
// __stdcall wajib agar kompatibel dengan Delegate C#
typedef void(__stdcall* LogCallbackType)(const char* message);