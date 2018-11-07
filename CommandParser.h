#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <bits/stdc++.h> 
#include "ChatUser.h"
#include "Socket.h"


using namespace std;


string parseCommand(ChatUser user, const string &msg);
string handleHELP();
string handleQUIT(ChatUser user);