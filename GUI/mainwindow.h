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
        Q_INVOKABLE void displayServerMessage(string message);
        Q_INVOKABLE void displayUserMessage(string message);
        ~MainWindow();

    private slots:
        void on_pushButton_2_clicked();
        void muteMessages();

    private:
        Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
