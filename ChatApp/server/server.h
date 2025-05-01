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

class Server 
{
    private:
        int serverSocket;
        sockaddr_in serverAddress;
    
    public:
        Server(string ipAddress, int port)
        {
            serverSocket = socket(AF_INET, SOCK_STREAM,0);
            
            memset(&serverAddress, 0, sizeof(serverAddress));

            serverAddress.sin_family = AF_INET;
            serverAddress.sin_port = htons(port);
            serverAddress.sin_addr.s_addr = ipAddress.empty() ? INADDR_ANY : inet_addr(ipAddress.c_str());


            if(serverSocket == -1)
            {
                cout << "Error in creating socket" << endl;
                exit(1);
            }

            bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
            listen(serverSocket, 5);

            cout<<"Server started !!!"<<endl;
        }

        void start();
        void broadCastMessage();
        void recieveMessage();
    
    ~Server()
    {
        close(serverSocket);
    }
};