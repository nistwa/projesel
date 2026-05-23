#include "hedefdialog.h"
#include "ui_hedefdialog.h"
#include <QMessageBox>

HedefDialog::HedefDialog(ButceYoneticisi* bm, QWidget *parent)
    : QDialog(parent), ui(new Ui::HedefDialog), bm(bm)
{
    ui->setupUi(this);
    setWindowTitle("Hedef Belirle");
    tabloYenile();
}

HedefDialog::~HedefDialog() { delete ui; }

void HedefDialog::on_btnKaydet_clicked() {
    QString kategori = ui->comboKategori->currentText();
    double  limit    = ui->spinLimit->value();
    int     ay       = ui->spinAy->value();
    int     yil      = ui->spinYil->value();

    if (limit <= 0) {
        QMessageBox::warning(this, "Hata", "Limit sifirdan buyuk olmali!");
        return;
    }

    bool sonuc = bm->hedefEkle(kategori, limit, ay, yil);
    if (sonuc) {
        QMessageBox::information(this, "Basarili", "Hedef kaydedildi!");
        tabloYenile();
    } else {
        QMessageBox::critical(this, "Hata", "Kayit basarisiz!");
    }
}

void HedefDialog::on_btnIptal_clicked() {
    close();
}

void HedefDialog::tabloYenile() {
    int ay  = ui->spinAy->value();
    int yil = ui->spinYil->value();

    auto hedefler = bm->hedefleriGetir(ay, yil);

    ui->tableHedefler->setRowCount(0);
    ui->tableHedefler->setColumnCount(4);
    ui->tableHedefler->setHorizontalHeaderLabels(
        {"ID", "Kategori", "Limit (TL)", "Ay/Yil"});

    for (const HedefKaydi& h : hedefler) {
        int row = ui->tableHedefler->rowCount();
        ui->tableHedefler->insertRow(row);
        ui->tableHedefler->setItem(row, 0,
                                   new QTableWidgetItem(QString::number(h.id)));
        ui->tableHedefler->setItem(row, 1,
                                   new QTableWidgetItem(h.kategori));
        ui->tableHedefler->setItem(row, 2,
                                   new QTableWidgetItem(QString::number(h.limitTutar)));
        ui->tableHedefler->setItem(row, 3,
                                   new QTableWidgetItem(
                                       QString::number(h.ay) + "/" + QString::number(h.yil)));
    }
}