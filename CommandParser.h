#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include "ChatUser.h"
#include "Socket.h"

using namespace std;


string parseCommand(ChatUser &user, map<string, vector<ChatUser>> &channels, const string &msg);

string handleDIE(ChatUser &user, map<string, vector<ChatUser>> &channels);
string handleHELP();
string handleINFO();
string handleISON(map<string, vector<ChatUser>> &channels);
string handleJOIN(ChatUser &user, map<string, vector<ChatUser>> &channels);
string handleKILL(ChatUser &user, map<string, vector<ChatUser>> &channels);
string handleLIST(map<string, vector<ChatUser>> &channels);
string handlePRIVMSG(ChatUser &user, map<string, vector<ChatUser>> &channels);
string handleQUIT(ChatUser &user, map<string, vector<ChatUser>> &channels);
string handleRULES();
string handleVERSION();

bool userIsInChannel(ChatUser &user, map<string, vector<ChatUser>> &channels);
void sendToEveryone(ChatUser user, map<string, vector<ChatUser>> &channels, string msg);
void removeUser(string username, map<string, vector<ChatUser>> &channels);
