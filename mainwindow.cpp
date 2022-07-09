#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QPixmap>
#include <QString>
#include <windows.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::get_current_wallpaper(){
    ui->lineEdit_tab2_file_path->setText("NULL");
}

void MainWindow::on_pushButton_set_clicked(){
    /*
    QString filepath = "C:\\Documents and Settings\\Owner\\My Documents\\Wallpapers\\wallpaper.png";
    char path[150];
    strcpy(path, currentFilePath.toStdString().c_str());
    char *pathp;
    pathp = path;

    cout << path;

    int result;
    result = SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, pathp, SPIF_UPDATEINIFILE);

    if (result)
    {
        cout << "Wallpaper set";
    }
    else
    {
        cout << "Wallpaper not set";
        cout << "SPI returned" << result;
    }
    */
}

void MainWindow::on_pushButton_tab1_open_file_clicked(){
    QString file_name = QFileDialog::getOpenFileName(this, "Open the wallpaper image", QDir::homePath());
    QPixmap pix(file_name);
    ui->lineEdit_tab1_file_path->setText(file_name);
    ui->label_tab1_image_preview->setPixmap(pix.scaled(650, 400, Qt::KeepAspectRatio));
}

