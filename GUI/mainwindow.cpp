#include "mainwindow.h"
#include "ui_mainwindow.h"

// Variables
string hostname = "127.0.0.1";
string username = "anonymous";
int port = 2000;
string configFile;
string testFile;
string logFile;

QString usercolor;
bool muted = false;
string channel = "general";

int sock;
struct sockaddr_in addr;
char buffer[2048];
stringstream ss;


// connectToServer(): connect to server
int MainWindow::connectToServer() {

    // Start client socket
    ui->chat_window->insertHtml(QString("<span style=\"color:#888888;\">%1<br/></span>").arg(QString::fromStdString("Connecting to " + hostname + ":" + to_string(port) + "...")));
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        ui->chat_window->insertPlainText("Unable to create socket. \n\n");
        return -1;
    }

    // Initialize sockaddr_in struct
    memset(&addr, '0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    // Set host addr
    if(inet_pton(AF_INET, hostname.c_str(), &addr.sin_addr) <= 0) {
        ui->chat_window->insertPlainText("Invalid addr. \n\n");
        return -1;
    }

    // Connect to socket
    if (::connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        ui->chat_window->insertPlainText("Unable to connect to server. \n\n");
        return -1;
    }

    // Send username to server
    write(sock, string(username+"\n").c_str(), string(username+"\n").size());
    return 0;
}


// readData(): read data from server
void MainWindow::readData() {

    // Recieve messages
    string message;
    while (true) {
        memset(&buffer, 0, sizeof(buffer));
        recv(sock, (char *)&buffer, sizeof(buffer), 0);
        message = buffer;

        // QUIT: close connection
        if (string(message).find("/QUIT\n") != std::string::npos) {
            recvServerMessage("Closing connection...");
            ::close(sock); exit(0);
        }

        // Username: switch username (or set guest username)
        else if (message[0] == '^') {

            // Change username
            username = string(message);
            username = username.substr(1, username.find_first_of('\n')-1);
            recvServerMessage("Your username is " + username + ".");

            // Get hash for new username's color so each username is its own color
            ss << std::hex << qHash(QString::fromStdString(username), 6);
            usercolor = QString::fromStdString(ss.str().substr(0, 6));
            ss.str(std::string());
        }

        // Channels: switch back to general (after being kicked)
        else if (message[0] == '#') {
            string old = message.substr(1, message.size()-2);
            recvServerMessage("You have been removed from the #" + old + " channel!");
            channel = "general";
            string join = "/join general\n";
            write(sock, join.c_str(), join.size());
        }

        // User message: display user's color and print message
        else if (message[0] == '[') {
            if (!muted) recvUserMessage(message);
        }

        // Server message: display message in light gray
        else recvServerMessage(message);
    }
}


// MainWindow: Constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {

    // Set up UI and connect to server
    ui->setupUi(this);
    if (connectToServer() < 0) exit(-1);

    // Start read thread
    QtConcurrent::run(this, &MainWindow::readData);

    // Connect slots and signals
    connect(ui->input, SIGNAL(returnPressed()), ui->send,SIGNAL(clicked()));                                     // Enter key -> send button
    connect(ui->input_privmsg, SIGNAL(returnPressed()), ui->send_privmsg,SIGNAL(clicked()));                     // Enter key -> send button
    connect(ui->clearchat, SIGNAL(clicked()), ui->chat_window, SLOT(clear()));                                   // Clear chat
    connect(ui->clearchat_2, SIGNAL(clicked()), ui->chat_window_privmsg, SLOT(clear()));                         // Clear private message chat
    connect(ui->mute, SIGNAL(stateChanged(int)), this, SLOT(muteMessages()));                                    // Mute messages
    connect(this, SIGNAL(displayMessage(QString)), ui->chat_window, SLOT(insertHtml(QString)));                  // Display messages
    connect(this, SIGNAL(displayPrivateMessage(QString)), ui->chat_window_privmsg, SLOT(insertHtml(QString)));   // Display private messages
    ui->chat_window->moveCursor(QTextCursor::End);
}


// MainWindow: Destructor
MainWindow::~MainWindow() {
    write(sock, string("/QUIT\n").c_str(), string("/QUIT\n").size());
    ::close(sock);
    delete ui;
    exit(0);
}


// on_send_clicked(): send message
void MainWindow::on_send_clicked() {

    // Read message from input
    string sendmsg = ui->input->text().toStdString() + "\n";
    if (sendmsg[0] != '/') {
        ui->chat_window->moveCursor(QTextCursor::End);
        ui->chat_window->insertHtml(QString("<span style=\"color:#" + usercolor + ";\">%1</span>").arg(QString::fromStdString(username + ": ")));
        ui->chat_window->insertHtml(QString("<span style=\"color:#000000;\">%1<br/></span>").arg(QString::fromStdString(sendmsg)));
    }

    // Send message
    write(sock, sendmsg.c_str(), sendmsg.size());
    ui->input->clear();
}


// on_send_privmsg_clicked(): send private message
void MainWindow::on_send_privmsg_clicked() {

    // Read message from input
    string sendmsg = ui->input_privmsg->text().toStdString() + "\n";
    if (sendmsg[0] != '/') {
        ui->chat_window->moveCursor(QTextCursor::End);
        ui->chat_window->insertHtml(QString("<span style=\"color:#" + usercolor + ";\">%1</span>").arg(QString::fromStdString(username + ": ")));
        ui->chat_window->insertHtml(QString("<span style=\"color:#000000;\">%1<br/></span>").arg(QString::fromStdString(sendmsg)));
    }

    // Send message
    write(sock, sendmsg.c_str(), sendmsg.size());
    ui->input_privmsg->clear();
}


// muteMessages(): toggle mute messages
void MainWindow::muteMessages() {
    muted = !muted;
}


// displayServerMessage(): display server message
void MainWindow::recvServerMessage(string message) {
    emit displayMessage(QString("<span style=\"color:#888888;\">%1<br/></span>").arg(QString::fromStdString(message)));
}


// displayUserMessage(): display user message
void MainWindow::recvUserMessage(string message) {

    // Parse user, channel, and message
    string user = message.substr(message.find_first_of(':')+1, message.find_last_of(']')-(message.find_first_of(':')+1));
    string chn = message.substr(1, message.find_first_of(':')-1);
    string msg = message.substr(message.find_last_of(']')+2);

    // Get hash to calculate user color
    ss << std::hex << qHash(QString::fromStdString(user), 6);
    std::string color(ss.str().substr(0, 6));
    ss.str(std::string());

    // Check if channel is PRIVMSG
    if (chn == "PRIVMSG") {
        emit displayPrivateMessage(QString::fromStdString("<span style=\"color:#" + color + ";\">%1</span>").arg(QString::fromStdString(user + ": ")));
        emit displayPrivateMessage(QString("<span style=\"color:#000000;\">%1<br/></span>").arg(QString::fromStdString(msg)));
    }

    // Display message
    else {
        emit displayMessage(QString::fromStdString("<span style=\"color:#" + color + ";\">%1</span>").arg(QString::fromStdString(user + ": ")));
        emit displayMessage(QString("<span style=\"color:#000000;\">%1<br/></span>").arg(QString::fromStdString(msg)));
    }
}
