#include "veritabani.h"
#include <QDebug>

// ─────────────────────────────────────────
// Constructor: nesne oluşturunca otomatik çalışır
VeriTabani::VeriTabani() {
    baglan();
    tablolariOlustur();
}

// Destructor: uygulama kapanınca bağlantıyı kapat
VeriTabani::~VeriTabani() {
    if (db.isOpen())
        db.close();
}

// ─────────────────────────────────────────
bool VeriTabani::baglan() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("butce_takip.db");

    if (!db.open()) {
        qDebug() << "HATA - Veritabani acilamadi:" << db.lastError().text();
        return false;
    }
    qDebug() << "Veritabani baglantisi basarili!";
    return true;
}

// ─────────────────────────────────────────
bool VeriTabani::tablolariOlustur() {
    QSqlQuery sorgu;

    bool h = sorgu.exec(
        "CREATE TABLE IF NOT EXISTS harcamalar ("
        "id        INTEGER PRIMARY KEY AUTOINCREMENT,"
        "kategori  TEXT    NOT NULL,"
        "tutar     REAL    NOT NULL,"
        "tarih     TEXT    NOT NULL,"
        "aciklama  TEXT"
        ")"
        );

    bool g = sorgu.exec(
        "CREATE TABLE IF NOT EXISTS hedefler ("
        "id           INTEGER PRIMARY KEY AUTOINCREMENT,"
        "kategori     TEXT    NOT NULL,"
        "limit_tutar  REAL    NOT NULL,"
        "ay           INTEGER NOT NULL,"
        "yil          INTEGER NOT NULL,"
        "UNIQUE(kategori, ay, yil)"
        ")"
        );

    if (h && g)
        qDebug() << "Tablolar hazir!";
    else
        qDebug() << "Tablo hatasi:" << sorgu.lastError().text();

    return h && g;
}

// ─────────────────────────────────────────
bool VeriTabani::harcamaKaydet(HarcamaKaydi h) {
    QSqlQuery sorgu;
    sorgu.prepare(
        "INSERT INTO harcamalar (kategori, tutar, tarih, aciklama) "
        "VALUES (:kategori, :tutar, :tarih, :aciklama)"
        );
    sorgu.bindValue(":kategori", h.kategori);
    sorgu.bindValue(":tutar",    h.tutar);
    sorgu.bindValue(":tarih",    h.tarih);
    sorgu.bindValue(":aciklama", h.aciklama);

    bool sonuc = sorgu.exec();
    if (!sonuc)
        qDebug() << "Harcama kayit hatasi:" << sorgu.lastError().text();
    return sonuc;
}

// ─────────────────────────────────────────
bool VeriTabani::hedefKaydet(HedefKaydi h) {
    QSqlQuery sorgu;
    sorgu.prepare(
        "INSERT OR REPLACE INTO hedefler "
        "(kategori, limit_tutar, ay, yil) "
        "VALUES (:kategori, :limit, :ay, :yil)"
        );
    sorgu.bindValue(":kategori", h.kategori);
    sorgu.bindValue(":limit",    h.limitTutar);
    sorgu.bindValue(":ay",       h.ay);
    sorgu.bindValue(":yil",      h.yil);

    bool sonuc = sorgu.exec();
    if (!sonuc)
        qDebug() << "Hedef kayit hatasi:" << sorgu.lastError().text();
    return sonuc;
}

// ─────────────────────────────────────────
bool VeriTabani::harcamaSil(int id) {
    QSqlQuery sorgu;
    sorgu.prepare("DELETE FROM harcamalar WHERE id = :id");
    sorgu.bindValue(":id", id);
    return sorgu.exec();
}

// ─────────────────────────────────────────
QList<HarcamaKaydi> VeriTabani::harcamalariGetir(int ay, int yil) {
    QList<HarcamaKaydi> liste;
    QSqlQuery sorgu;

    sorgu.prepare(
        "SELECT id, kategori, tutar, tarih, aciklama "
        "FROM harcamalar "
        "WHERE strftime('%m', tarih) = :ay "
        "AND   strftime('%Y', tarih) = :yil "
        "ORDER BY tarih DESC"
        );
    // Ay 2 haneli olmalı: 5 → "05"
    sorgu.bindValue(":ay",  QString("%1").arg(ay, 2, 10, QChar('0')));
    sorgu.bindValue(":yil", QString::number(yil));
    sorgu.exec();

    while (sorgu.next()) {
        HarcamaKaydi k;
        k.id       = sorgu.value("id").toInt();
        k.kategori = sorgu.value("kategori").toString();
        k.tutar    = sorgu.value("tutar").toDouble();
        k.tarih    = sorgu.value("tarih").toString();
        k.aciklama = sorgu.value("aciklama").toString();
        liste.append(k);
    }
    return liste;
}

// ─────────────────────────────────────────
QList<HedefKaydi> VeriTabani::hedefleriGetir(int ay, int yil) {
    QList<HedefKaydi> liste;
    QSqlQuery sorgu;

    sorgu.prepare(
        "SELECT id, kategori, limit_tutar, ay, yil "
        "FROM hedefler WHERE ay = :ay AND yil = :yil"
        );
    sorgu.bindValue(":ay",  ay);
    sorgu.bindValue(":yil", yil);
    sorgu.exec();

    while (sorgu.next()) {
        HedefKaydi h;
        h.id         = sorgu.value("id").toInt();
        h.kategori   = sorgu.value("kategori").toString();
        h.limitTutar = sorgu.value("limit_tutar").toDouble();
        h.ay         = sorgu.value("ay").toInt();
        h.yil        = sorgu.value("yil").toInt();
        liste.append(h);
    }
    return liste;
}

// ─────────────────────────────────────────
QList<HarcamaKaydi> VeriTabani::harcamalariAra(
    QString kategori, int ay, int yil)
{
    QList<HarcamaKaydi> liste;
    QSqlQuery sorgu;

    sorgu.prepare(
        "SELECT id, kategori, tutar, tarih, aciklama "
        "FROM harcamalar "
        "WHERE kategori = :kategori "
        "AND strftime('%m', tarih) = :ay "
        "AND strftime('%Y', tarih) = :yil"
        );
    sorgu.bindValue(":kategori", kategori);
    sorgu.bindValue(":ay",  QString("%1").arg(ay, 2, 10, QChar('0')));
    sorgu.bindValue(":yil", QString::number(yil));
    sorgu.exec();

    while (sorgu.next()) {
        HarcamaKaydi k;
        k.id       = sorgu.value("id").toInt();
        k.kategori = sorgu.value("kategori").toString();
        k.tutar    = sorgu.value("tutar").toDouble();
        k.tarih    = sorgu.value("tarih").toString();
        k.aciklama = sorgu.value("aciklama").toString();
        liste.append(k);
    }
    return liste;
}