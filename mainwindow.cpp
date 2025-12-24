#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <strings.h>
#include <string.h>

#include "SMS_QT.h"

char device[256];
int baud;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionQuit, &QAction::triggered, this, &QMainWindow::close);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnExec_clicked()
{
    strncpy(device, ui->txtDevName->text().toUtf8().constData(), sizeof(device) - 1);
    device[sizeof(device) - 1] = '\0';
    if(strcmp(ui->dropBaudSelect->currentText().toUtf8().constData(), "9600") == 0)
        baud = 9600;
    else
        baud = 115200;
    ui->dispMsg->setText(QString::asprintf("Opening %s at %d baud...\n", device, baud));
    char *msgBuf = read_all_sms(device, baud);
    ui->dispMsg->setText(QString::asprintf("%s\n", msgBuf));
    free(msgBuf);
}

