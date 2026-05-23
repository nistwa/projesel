#ifndef VERITABANI_H
#define VERITABANI_H

#include <QtSql>
#include <QString>
#include <QList>

// ── Tek bir harcama kaydını temsil eder ──
struct HarcamaKaydi {
    int     id;
    QString kategori;
    double  tutar;
    QString tarih;      // "2026-05-03" formatında
    QString aciklama;
};

// ── Tek bir hedef kaydını temsil eder ──
struct HedefKaydi {
    int     id;
    QString kategori;
    double  limitTutar;
    int     ay;         // 1-12
    int     yil;        // örn: 2026
};

class VeriTabani {
public:
    VeriTabani();
    ~VeriTabani();

    bool baglan();
    bool tablolariOlustur();

    bool harcamaKaydet(HarcamaKaydi h);
    bool hedefKaydet(HedefKaydi h);
    bool harcamaSil(int id);

    QList<HarcamaKaydi> harcamalariGetir(int ay, int yil);
    QList<HedefKaydi>   hedefleriGetir(int ay, int yil);
    QList<HarcamaKaydi> harcamalariAra(QString kategori, int ay, int yil);

private:
    QSqlDatabase db;
};

#endif // VERITABANI_H