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
mutex sendMutex;
mutex recvMutex;


QPalette blue;
QPalette black;


// connectToServer(): connect to server
int MainWindow::connectToServer() {

    // Start client socket
    ui->plainTextEdit_2->insertPlainText(QString::fromStdString("Connecting to " + hostname + ":" + to_string(port) + "...\n"));
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        ui->plainTextEdit_2->insertPlainText("Unable to create socket. \n\n");
        return -1;
    }

    // Initialize sockaddr_in struct
    memset(&addr, '0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    // Set host addr
    if(inet_pton(AF_INET, hostname.c_str(), &addr.sin_addr) <= 0) {
        ui->plainTextEdit_2->insertPlainText("Invalid addr. \n\n");
        return -1;
    }

    // Connect to socket
    if (::connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        ui->plainTextEdit_2->insertPlainText("Unable to connect to server. \n\n");
        return -1;
    }

    // Send username to server
    write(sock, string(username+"\n").c_str(), string(username+"\n").size());
    return 0;
}


// readData(): read data from server
void MainWindow::readData() {
    while (true) {
        memset(&buffer, 0, sizeof(buffer));
        recv(sock, (char *)&buffer, sizeof(buffer), 0);

        // QUIT
        if (string(buffer).find("/QUIT\n") != std::string::npos) {
            ui->plainTextEdit_2->insertPlainText("Closing connection...\n");
            ::close(sock); exit(0);
        }

        // Guest username
        else if (buffer[0] == '^') {
            username = string(buffer);
            username = username.substr(1, username.find_first_of('\n')-1);
            ui->plainTextEdit_2->insertPlainText (QString::fromStdString("Your username is " + username + ".\n"));
        }

        // Switch channels
        else if (buffer[0] == '#') {
            string old = string(buffer);
            old = old.substr(1, old.size()-2);
            ui->plainTextEdit_2->insertPlainText(QString::fromStdString("You have been removed from the #" + old + " channel!\n"));
            channel = "general";
            string join = "/join general\n";
            write(sock, join.c_str(), join.size());
        }
        else {
            ui->plainTextEdit_2->moveCursor (QTextCursor::End);
            ui->plainTextEdit_2->insertPlainText (QString::fromStdString(buffer));
        }
    }
}

/*
// writeData(): write data to server
void writeData() {
    while(true){
        string s;
        getline(cin, s);
        s += "\n";
        write(sock, s.c_str(), s.size());
    }
}
*/

// Main Window constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    // Color palettes
    blue = ui->plainTextEdit_2->palette();
    black = ui->plainTextEdit_2->palette();
    blue.setColor(QPalette::Text, Qt::blue);
    black.setColor(QPalette::Text, Qt::black);

    // Connect to server
    if (connectToServer() < 0){
        exit(-1);
    }

    // Start read/write threads
    QtConcurrent::run(this, &MainWindow::readData);
    //thread writeThread(&writeData);
    //writeThread.join();
    //readThread.join();

    connect(ui->lineEdit_2, SIGNAL(returnPressed()), ui->pushButton_2,SIGNAL(clicked()));
    ui->plainTextEdit_2->moveCursor (QTextCursor::End);
}


// Main window destructor
MainWindow::~MainWindow()
{
    write(sock, string("/QUIT\n").c_str(), string("/QUIT\n").size());
    ::close(sock);
    delete ui;
    exit(0);
}

void MainWindow::on_pushButton_2_clicked()
{
    string sendmsg = ui->lineEdit_2->text().toStdString() + "\n";
    ui->plainTextEdit_2->moveCursor (QTextCursor::End);
    if (sendmsg[0] != '/') {
        ui->plainTextEdit_2->setPalette(blue);
        ui->plainTextEdit_2->insertPlainText (QString::fromStdString(username + ": "));
        ui->plainTextEdit_2->setPalette(black);
        ui->plainTextEdit_2->insertPlainText (QString::fromStdString(sendmsg));
    }
    write(sock, sendmsg.c_str(), sendmsg.size());
    ui->lineEdit_2->clear();
}
