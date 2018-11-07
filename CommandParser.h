#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <bits/stdc++.h> 
#include "Socket.h"


using namespace std;


string parseCommand(shared_ptr<Socket> clientSocket, int id, const string &msg);

string handleHELP();
string handleINFO();
string handleQUIT(shared_ptr<Socket> clientSocket, int id);