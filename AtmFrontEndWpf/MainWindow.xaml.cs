using System;
using System.Windows; // Ini Namespace utama WPF
using System.Runtime.InteropServices; // Untuk DllImport

namespace AtmFrontEndWpf
{
    public partial class MainWindow : Window
    {
        // Simpan variabel delegate agar tidak dihapus Garbage Collector
        private NativeBridge.LogCallbackDelegate _logger;

        public MainWindow()
        {
            InitializeComponent();
            SetupMiddleware();
        }

        private void SetupMiddleware()
        {
            // Hubungkan fungsi penerima log
            _logger = new NativeBridge.LogCallbackDelegate(ReceiveLog);

            try
            {
                // Daftarkan ke C++
                NativeBridge.SetupCallback(_logger);
                AddLog("UI: WPF Ready. Terhubung ke DLL.");
            }
            catch (DllNotFoundException)
            {
                MessageBox.Show("File AtmCore.dll tidak ditemukan! Pastikan sudah dicopy ke folder Debug/bin.");
            }
        }

        // --- FUNGSI INI DIPANGGIL OLEH C++ ---
        private void ReceiveLog(string message)
        {
            // PENTING: Karena C++ jalan di thread berbeda, kita pakai Dispatcher untuk update UI WPF
            this.Dispatcher.Invoke(() =>
            {
                AddLog(message);
            });
        }

        private void AddLog(string msg)
        {
            string time = DateTime.Now.ToString("HH:mm:ss");
            // Menambah item ke ListBox (Paling atas)
            lstLog.Items.Insert(0, $"[{time}] {msg}");
        }

        // Event saat tombol Start diklik
        private void btnInit_Click(object sender, RoutedEventArgs e)
        {
            AddLog("UI: Mengirim perintah Initialize...");
            NativeBridge.InitializeSystem();
        }

        // Event saat tombol Test diklik
        private void btnTest_Click(object sender, RoutedEventArgs e)
        {
            // Tes Cek Status
            NativeBridge.CheckDeviceStatus("CDM30");
            NativeBridge.CheckDeviceStatus("PIN30");

            // Tes Transaksi
            NativeBridge.DoTransactionTest();
        }
    }
}