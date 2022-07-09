#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->isFileSelected = false;
    this->get_current_wallpaper();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::get_current_wallpaper(){
    ui->lineEdit_tab2_file_path->setText("NULL");

    // Get Wallpaper path
    WCHAR bgPath[MAX_PATH];

    int result = SystemParametersInfo(SPI_GETDESKWALLPAPER, MAX_PATH, &bgPath, 0);

    if (!result){
        QMessageBox::critical(this, "Error", "Fail to get the wallpaper: " + QString::number(result), QMessageBox::Ok);
    }else{
        QString file_name = QString::fromWCharArray(bgPath).replace("\\", "/");
        QPixmap pix(file_name);
        ui->lineEdit_tab2_file_path->setText(file_name);
        ui->label_tab2_image_preview->setPixmap(pix.scaled(650, 400, Qt::KeepAspectRatio));
    }

    // Get Wallpaper Style
    HKEY hkey = HKEY_CURRENT_USER;
    LPCSTR lpSubKey = "Control Panel\\Desktop";
    LPCSTR lpValue = "WallpaperStyle";

    int wallpaper_style = WindowsReg::get_REG_SZ_value(hkey, lpSubKey, lpValue);

    if (wallpaper_style > -1) {
        switch(wallpaper_style){
            case 0:
                ui->radioButton_tab2_center->setChecked(true);
                break;
            case 1:
                ui->radioButton_tab2_tile->setChecked(true);
                break;
            case 2:
                ui->radioButton_tab2_stretch->setChecked(true);
                break;
            case 3:
                ui->radioButton_tab2_fit->setChecked(true);
                break;
            case 4:
                ui->radioButton_tab2_fill->setChecked(true);
                break;
            case 5:
                ui->radioButton_tab2_span->setChecked(true);
                break;
        }
    } else {
        QMessageBox::critical(this, "Error", "Error reading WallpaperStyle: " + QString::number(result), QMessageBox::Ok);
    }
}

void MainWindow::on_pushButton_tab1_open_file_clicked(){
    QString file_name = QFileDialog::getOpenFileName(this, "Open the wallpaper image", QDir::homePath());
    QPixmap pix(file_name);
    ui->lineEdit_tab1_file_path->setText(file_name);
    ui->label_tab1_image_preview->setPixmap(pix.scaled(650, 400, Qt::KeepAspectRatio));
    this->isFileSelected = true;
}

void MainWindow::on_pushButton_tab1_setwallpaper_clicked()
{
    int wallpaper_style = 0;
    QVector<bool> wallpaper_style_option;

    if(!this->isFileSelected){
        QMessageBox::warning(this, "Error", "Images is not selected!", QMessageBox::Ok);
    }else{
        wallpaper_style_option.append(ui->radioButton_tab1_center->isChecked());
        wallpaper_style_option.append(ui->radioButton_tab1_tile->isChecked());
        wallpaper_style_option.append(ui->radioButton_tab1_stretch->isChecked());
        wallpaper_style_option.append(ui->radioButton_tab1_fit->isChecked());
        wallpaper_style_option.append(ui->radioButton_tab1_fill->isChecked());
        wallpaper_style_option.append(ui->radioButton_tab1_span->isChecked());

        for(int i = 0; i < wallpaper_style_option.length(); i++){
            if(wallpaper_style_option[i])
                wallpaper_style = i;
        }

        QString filepath =  ui->lineEdit_tab1_file_path->text().replace("/", "\\");
        char path[150];
        strncpy(path, filepath.toStdString().c_str(), sizeof(path));

        int result = SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (PVOID) path, SPIF_UPDATEINIFILE);

        if (!result){
            QMessageBox::critical(this, "Error", "Fail to set the wallpaper: " + QString::number(result), QMessageBox::Ok);
        }else{
            QMessageBox::information(this, "Saved", "Wallpaper set!: "+filepath, QMessageBox::Ok);
            this->get_current_wallpaper();
        }

    }
}

