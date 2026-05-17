-- Eğer önceden tablo varsa temizle (Hata almamak için)
DROP TABLE IF EXISTS transactions;

-- İşlemler tablosunu oluştur
CREATE TABLE transactions (
    id          INTEGER PRIMARY KEY AUTOINCREMENT, -- Her işlemin benzersiz numarası
    type        TEXT NOT NULL,                     -- "Gelir" veya "Gider"
    category    TEXT NOT NULL,                     -- "Mutfak", "Kira", "Maaş" vb.
    amount      REAL NOT NULL,                     -- Para miktarı (Ondalıklı olabilir)
    date        TEXT NOT NULL,                     -- "YYYY-MM-DD" formatında tarih
    description TEXT                               -- İsteğe bağlı açıklama
);
