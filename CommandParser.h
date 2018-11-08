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

string handleHELP();
string handleINFO();
string handleJOIN(ChatUser &user, map<string, vector<ChatUser>> &channels);
string handleRULES();
string handleVERSION();
string handleQUIT(ChatUser &user, map<string, vector<ChatUser>> &channels);