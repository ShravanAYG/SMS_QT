#include "mainwindow.h"

#include <QApplication>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#include "SMS_QT.h"

#define BUF_SIZE 8192

int set_interface_attribs(int fd, int speed) {
    struct termios tty;
    tcgetattr(fd, &tty);
    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
    tty.c_iflag &= ~IGNBRK;
    tty.c_lflag = 0;
    tty.c_oflag = 0;
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 10;
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~(PARENB | PARODD);
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;
    return tcsetattr(fd, TCSANOW, &tty);
}

void send_at_command(int fd, const char* cmd) {
    write(fd, cmd, strlen(cmd));
    write(fd, "\r", 1);
    usleep(100000);
}

char* read_all_sms(const char* tty_device, int baudrate) {
    int fd = open(tty_device, O_RDWR | O_NOCTTY | O_SYNC);

    speed_t speed;
    if (baudrate == 9600) speed = B9600;
    else if (baudrate == 19200) speed = B19200;
    else speed = B115200;

    set_interface_attribs(fd, speed);

    char* res = (char *)calloc(BUF_SIZE, sizeof(char));

    tcflush(fd, TCIOFLUSH);
    send_at_command(fd, "AT");
    usleep(100000);
    send_at_command(fd, "AT+CMGF=1");
    usleep(100000);
    send_at_command(fd, "AT+CMGL=\"ALL\"");
    usleep(500000);

    int n = read(fd, res, BUF_SIZE - 1);
    res[n] = '\0';

    close(fd);
    return res;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
