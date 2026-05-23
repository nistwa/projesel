#include "harcamadialog.h"
#include "ui_harcamadialog.h"
#include <QMessageBox>

HarcamaDialog::HarcamaDialog(ButceYoneticisi* bm, QWidget *parent)
    : QDialog(parent), ui(new Ui::HarcamaDialog), bm(bm)
{
    ui->setupUi(this);
    setWindowTitle("Harcama Gir");
    ui->dateTarih->setDate(QDate::currentDate());
    tabloYenile();
}

HarcamaDialog::~HarcamaDialog() { delete ui; }

void HarcamaDialog::on_btnKaydet_clicked() {
    QString kategori = ui->comboKategori->currentText();
    double  tutar    = ui->spinTutar->value();
    QString tarih    = ui->dateTarih->date().toString("yyyy-MM-dd");
    QString aciklama = ui->txtAciklama->text();

    if (tutar <= 0) {
        QMessageBox::warning(this, "Hata", "Tutar sifirdan buyuk olmali!");
        return;
    }

    bool sonuc = bm->harcamaEkle(kategori, tutar, tarih, aciklama);
    if (sonuc) {
        QMessageBox::information(this, "Basarili", "Harcama kaydedildi!");
        ui->spinTutar->setValue(0);
        ui->txtAciklama->clear();
        tabloYenile();
    } else {
        QMessageBox::critical(this, "Hata", "Kayit basarisiz!");
    }
}

void HarcamaDialog::on_btnIptal_clicked() { close(); }

void HarcamaDialog::on_btnSil_clicked() {
    int row = ui->tableHarcamalar->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Uyari", "Lutfen bir kayit secin!");
        return;
    }

    int id = ui->tableHarcamalar->item(row, 0)->text().toInt();

    auto cevap = QMessageBox::question(this, "Emin misin?",
                                       "Bu harcamayi silmek istiyor musun?");

    if (cevap == QMessageBox::Yes) {
        bm->harcamaSil(id);
        tabloYenile();
    }
}

void HarcamaDialog::tabloYenile() {
    QDate bugun = QDate::currentDate();
    auto liste = bm->harcamalariGetir(bugun.month(), bugun.year());

    ui->tableHarcamalar->setRowCount(0);
    ui->tableHarcamalar->setColumnCount(5);
    ui->tableHarcamalar->setHorizontalHeaderLabels(
        {"ID", "Kategori", "Tutar", "Tarih", "Aciklama"});

    for (const HarcamaKaydi& h : liste) {
        int row = ui->tableHarcamalar->rowCount();
        ui->tableHarcamalar->insertRow(row);
        ui->tableHarcamalar->setItem(row, 0,
                                     new QTableWidgetItem(QString::number(h.id)));
        ui->tableHarcamalar->setItem(row, 1,
                                     new QTableWidgetItem(h.kategori));
        ui->tableHarcamalar->setItem(row, 2,
                                     new QTableWidgetItem(QString::number(h.tutar)));
        ui->tableHarcamalar->setItem(row, 3,
                                     new QTableWidgetItem(h.tarih));
        ui->tableHarcamalar->setItem(row, 4,
                                     new QTableWidgetItem(h.aciklama));
    }
}