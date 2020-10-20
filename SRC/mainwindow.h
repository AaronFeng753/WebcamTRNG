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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qcoreapplication.h>

#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>

#include <QThread>
#include <QRandomGenerator>
#include <QFile>
#include <QCryptographicHash>
#include <QDateTime>
#include <QProcess>
#include <QMessageBox>

#include <QDesktopServices>
#include <QUrl>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString VERSION = "v0.01";//软件版本号

    QString Application_Current_Path = qApp->applicationDirPath();//当前路径

    QCamera *camera = new QCamera(); // 摄像头对象
    QCameraImageCapture *imageCapture = new QCameraImageCapture(camera); // 用于截取摄像头图像

    bool NotifyStatus=true;

    void Delay_sec_sleep(int time);

    void Delay_msec_sleep(int time);

private slots:

    void on_pushButton_Generate_clicked();

    void on_pushButton_CheckUpdate_clicked();

    void on_pushButton_Donate_clicked();

    void on_pushButton_OfficalSite_clicked();

public slots:

    void ImageIsReady();
    void CheckCam();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
