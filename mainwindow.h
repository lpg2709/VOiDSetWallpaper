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

// DESKTOP_WALLPAPER_POSITION Copy from shobjidl.h
//  just because it gives error when compiling for debug????
typedef enum DESKTOP_WALLPAPER_POSITION {
    DWPOS_CENTER = 0,
    DWPOS_TILE = 1,
    DWPOS_STRETCH = 2,
    DWPOS_FIT = 3,
    DWPOS_FILL = 4,
    DWPOS_SPAN = 5
} DESKTOP_WALLPAPER_POSITION;

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
    bool isDarkTheme;
    DESKTOP_WALLPAPER_POSITION wallpaperStyle;
    QString final_wallpaper_folder;

private slots:
    void on_pushButton_tab1_open_file_clicked();

    void get_current_wallpaper();

    void on_pushButton_tab1_setwallpaper_clicked();

    void print_log(QString msg);

    void on_radioButton_tab1_light_toggled(bool checked);

    void on_radioButton_tab1_center_clicked();

    void on_radioButton_tab1_tile_clicked();

    void on_radioButton_tab1_stretch_clicked();

    void on_radioButton_tab1_fit_clicked();

    void on_radioButton_tab1_fill_clicked();

    void on_radioButton_tab1_span_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
