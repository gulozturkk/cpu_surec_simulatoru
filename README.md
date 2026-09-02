# İşletim Sistemi Süreç ve Zamanlama Simülatörü (OS Simulator)

Atatürk Üniversitesi Mühendislik Fakültesi Yazılım Mühendisliği Bölümü İşletim Sistemleri dersi kapsamında C programlama dili ile geliştirilmiş süreç yönetimi ve zamanlama simülasyonu projesidir.

## Projenin Amacı ve Kapsamı
Bu proje, işletim sistemlerinin çekirdek seviyesindeki temel mekanizmalarını simüle ederek yazılımsal düzeyde anlamayı amaçlar:
- **Süreç Yönetimi (Process Management):** İşletim sistemindeki süreçlerin yaşam döngüsü ve durum geçişleri.
- **CPU Zamanlama Algoritmaları:** İşlemci paylaşımı ve zamanlama stratejilerinin C diliyle modellenmesi.
- **Modüler Mimari:** `main.c` tabanlı, sistem mimarisi ve komut döngülerini mantıksal olarak yürüten yapı[cite: 11].

## Kullanılan Teknolojiler
- **Dil:** C Programlama Dili
- **Geliştirme Ortamı:** Xcode / VS Code / GCC Compiler
- **Kapsam:** İşletim Sistemleri Teorisi ve Uygulaması

## Kurulum ve Çalıştırma
Projeyi klonladıktan sonra terminal üzerinden derleyip çalıştırabilirsiniz:

```bash
git clone [https://github.com/gulozturkk/OS-Process-Scheduler-Simulator.git](https://github.com/gulozturkk/OS-Process-Scheduler-Simulator.git)
cd OS-Process-Scheduler-Simulator/250710093_GU\ RK/is\ letim_proje1/is\ letim_proje1
gcc main.c -o os_simulator
./os_simulator
