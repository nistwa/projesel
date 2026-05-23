#ifndef BUTCEYONETICISI_H
#define BUTCEYONETICISI_H

#include "veritabani.h"
#include <QMap>
#include <QString>

class ButceYoneticisi {
public:
    ButceYoneticisi();

    // ── Veri ekleme / silme ──
    bool harcamaEkle(QString kategori, double tutar,
                     QString tarih, QString aciklama);
    bool hedefEkle(QString kategori, double limitTutar,
                   int ay, int yil);
    bool harcamaSil(int id);

    // ── Sorgulama ──
    QList<HarcamaKaydi> harcamalariGetir(int ay, int yil);
    QList<HedefKaydi>   hedefleriGetir(int ay, int yil);
    QList<HarcamaKaydi> harcamalariAra(QString kategori,
                                       int ay, int yil);

    // ── Hesaplama ──
    // Her kategorinin o ay toplam harcamasını döner
    // Örnek: {"Kozmetik": 250.0, "Market": 180.5}
    QMap<QString, double> kategoriToplam(int ay, int yil);

    // ── Asistan ──
    QString asistanYorumu(int ay, int yil);

private:
    VeriTabani db;   // Veritabanı nesnesi burada — dışarıdan erişilemiyor
};

#endif // BUTCEYONETICISI_H