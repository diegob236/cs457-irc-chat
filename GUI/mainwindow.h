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
#include <mutex>
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
        void muteMessages();
        ~MainWindow();

    private slots:
        void on_pushButton_2_clicked();

    private:
        Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
