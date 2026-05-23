#ifndef HEFEFDIALOG_H
#define HEFEFDIALOG_H

#include <QDialog>
#include "butceyoneticisi.h"

namespace Ui { class HedefDialog; }

class HedefDialog : public QDialog {
    Q_OBJECT

public:
    explicit HedefDialog(ButceYoneticisi* bm, QWidget *parent = nullptr);
    ~HedefDialog();

private slots:
    void on_btnKaydet_clicked();
    void on_btnIptal_clicked();

private:
    Ui::HedefDialog *ui;
    ButceYoneticisi* bm;
    void tabloYenile();
};

#endif