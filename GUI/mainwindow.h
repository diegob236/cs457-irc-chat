#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtConcurrent>
#include <QHash>

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstring>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {

    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        int connectToServer();
        void readData();
        void recvServerMessage(string message);
        void recvUserMessage(string message);
        ~MainWindow();

    signals:
        void displayMessage(QString message);
        void displayPrivateMessage(QString message);

    private slots:
        void on_send_clicked();
        void on_send_privmsg_clicked();
        void muteMessages();

    private:
        Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
