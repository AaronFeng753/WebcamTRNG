/*
    Copyright (C) 2020  Aaron Feng

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    My Github homepage: https://github.com/AaronFeng753
*/


#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //===
    this->setWindowTitle("WebcamTRNG "+VERSION+" by Aaron Feng");
    //===
    connect(imageCapture, SIGNAL(imageSaved(int, const QString)), this, SLOT(ImageIsReady()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//==========================================================
/*
============= 安全的阻塞延时 =====================
*/
void MainWindow::Delay_sec_sleep(int time)
{
    QThread::sleep(time);
}

void MainWindow::Delay_msec_sleep(int time)
{
    QThread::msleep(time);
}
//==========================================================

void MainWindow::on_pushButton_Generate_clicked()
{
    connect(camera, SIGNAL(statusChanged(QCamera::Status)), this, SLOT(CheckCam()));
    NotifyStatus=true;
    camera->start();
    //拍照保存照片
    QDateTime time = QDateTime::currentDateTime();
    QString Current_Time = time.toString("ss_zzz");
    QString pic_path = Application_Current_Path+"/1.jpg";
    imageCapture->capture(pic_path);
}

void MainWindow::ImageIsReady()
{
    QString pic_path = Application_Current_Path+"/1.jpg";
    QFile file(pic_path);
    QByteArray byteArray;
    if(file.open(QIODevice::ReadOnly))
    {
        byteArray = file.readAll();
    }
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(byteArray);  // 添加数据到加密哈希值
    QByteArray result = hash.result();  // 返回最终的哈希值
    QString strMD5 = result.toHex();
    QString program = Application_Current_Path+"/StringToSeed.exe";
    QProcess getSeed;
    getSeed.start("\""+program+"\" "+strMD5);
    while(!getSeed.waitForStarted(100)) {}
    while(!getSeed.waitForFinished(100)) {}
    quint32 Seed=getSeed.readAllStandardOutput().toULong();
    QRandomGenerator QRandomGenerator_self(Seed);
    ui->lineEdit_ResNum_int->setText(QString::number(QRandomGenerator_self.bounded(ui->spinBox_MinNum_int->value(),ui->spinBox_MaxNum_int->value())));
    QFile::remove(pic_path);
}

void MainWindow::CheckCam()
{
    if(camera->status()==QCamera::UnavailableStatus && NotifyStatus==true)
    {
        QMessageBox *MSG = new QMessageBox();
        MSG->setWindowTitle(tr("Error"));
        MSG->setText("No webcam available.");
        MSG->setIcon(QMessageBox::Warning);
        MSG->setModal(false);
        MSG->show();
        NotifyStatus=false;
    }
}

void MainWindow::on_pushButton_CheckUpdate_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/AaronFeng753/WebcamTRNG/releases"));
}

void MainWindow::on_pushButton_Donate_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/AaronFeng753/WebcamTRNG/blob/master/Donate.md"));
}

void MainWindow::on_pushButton_OfficalSite_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/AaronFeng753/WebcamTRNG"));
}
