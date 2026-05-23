#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "butceyoneticisi.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnHedef_clicked();
    void on_btnHarcama_clicked();
    void on_btnRapor_clicked();

private:
    Ui::MainWindow *ui;
    ButceYoneticisi bm;
};

#endif // MAINWINDOW_H