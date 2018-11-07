#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <bits/stdc++.h> 
#include "ChatUser.h"
#include "Socket.h"


using namespace std;


string parseCommand(ChatUser user, vector<ChatUser> users, const string &msg);

string handleHELP();
string handleINFO();
string handleQUIT(ChatUser user, vector<ChatUser> users);