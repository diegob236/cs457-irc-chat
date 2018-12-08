#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtConcurrent>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstring>
#include <thread>
#include <sys/socket.h>
#include <unistd.h>
#include <mutex>
#include "Socket.h"
#include <fstream>

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
        ~MainWindow();

    private slots:
        void on_pushButton_2_clicked();

    private:
        Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
