#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->isFileSelected = false;
    this->isDarkTheme = false;
    this->wallpaperStyle = DWPOS_CENTER;

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
            this->wallpaperStyle = DWPOS_CENTER;
            break;
        case 1:
            ui->radioButton_tab2_tile->setChecked(true);
            this->wallpaperStyle = DWPOS_TILE;
            break;
        case 2:
            ui->radioButton_tab2_stretch->setChecked(true);
            this->wallpaperStyle = DWPOS_STRETCH;
            break;
        case 3:
            ui->radioButton_tab2_fit->setChecked(true);
            this->wallpaperStyle = DWPOS_FIT;
            break;
        case 4:
            ui->radioButton_tab2_fill->setChecked(true);
            this->wallpaperStyle = DWPOS_FILL;
            break;
        case 5:
            ui->radioButton_tab2_span->setChecked(true);
            this->wallpaperStyle = DWPOS_SPAN;
            break;
        }
        this->print_log("Get current Wallpaper style: " + QString::number(wallpaper_style));
    } else {
        this->print_log("Error: Reading WallpaperStyle: " + QString::number(wallpaper_style));
        QMessageBox::critical(this, "Error", "Error reading WallpaperStyle: " + QString::number(wallpaper_style), QMessageBox::Ok);
    }

    // Get AppsUseLightTheme
    this->print_log("Get current theme ...");
    int AppsUseLightTheme = WindowsReg::get_DWORD_value(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", "AppsUseLightTheme");
    if (AppsUseLightTheme > -1) {
        this->print_log("Current theme: " + QString::number(AppsUseLightTheme));
        switch(AppsUseLightTheme){
        case 0:
            ui->radioButton_tab2_dark->setChecked(true);
            break;
        case 1:
            ui->radioButton_tab2_light->setChecked(true);
            break;
        }
    } else {
        this->print_log("Error: Reading AppsUseLightTheme: " + QString::number(AppsUseLightTheme));
        QMessageBox::critical(this, "Error", "Error reading AppsUseLightTheme: " + QString::number(AppsUseLightTheme), QMessageBox::Ok);
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
    this->print_log("Setting Wallpaper ...");

    if(!this->isFileSelected){
        QMessageBox::warning(this, "Error", "Images is not selected!", QMessageBox::Ok);
    }else{
        this->print_log("Setting Wallpaper style ...");
        //        // Set Wallpaper Style
        //        const BYTE *lpData = (const BYTE*) wallpaper_style;

        //        int wallpaper_style_status = WindowsReg::set_REG_SZ_value(HKEY_CURRENT_USER, "Control Panel\\Desktop", lpData);
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

void MainWindow::on_radioButton_tab1_light_toggled(bool checked) {
    this->isDarkTheme = checked;
    DWORD darkTheme = this->isDarkTheme ? 1 : 0;

    int result = WindowsReg::set_DWORD_value(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize\\AppsUseLightTheme", (const BYTE*)&darkTheme);

    if (ERROR_SUCCESS == result) {
        this->print_log("Deu boa: " + QString::number(darkTheme));
    } else {
        this->print_log("RUIM: " + QString::number(result));
    }
}


void MainWindow::on_radioButton_tab1_center_clicked() {
    if(ui->radioButton_tab1_center)
        this->wallpaperStyle = DWPOS_CENTER;
}

void MainWindow::on_radioButton_tab1_tile_clicked() {
    if(ui->radioButton_tab1_center)
        this->wallpaperStyle = DWPOS_TILE;
}

void MainWindow::on_radioButton_tab1_stretch_clicked() {
    if(ui->radioButton_tab1_center)
        this->wallpaperStyle = DWPOS_STRETCH;
}

void MainWindow::on_radioButton_tab1_fit_clicked() {
    if(ui->radioButton_tab1_center)
        this->wallpaperStyle = DWPOS_FIT;
}

void MainWindow::on_radioButton_tab1_fill_clicked() {
    if(ui->radioButton_tab1_center)
        this->wallpaperStyle = DWPOS_FILL;
}

void MainWindow::on_radioButton_tab1_span_clicked() {
    if(ui->radioButton_tab1_center)
        this->wallpaperStyle = DWPOS_SPAN;
}

