#include "butceyoneticisi.h"

// ─────────────────────────────────────────
ButceYoneticisi::ButceYoneticisi() {
    // VeriTabani nesnesi otomatik oluşur
    // constructor'ında baglan() ve tablolariOlustur() çağrılıyor
}

// ─────────────────────────────────────────
bool ButceYoneticisi::harcamaEkle(QString kategori, double tutar,
                                  QString tarih, QString aciklama) {
    HarcamaKaydi h;
    h.kategori = kategori;
    h.tutar    = tutar;
    h.tarih    = tarih;
    h.aciklama = aciklama;
    return db.harcamaKaydet(h);
}

// ─────────────────────────────────────────
bool ButceYoneticisi::hedefEkle(QString kategori, double limitTutar,
                                int ay, int yil) {
    HedefKaydi h;
    h.kategori   = kategori;
    h.limitTutar = limitTutar;
    h.ay         = ay;
    h.yil        = yil;
    return db.hedefKaydet(h);
}

// ─────────────────────────────────────────
bool ButceYoneticisi::harcamaSil(int id) {
    return db.harcamaSil(id);
}

// ─────────────────────────────────────────
QList<HarcamaKaydi> ButceYoneticisi::harcamalariGetir(int ay, int yil) {
    return db.harcamalariGetir(ay, yil);
}

// ─────────────────────────────────────────
QList<HedefKaydi> ButceYoneticisi::hedefleriGetir(int ay, int yil) {
    return db.hedefleriGetir(ay, yil);
}

// ─────────────────────────────────────────
QList<HarcamaKaydi> ButceYoneticisi::harcamalariAra(
    QString kategori, int ay, int yil) {
    return db.harcamalariAra(kategori, ay, yil);
}

// ─────────────────────────────────────────
QMap<QString, double> ButceYoneticisi::kategoriToplam(int ay, int yil) {
    QMap<QString, double> toplam;

    // O aya ait tüm harcamaları getir
    QList<HarcamaKaydi> liste = db.harcamalariGetir(ay, yil);

    // Her harcamayı kategorisine göre topla
    for (const HarcamaKaydi& h : liste) {
        toplam[h.kategori] += h.tutar;
        // += : kategori ilk kez görülüyorsa 0'dan başlar, üstüne ekler
    }

    return toplam;
}

// ─────────────────────────────────────────
QString ButceYoneticisi::asistanYorumu(int ay, int yil) {
    // Harcama toplamları
    QMap<QString, double> toplamlar = kategoriToplam(ay, yil);

    // Hedefler
    QList<HedefKaydi> hedefler = db.hedefleriGetir(ay, yil);

    if (hedefler.isEmpty()) {
        return "Hic hedef belirlememissin bile... "
               "Once hedef gir, sonra konusalim!";
    }

    QString yorum = "=== AYLIK RAPOR ===\n\n";

    double toplamLimit   = 0;
    double toplamHarcama = 0;
    QString enKotuKategori = "";
    double enKotuOran = 0;

    for (const HedefKaydi& h : hedefler) {
        double harcanan = toplamlar.value(h.kategori, 0.0);
        double oran = (h.limitTutar > 0)
                          ? (harcanan / h.limitTutar) * 100.0
                          : 0.0;

        toplamLimit   += h.limitTutar;
        toplamHarcama += harcanan;

        // En çok aşılan kategoriyi bul
        if (oran > enKotuOran) {
            enKotuOran     = oran;
            enKotuKategori = h.kategori;
        }

        // Her kategori için satır
        yorum += h.kategori + ": ";
        yorum += QString::number(harcanan, 'f', 2) + " TL / ";
        yorum += QString::number(h.limitTutar, 'f', 2) + " TL ";
        yorum += "(" + QString::number(oran, 'f', 1) + "%)\n";
    }

    // Genel oran
    double genelOran = (toplamLimit > 0)
                           ? (toplamHarcama / toplamLimit) * 100.0
                           : 0.0;

    yorum += "\n";

    // Espirili genel yorum
    if (genelOran < 50.0) {
        yorum += "GENEL: Butceni bu kadar iyi yonetmek "
                 "ciddi bir yetenek! Sana bir kupa lazim!";
    }
    else if (genelOran < 80.0) {
        yorum += "GENEL: Fena degil, annen seninle "
                 "gurur duyardi. Boyle devam!";
    }
    else if (genelOran < 100.0) {
        yorum += "GENEL: Son virajda biraz zorlandik ama "
                 "sinirdan atladiniz. Neredeyse!";
    }
    else {
        yorum += "GENEL: Ay sonu gelmeden hesap sifirlandi. "
                 "Champion geri donsin lutfen...";
    }

    // En çok aşılan kategoriyi vurgula
    if (!enKotuKategori.isEmpty() && enKotuOran > 100.0) {
        yorum += "\n\nBu ayin MVP'si (en cok asan): "
                 + enKotuKategori
                 + " kategorisi! ("
                 + QString::number(enKotuOran, 'f', 1)
                 + "% kullanildi)";
    }

    return yorum;
}