#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdlib.h>

#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QPixmap>
#include <QString>
#include <QVector>
#include <windows.h>
#include <QMessageBox>
#include <QDateTime>
#include <qDebug>

#include "windowsreg.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool isFileSelected;

    enum WALLPAPER_STYLE {
        CENTER, TILE, STRETCH, FIT, FILL, SPAN
    };

private slots:
    void on_pushButton_tab1_open_file_clicked();

    void get_current_wallpaper();

    void on_pushButton_tab1_setwallpaper_clicked();

    void print_log(QString msg);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
