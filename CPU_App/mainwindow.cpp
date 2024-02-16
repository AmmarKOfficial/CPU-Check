#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSysInfo>
#include <QStorageInfo>
#include <QNetworkInterface>
#include <QSettings>
#include <QProcess>
#include <windows.h>
#include <intrin.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    system("title SystemInfo_Example - Thecodeprogram");
    ui->c_arch->setText(QSysInfo::currentCpuArchitecture().toLocal8Bit().constData());
    ui->p_type->setText(QSysInfo::prettyProductName().toLocal8Bit().constData());
    ui->m_id->setText(QSysInfo::machineHostName().toLocal8Bit().constData());

    int i = 1;
    foreach (const QStorageInfo &storage, QStorageInfo::mountedVolumes()) {
        if (storage.isValid() && storage.isReady()) {
            if (!storage.isReadOnly()) {
                if(i==1){
                    ui->diskn_1->setText(storage.name().toLocal8Bit().constData());
                    ui->disk1_ava->setText(QString::number(storage.bytesAvailable() / 1000000000));
                    ui->disk1_size->setText(QString::number(storage.bytesTotal() / 1000000000));
                }
                if(i==2){
                    ui->diskn_2->setText(storage.name().toLocal8Bit().constData());
                    ui->disk2_ava->setText(QString::number(storage.bytesAvailable() / 1000000000));
                    ui->disk2_size->setText(QString::number(storage.bytesTotal() / 1000000000));
                }
                if(i==3){
                    ui->diskn_3->setText(storage.name().toLocal8Bit().constData());
                    ui->disk3_ava->setText(QString::number(storage.bytesAvailable() / 1000000000));
                    ui->disk3_size->setText(QString::number(storage.bytesTotal() / 1000000000));
                }
                if(i==4){
                    ui->diskn_4->setText(storage.name().toLocal8Bit().constData());
                    ui->disk4_ava->setText(QString::number(storage.bytesAvailable() / 1000000000));
                    ui->disk4_size->setText(QString::number(storage.bytesTotal() / 1000000000));
                }
            }
        }
        i++;
    }

    QSettings settings("HKEY_LOCAL_MACHINE\\HARDWARE\\DESCRIPTION\\System\\BIOS", QSettings::NativeFormat);
    ui->sys_mu->setText(settings.value("SystemManufacturer", "0").toString().toLocal8Bit().constData());
    ui->pname->setText(settings.value("SystemProductName", "0").toString().toLocal8Bit().constData());
    ui->sku->setText(settings.value("SystemSKU", "0").toString().toLocal8Bit().constData());


    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(memoryStatus);

    if (GlobalMemoryStatusEx(&memoryStatus)) {
        double totalMemoryGB = static_cast<double>(memoryStatus.ullTotalPhys) / (1024 * 1024 * 1024);
        double usedMemoryGB = static_cast<double>(memoryStatus.ullTotalPhys - memoryStatus.ullAvailPhys) / (1024 * 1024 * 1024);

        ui->tram->setText(QString::number(totalMemoryGB, 'f', 2) + " GB");
        ui->uram->setText(QString::number(usedMemoryGB, 'f', 2) + " GB");
    }

    // Get the processor frequency using Windows API
    int cpuInfo[4] = { -1 };
    __cpuid(cpuInfo, 0x80000000);

    unsigned int extendedInformation = cpuInfo[0];

    if (extendedInformation >= 0x80000004) {
        char brandString[0x40];
        for (unsigned int i = 0x80000002; i <= 0x80000004; ++i) {
            __cpuid(cpuInfo, i);
            memcpy(brandString + (i - 0x80000002) * 16, cpuInfo, sizeof(cpuInfo));
        }

        ui->cpu->setText(brandString);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    delete ui;
}

