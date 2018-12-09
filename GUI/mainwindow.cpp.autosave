#include "mainwindow.h"
#include "ui_mainwindow.h"

// Variables
string hostname = "127.0.0.1";
string username = "anonymous";
string channel = "general";
int port = 2000;
string configFile;
string testFile;
string logFile;

int sock;
struct sockaddr_in addr;
char buffer[2048];
stringstream ss;

QMutex sendMutex;
QMutex recvMutex;
QMutex colorMutex;

// connectToServer(): connect to server
int MainWindow::connectToServer() {

    // Start client socket

    ui->textBrowser_2->insertHtml(QString("<span style=\"color:#888888;\">%1<br/></span>").arg(QString::fromStdString("Connecting to " + hostname + ":" + to_string(port) + "...")));
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        ui->textBrowser_2->insertPlainText("Unable to create socket. \n\n");
        return -1;
    }

    // Initialize sockaddr_in struct
    memset(&addr, '0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    // Set host addr
    if(inet_pton(AF_INET, hostname.c_str(), &addr.sin_addr) <= 0) {
        ui->textBrowser_2->insertPlainText("Invalid addr. \n\n");
        return -1;
    }

    // Connect to socket
    if (::connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        ui->textBrowser_2->insertPlainText("Unable to connect to server. \n\n");
        return -1;
    }

    // Send username to server
    write(sock, string(username+"\n").c_str(), string(username+"\n").size());
    return 0;
}


// readData(): read data from server
void MainWindow::readData() {

    // Recieve messages
    while (true) {
        string message;
        QMutexLocker recvlock(&recvMutex);
        recvlock.relock();
        memset(&buffer, 0, sizeof(buffer));
        recv(sock, (char *)&buffer, sizeof(buffer), 0);
        message = buffer;
        recvlock.unlock();

        // QUIT: close connection
        if (string(message).find("/QUIT\n") != std::string::npos) {
            ui->textBrowser_2->moveCursor(QTextCursor::End);
            ui->textBrowser_2->insertHtml(QString("<span style=\"color:#888888;\">%1<br/></span>").arg(QString::fromStdString("Closing connection...\n")));
            ::close(sock); exit(0);
        }

        // Username: switch username (or set guest username)
        else if (message[0] == '^') {
            username = string(message);
            username = username.substr(1, username.find_first_of('\n')-1);
            ui->textBrowser_2->moveCursor(QTextCursor::End);
            ui->textBrowser_2->insertHtml(QString("<span style=\"color:#888888;\">%1<br/></span>").arg(QString::fromStdString("Your username is " + username + ".")));
        }

        // Channels: switch channels (after being kicked)
        else if (message[0] == '#') {
            string old = string(message);
            old = old.substr(1, old.size()-2);
            ui->textBrowser_2->moveCursor(QTextCursor::End);
            ui->textBrowser_2->insertHtml(QString("<span style=\"color:#888888;\">%1<br/></span>").arg(QString::fromStdString("You have been removed from the #" + old + " channel!")));
            channel = "general";
            string join = "/join general\n";
            write(sock, join.c_str(), join.size());
        }

        // User message: display user's color and print message
        else if (message[0] == '[') {

            // Get user, channel, and message
            string chn = message.substr(1, message.find_first_of(':')-1);
            string user = message.substr(message.find_first_of(':')+1, message.find_last_of(']')-(message.find_first_of(':')+1));
            string msg = message.substr(message.find_last_of(']')+2);

            // Get hash for user's color
            QMutexLocker colorlock(&colorMutex);
            colorlock.relock();
            ss << std::hex << qHash(QString::fromStdString(user), 6);
            std::string hash(ss.str().substr(0, 6));
            ss.str(std::string());
            colorlock.unlock();

            // Display message
            ui->textBrowser_2->moveCursor(QTextCursor::End);
            ui->textBrowser_2->insertHtml(QString::fromStdString("<span style=\"color:#" + hash + ";\">%1</span>").arg(QString::fromStdString(user + ": ")));
            ui->textBrowser_2->insertHtml(QString("<span style=\"color:#000000;\">%1<br/></span>").arg(QString::fromStdString(msg)));
        }

        // Server message: display message in light gray
        else {
            ui->textBrowser_2->moveCursor (QTextCursor::End);
            ui->textBrowser_2->insertHtml(QString("<span style=\"color:#888888;\">%1<br/></span>").arg(QString::fromStdString(message)));
        }
    }
}


// Main Window constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {

    // Set up UI
    ui->setupUi(this);

    // Connect to server
    if (connectToServer() < 0) exit(-1);

    // Start read thread
    QtConcurrent::run(this, &MainWindow::readData);

    // Connect enter key to send button
    connect(ui->lineEdit_2, SIGNAL(returnPressed()), ui->pushButton_2,SIGNAL(clicked()));
    connect(ui->clearchat, SIGNAL(clicked()), ui->clearchat,SIGNAL(clicked()));
    ui->textBrowser_2->moveCursor (QTextCursor::End); //need to get to the bottom of what this line does
}


// Main window destructor
MainWindow::~MainWindow() {
    QMutexLocker sendlock(&sendMutex);
    sendlock.relock();
    write(sock, string("/QUIT\n").c_str(), string("/QUIT\n").size());
    sendlock.unlock();
    ::close(sock);
    delete ui;
    exit(0);
}


// Main window send button
void MainWindow::on_pushButton_2_clicked() {

    // Read message from input
    string sendmsg = ui->lineEdit_2->text().toStdString() + "\n";
    if (sendmsg[0] != '/') {
        ui->textBrowser_2->moveCursor(QTextCursor::End);
        ui->textBrowser_2->insertHtml(QString("<span style=\"color:#0000ff;\">%1</span>").arg(QString::fromStdString(username + ": ")));
        ui->textBrowser_2->insertHtml(QString("<span style=\"color:#000000;\">%1<br/></span>").arg(QString::fromStdString(sendmsg)));
    }

    // Send message
    QMutexLocker sendlock(&sendMutex);
    sendlock.relock();
    write(sock, sendmsg.c_str(), sendmsg.size());
    sendlock.unlock();
    ui->lineEdit_2->clear();
}

void MainWindow::on_clearchat_clicked() {
    ui->textBrowser_2->moveCursor(QTextCursor::End);
    ui->lineEdit_2->clear();
}
