#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hedefdialog.h"
#include "harcamadialog.h"
#include "rapordialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Butce Takip");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_btnHedef_clicked() {
    HedefDialog dialog(&bm, this);
    dialog.exec();
}

void MainWindow::on_btnHarcama_clicked() {
    HarcamaDialog dialog(&bm, this);
    dialog.exec();
}

void MainWindow::on_btnRapor_clicked() {
    RaporDialog dialog(&bm, this);
    dialog.exec();
}