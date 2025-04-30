#include "server.h"

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

        thread clientThread(handl_client, clientSocket);
        clientThread.detach();
    }
}

void handl_client(int clientSocket)
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


int main()
{
    Server server("127.0.0.1", 8080);
    server.start();

    return 0;
}



