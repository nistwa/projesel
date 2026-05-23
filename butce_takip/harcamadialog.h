#ifndef HARCAMADIALOG_H
#define HARCAMADIALOG_H

#include <QDialog>
#include "butceyoneticisi.h"

namespace Ui { class HarcamaDialog; }

class HarcamaDialog : public QDialog {
    Q_OBJECT

public:
    explicit HarcamaDialog(ButceYoneticisi* bm, QWidget *parent = nullptr);
    ~HarcamaDialog();

private slots:
    void on_btnKaydet_clicked();
    void on_btnIptal_clicked();
    void on_btnSil_clicked();

private:
    Ui::HarcamaDialog *ui;
    ButceYoneticisi* bm;
    void tabloYenile();
};

#endif