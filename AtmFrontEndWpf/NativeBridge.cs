using System;
using System.Runtime.InteropServices;

namespace AtmFrontEndWpf
{
    public class NativeBridge
    {
        // Nama DLL C++ Anda
        const string DllName = "AtmCore.dll";

        // Definisi Delegate (Wajib sama dengan C++)
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void LogCallbackDelegate(string message);

        // Import Fungsi C++
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetupCallback(LogCallbackDelegate callback);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int InitializeSystem();

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int CheckDeviceStatus(string deviceName);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void DoTransactionTest();
    }
}