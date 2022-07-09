#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->isFileSelected = false;
    this->print_log("Starting program ...");
    this->print_log("Get current Wallpaper configuration ...");
    this->get_current_wallpaper();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::print_log(QString msg){
    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("dd.MM.yyyy hh:mm:ss:zzz");

    QString output = "[ " + formattedTime + " ] " + msg + "\n";

    ui->plainTextEdit_log->moveCursor(QTextCursor::End);
    ui->plainTextEdit_log->textCursor().insertText(output);
    ui->plainTextEdit_log->moveCursor(QTextCursor::End);
}

void MainWindow::get_current_wallpaper(){
    ui->lineEdit_tab2_file_path->setText("NULL");

    // Get Wallpaper path
    WCHAR bgPath[MAX_PATH];

    this->print_log("Get Wallpaper path ...");
    int result = SystemParametersInfo(SPI_GETDESKWALLPAPER, MAX_PATH, &bgPath, 0);

    if (!result){
        this->print_log("Error: Fail to get the wallpaper: " + QString::number(result));
        QMessageBox::critical(this, "Error", "Fail to get the wallpaper: " + QString::number(result), QMessageBox::Ok);
    }else{
        QString file_name = QString::fromWCharArray(bgPath).replace("\\", "/");
        this->print_log("Wallpaper path find: " + file_name);
        QPixmap pix(file_name);
        ui->lineEdit_tab2_file_path->setText(file_name);
        ui->label_tab2_image_preview->setPixmap(pix.scaled(650, 400, Qt::KeepAspectRatio));
    }

    // Get Wallpaper Style
    HKEY hkey = HKEY_CURRENT_USER;
    LPCSTR lpSubKey = "Control Panel\\Desktop";
    LPCSTR lpValue = "WallpaperStyle";

    this->print_log("Get current Wallpaper style ...");
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
        this->print_log("Get current Wallpaper style: " + QString::number(wallpaper_style));
    } else {
        this->print_log("Error: Reading WallpaperStyle: " + QString::number(wallpaper_style));
        QMessageBox::critical(this, "Error", "Error reading WallpaperStyle: " + QString::number(wallpaper_style), QMessageBox::Ok);
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

    this->print_log("Setting Wallpaper ...");

    if(!this->isFileSelected){
        QMessageBox::warning(this, "Error", "Images is not selected!", QMessageBox::Ok);
    }else{
        wallpaper_style_option.append(ui->radioButton_tab1_center->isChecked());
        wallpaper_style_option.append(ui->radioButton_tab1_tile->isChecked());
        wallpaper_style_option.append(ui->radioButton_tab1_stretch->isChecked());
        wallpaper_style_option.append(ui->radioButton_tab1_fit->isChecked());
        wallpaper_style_option.append(ui->radioButton_tab1_fill->isChecked());
        wallpaper_style_option.append(ui->radioButton_tab1_span->isChecked());

        this->print_log("Readding Wallpaper style ...");
        for(int i = 0; i < wallpaper_style_option.length(); i++){
            if(wallpaper_style_option[i])
                wallpaper_style = i;
        }
        this->print_log("Setting Wallpaper style ...");
//        // Set Wallpaper Style
//        HKEY hKey = HKEY_CURRENT_USER;
//        LPCSTR lpValueName = "Control Panel\\Desktop";
//        const BYTE *lpData = (const BYTE*) wallpaper_style;

//        int wallpaper_style_status = WindowsReg::set_REG_SZ_value(hKey, lpValueName, lpData);
//        if (wallpaper_style_status > 0){
//            QMessageBox::critical(this, "Error", "Fail to set the wallpaper style: " + QString::number(wallpaper_style_status), QMessageBox::Ok);
//        }

        QString filepath =  ui->lineEdit_tab1_file_path->text().replace("/", "\\");
        QStringList parts = filepath.split(QDir::separator());
        QString filename = parts.at(parts.size()-1);
        QString final_filepath = QDir::homePath() + QDir::toNativeSeparators("/AppData/Local/Microsoft/Windows/Themes/RoamedThemeFiles/DesktopBackground/" + filename);
        char path[150];
        strncpy(path, final_filepath.toStdString().c_str(), sizeof(path));

        this->print_log("Copy wallpaper file to default path ...");
        QFile::copy(QDir::toNativeSeparators(filepath), final_filepath);
        this->print_log("File copy: " + final_filepath);

        // Set wallpaper and reload user configs
        int result = SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (PVOID) path, SPIF_UPDATEINIFILE);

        if (!result){
            this->print_log("Error: Fail to set the wallpaper: " + QString::number(result));
            QMessageBox::critical(this, "Error", "Fail to set the wallpaper: " + QString::number(result), QMessageBox::Ok);
        }else{
            QMessageBox::information(this, "Saved", "Wallpaper set!: "+filepath, QMessageBox::Ok);
            this->print_log("Configs applyed!");
            this->get_current_wallpaper();
        }

    }
}

