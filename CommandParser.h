#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <bits/stdc++.h> 
#include "Socket.h"


using namespace std;


int parseCommand(shared_ptr<Socket> clientSocket, int id, const string &msg);
int handleQUIT(shared_ptr<Socket> clientSocket, int id);