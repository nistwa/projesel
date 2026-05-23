#ifndef RAPORDIALOG_H
#define RAPORDIALOG_H

#include <QDialog>
#include "butceyoneticisi.h"

namespace Ui { class RaporDialog; }

class RaporDialog : public QDialog {
    Q_OBJECT

public:
    explicit RaporDialog(ButceYoneticisi* bm, QWidget *parent = nullptr);
    ~RaporDialog();

private slots:
    void on_btnRapor_clicked();
    void on_btnKapat_clicked();

private:
    Ui::RaporDialog *ui;
    ButceYoneticisi* bm;
};

#endif