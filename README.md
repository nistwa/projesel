# 💰 BütçeApp — Kişisel Bütçe Takip Uygulaması

**T.C. Marmara Üniversitesi | Teknoloji Fakültesi | Elektrik-Elektronik Mühendisliği**  
**BLM1030 Bilgisayar Programlama | 2025-2026 Bahar Dönemi Proje Ödevi**

---

## Proje Hakkında

Gelir ve giderlerinizi kategori bazlı takip edebileceğiniz, haftalık/aylık istatistikler sunan masaüstü uygulaması. C++ ve Qt ile geliştirilmiş, veriler SQLite veritabanında saklanmaktadır.

---

## Ekip

| İsim | Rol | Sorumluluk |
|------|-----|------------|
| Azra Topal | Backend | Transaction, Income, Expense, TransactionManager, DatabaseManager .cpp dosyaları |
| Şevval Türkan Kafes | Frontend | Qt Designer formları, arayüz bileşenleri |
| Nisanur Özpehlivan | OOP Tasarım + Veritabanı + Rapor | Header dosyaları, SQLite şeması, proje raporu, UML diyagramı |

---

## Kullanılan Teknolojiler

- **C++17**
- **Qt 6** (GUI)
- **SQLite** (Veritabanı)
- **Qt Designer** (Form tasarımı)

---

## Proje Yapısı

```
butce-app/
│
├── headers/                  ← OOP sınıf iskeletleri (.h dosyaları)
│   ├── Transaction.h         ← Soyut temel sınıf
│   ├── Income.h              ← Gelir sınıfı
│   ├── Expense.h             ← Gider sınıfı
│   ├── TransactionManager.h  ← Liste ve iş mantığı yönetimi
│   └── DatabaseManager.h     ← SQLite okuma/yazma
│
├── src/                      ← Fonksiyon implementasyonları (.cpp dosyaları)
│   ├── Transaction.cpp
│   ├── Income.cpp
│   ├── Expense.cpp
│   ├── TransactionManager.cpp
│   └── DatabaseManager.cpp
│
├── ui/                       ← Qt Designer arayüz dosyaları
│   ├── mainwindow.h
│   ├── mainwindow.cpp
│   └── mainwindow.ui
│
├── docs/                     ← Rapor ve diyagramlar
│   ├── rapor.pdf
│   └── uml.png
│
├── main.cpp                  ← Programın giriş noktası
├── ButceApp.pro              ← Qt proje dosyası
└── README.md
```

---

## OOP Kavramları

| Kavram | Nerede Kullanıldı |
|--------|-------------------|
| Soyutlama | `Transaction` soyut sınıfı — doğrudan nesne oluşturulamaz |
| Sarmalama | Tüm değişkenler `private`/`protected`, getter/setter ile erişim |
| Kalıtım | `Income` ve `Expense`, `Transaction`'dan türetilmiş |
| Çok biçimlilik | `getType()` ve `getSummary()` sanal fonksiyonları |

---

## Özellikler

- Gelir/gider kaydı oluşturma
- Kategori bazlı listeleme
- Kayıt arama ve silme
- Haftalık & aylık özet istatistikler
- SQLite ile kalıcı veri saklama

---

## Nasıl Çalıştırılır?

1. Qt Creator'ı aç
2. `ButceApp.pro` dosyasını aç
3. Build → Run

---

## Son Teslim

- **Yükleme:** 28 Mayıs 2026 - 23:59
- **Sunum:** 29 Mayıs 2026 - Laboratuvar
