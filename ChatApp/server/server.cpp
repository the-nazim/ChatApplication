#include <bits/stdc++.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;

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

void Server::start()
{
    while(true)
    {
        int clientSocket = accept(serverSocket, nullptr,nullptr);
        if(clientSocket == -1)
        {
            cout << "Error in accepting connection" << endl;
            continue;
        }

        int pid = fork();
        if(pid == 0)
        {
            char buffer[1024] = {0};
            while(true)
            {
                memset(buffer, 0, sizeof(buffer));
                int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
                if (bytesReceived <= 0) 
                    // Client disconnected or error occurred
                    break;
                    
                cout << "Message from client: " << buffer << endl;
            }
            close(clientSocket);
            exit(0);   
        }
    }
}

// Server::void broadCastMessage()
// {

// }

// Server::void recieveMessage()
// {

// }

int main()
{
    Server server("127.0.0.1", 8080);
    server.start();

    return 0;
}



