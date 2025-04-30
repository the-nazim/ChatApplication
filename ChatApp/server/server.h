#include <bits/stdc++.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <thread>
#include <cstring>
#include <cstdlib>

using namespace std;

void handl_client(int clientSocket);