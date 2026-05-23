#include "rapordialog.h"
#include "ui_rapordialog.h"

RaporDialog::RaporDialog(ButceYoneticisi* bm, QWidget *parent)
    : QDialog(parent), ui(new Ui::RaporDialog), bm(bm)
{
    ui->setupUi(this);
    setWindowTitle("Ay Sonu Raporu");
    ui->spinAy->setValue(QDate::currentDate().month());
    ui->spinYil->setValue(QDate::currentDate().year());
}

RaporDialog::~RaporDialog() { delete ui; }

void RaporDialog::on_btnRapor_clicked() {
    int ay  = ui->spinAy->value();
    int yil = ui->spinYil->value();
    QString yorum = bm->asistanYorumu(ay, yil);
    ui->lblYorum->setText(yorum);
}

void RaporDialog::on_btnKapat_clicked() { close(); }